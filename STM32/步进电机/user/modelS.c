#include "modelS.h"
#include "printf.h"

/*电机1在该定时周期（电机频率）下应该运行的步数的表格*/
/*下同*/
uint16_t timetable[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/*将参数降为2/3 S型曲线参数生成的表格，这样做的目的是对应运行步数
比较少的情况下也可以找到一条“小"型曲线,1/3曲线也是同样的道理*/
uint16_t timetable23[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable23[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/*将参数降为1/3 S型曲线参数生成的表格*/
uint16_t timetable13[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable13[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/**************************************************************************************
根据S型曲线参数获取某个时刻的频率，所有单位均是标准单位：HZ，S
入口参数:
				fstart，启动频率 
				faa，加加速频率
				taa，加加速时间
				tua，匀加速时间
				tra，减加速时间
				t，时刻t
返回参数：
        t 时刻的运行频率
 **************************************************************************************/
static float GetFreAtTime(float fstart,float faa,float taa,float tua,float tra,float t)
{
		//根据公式计算从开始到最高速过冲中，t时刻的转动频率，公式参见文档的详细解释
	  if(t>=0&&t<taa){
			//加加速阶段
			return fstart+0.5*faa*t*t;
		}else if(taa<=t&&t<(taa+tua)){
			//匀加速阶段
			return fstart+0.5*faa*taa*taa+(t-taa)*faa*taa;
		}else if((taa+tua)<=t&&t<(taa+tua+tra)){
			//减加速阶段
			return fstart+0.5*faa*taa*taa+(tua)*faa*taa+0.5*faa*taa*tra-0.5*faa*taa*(taa+tua+tra-t)*(taa+tua+tra-t)/(tra);  //画图球值
		}else if(t == taa + tua + tra){
			return fstart+0.5*faa*taa*taa+(tua)*faa*taa+0.5*faa*taa*tra;
		}
		
		return 0;
}
 

/**************************************************************************************
 计算S型曲线算法的每一个运行阶梯对应定时器的周期及应该运行的步数    这个函数先不管总的步数，也不管恒速运行的步数
入口参数:
				fstart，启动频率 
				faa，加加速频率
				taa，加加速时间
				tua，匀加速时间
				tra，减加速时间
				MotorTimeTable，计算出来的每个阶梯的定时器周期参数存放数组
				MotorStepTable，计算出来的每个阶梯的运行步数参数存放数组
返回参数：
        无
 **************************************************************************************/
static void CalcMotorPeriStep_CPF(float fstart,float faa,float taa,float tua,float tra,uint16_t TimeTable[],int StepTable[])
{
  int  i;
	float fi = 0;
	/*计算加加速阶段*/
	for(i=0;i<STEP_AA;i++)           
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa/STEP_AA*i);    //先运算速度 离散化时间
		/*将频率转换成定时器周期2TIME_PARA要根据MCU设定的定时器预分频和时钟频率确定*/
		TimeTable[i]=F2TIME_PARA/fi;        //运算定时器ARR的值
		/*按照S型曲线参数原理，加速的过程很长，工程应该中将其修正，除以STEP_PARA*/
		StepTable[i]=fi*(taa/STEP_AA)/STEP_PARA;   //运算每一个时间段上运行的步数
	}

	/*计算匀加速阶段*/
	for(i=STEP_AA;i<STEP_AA+STEP_UA;i++)
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+(tua/STEP_UA)*(i-STEP_AA));
		TimeTable[i]=F2TIME_PARA/fi;
		StepTable[i]=fi*(tua/STEP_UA)/STEP_PARA;
	}
	/*计算减加速阶段*/
	for(i=STEP_AA+STEP_UA;i<STEP_AA+STEP_UA+STEP_RA;i++)
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+tua+tra/STEP_RA*(i-STEP_AA-STEP_UA));
		TimeTable[i]=F2TIME_PARA/fi;
		StepTable[i]=fi*(tra/STEP_RA)/STEP_PARA;
	}
	/*计算最高速阶段*/
	fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+tua+tra);
	TimeTable[STEP_AA+STEP_UA+STEP_RA]=F2TIME_PARA/fi;
	StepTable[STEP_AA+STEP_UA+STEP_RA]=0;
	
	/*减速阶段是对称的*/
	for(i=STEP_AA+STEP_UA+STEP_RA+1;i<2*(STEP_AA+STEP_UA+STEP_RA)+1;i++)    //i的范围是0~2*(STEP_AA+STEP_UA+STEP_RA；
	{ 
		TimeTable[i]=TimeTable[2*(STEP_AA+STEP_UA+STEP_RA)-i];
		StepTable[i]=StepTable[2*(STEP_AA+STEP_UA+STEP_RA)-i];
	}
}
 
/**************************************************************************************
 电机运行参数初始化，主要是根据设定的S型曲线参数生成对应的控制表格
入口参数:
				无
返回参数：
        无
 **************************************************************************************/
void MotorRunParaInitial(void)
{ 
	/*FIXME:用户可以改变该参数实现S型曲线的升降特性*/ 
	CalcMotorPeriStep_CPF(M_FRE_START,M_FRE_AA,M_T_AA,M_T_UA,M_T_RA,timetable,steptable); 

	/*更改参数降为2/3生成的表格*/
	CalcMotorPeriStep_CPF(M_FRE_START*2.0/3,M_FRE_AA*2.0/3,M_T_AA*2.0/3,M_T_UA*2.0/3,M_T_RA*2.0/3,timetable23,steptable23); 
	
	/*更改参数降为1/3生成的表格*/
	CalcMotorPeriStep_CPF(M_FRE_START*1.0/3,M_FRE_AA*1.0/3,M_T_AA*1.0/3,M_T_UA*1.0/3,M_T_RA*1.0/3,timetable13,steptable13); 
	  	
}
