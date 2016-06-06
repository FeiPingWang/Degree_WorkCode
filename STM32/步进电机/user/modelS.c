#include "modelS.h"
#include "printf.h"

/*���1�ڸö�ʱ���ڣ����Ƶ�ʣ���Ӧ�����еĲ����ı��*/
/*��ͬ*/
uint16_t timetable[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/*��������Ϊ2/3 S�����߲������ɵı����������Ŀ���Ƕ�Ӧ���в���
�Ƚ��ٵ������Ҳ�����ҵ�һ����С"������,1/3����Ҳ��ͬ���ĵ���*/
uint16_t timetable23[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable23[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/*��������Ϊ1/3 S�����߲������ɵı��*/
uint16_t timetable13[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};
int steptable13[2*(STEP_AA+STEP_UA+STEP_RA)+1] = { 0};

/**************************************************************************************
����S�����߲�����ȡĳ��ʱ�̵�Ƶ�ʣ����е�λ���Ǳ�׼��λ��HZ��S
��ڲ���:
				fstart������Ƶ�� 
				faa���Ӽ���Ƶ��
				taa���Ӽ���ʱ��
				tua���ȼ���ʱ��
				tra��������ʱ��
				t��ʱ��t
���ز�����
        t ʱ�̵�����Ƶ��
 **************************************************************************************/
static float GetFreAtTime(float fstart,float faa,float taa,float tua,float tra,float t)
{
		//���ݹ�ʽ����ӿ�ʼ������ٹ����У�tʱ�̵�ת��Ƶ�ʣ���ʽ�μ��ĵ�����ϸ����
	  if(t>=0&&t<taa){
			//�Ӽ��ٽ׶�
			return fstart+0.5*faa*t*t;
		}else if(taa<=t&&t<(taa+tua)){
			//�ȼ��ٽ׶�
			return fstart+0.5*faa*taa*taa+(t-taa)*faa*taa;
		}else if((taa+tua)<=t&&t<(taa+tua+tra)){
			//�����ٽ׶�
			return fstart+0.5*faa*taa*taa+(tua)*faa*taa+0.5*faa*taa*tra-0.5*faa*taa*(taa+tua+tra-t)*(taa+tua+tra-t)/(tra);  //��ͼ��ֵ
		}else if(t == taa + tua + tra){
			return fstart+0.5*faa*taa*taa+(tua)*faa*taa+0.5*faa*taa*tra;
		}
		
		return 0;
}
 

/**************************************************************************************
 ����S�������㷨��ÿһ�����н��ݶ�Ӧ��ʱ�������ڼ�Ӧ�����еĲ���    ��������Ȳ����ܵĲ�����Ҳ���ܺ������еĲ���
��ڲ���:
				fstart������Ƶ�� 
				faa���Ӽ���Ƶ��
				taa���Ӽ���ʱ��
				tua���ȼ���ʱ��
				tra��������ʱ��
				MotorTimeTable�����������ÿ�����ݵĶ�ʱ�����ڲ����������
				MotorStepTable�����������ÿ�����ݵ����в��������������
���ز�����
        ��
 **************************************************************************************/
static void CalcMotorPeriStep_CPF(float fstart,float faa,float taa,float tua,float tra,uint16_t TimeTable[],int StepTable[])
{
  int  i;
	float fi = 0;
	/*����Ӽ��ٽ׶�*/
	for(i=0;i<STEP_AA;i++)           
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa/STEP_AA*i);    //�������ٶ� ��ɢ��ʱ��
		/*��Ƶ��ת���ɶ�ʱ�����ڣF2TIME_PARAҪ����MCU�趨�Ķ�ʱ��Ԥ��Ƶ��ʱ��Ƶ��ȷ��*/
		TimeTable[i]=F2TIME_PARA/fi;        //���㶨ʱ��ARR��ֵ
		/*����S�����߲���ԭ�����ٵĹ��̺ܳ�������Ӧ���н�������������STEP_PARA*/
		StepTable[i]=fi*(taa/STEP_AA)/STEP_PARA;   //����ÿһ��ʱ��������еĲ���
	}

	/*�����ȼ��ٽ׶�*/
	for(i=STEP_AA;i<STEP_AA+STEP_UA;i++)
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+(tua/STEP_UA)*(i-STEP_AA));
		TimeTable[i]=F2TIME_PARA/fi;
		StepTable[i]=fi*(tua/STEP_UA)/STEP_PARA;
	}
	/*��������ٽ׶�*/
	for(i=STEP_AA+STEP_UA;i<STEP_AA+STEP_UA+STEP_RA;i++)
	{
		fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+tua+tra/STEP_RA*(i-STEP_AA-STEP_UA));
		TimeTable[i]=F2TIME_PARA/fi;
		StepTable[i]=fi*(tra/STEP_RA)/STEP_PARA;
	}
	/*��������ٽ׶�*/
	fi=GetFreAtTime(fstart,faa,taa,tua,tra,taa+tua+tra);
	TimeTable[STEP_AA+STEP_UA+STEP_RA]=F2TIME_PARA/fi;
	StepTable[STEP_AA+STEP_UA+STEP_RA]=0;
	
	/*���ٽ׶��ǶԳƵ�*/
	for(i=STEP_AA+STEP_UA+STEP_RA+1;i<2*(STEP_AA+STEP_UA+STEP_RA)+1;i++)    //i�ķ�Χ��0~2*(STEP_AA+STEP_UA+STEP_RA��
	{ 
		TimeTable[i]=TimeTable[2*(STEP_AA+STEP_UA+STEP_RA)-i];
		StepTable[i]=StepTable[2*(STEP_AA+STEP_UA+STEP_RA)-i];
	}
}
 
/**************************************************************************************
 ������в�����ʼ������Ҫ�Ǹ����趨��S�����߲������ɶ�Ӧ�Ŀ��Ʊ��
��ڲ���:
				��
���ز�����
        ��
 **************************************************************************************/
void MotorRunParaInitial(void)
{ 
	/*FIXME:�û����Ըı�ò���ʵ��S�����ߵ���������*/ 
	CalcMotorPeriStep_CPF(M_FRE_START,M_FRE_AA,M_T_AA,M_T_UA,M_T_RA,timetable,steptable); 

	/*���Ĳ�����Ϊ2/3���ɵı��*/
	CalcMotorPeriStep_CPF(M_FRE_START*2.0/3,M_FRE_AA*2.0/3,M_T_AA*2.0/3,M_T_UA*2.0/3,M_T_RA*2.0/3,timetable23,steptable23); 
	
	/*���Ĳ�����Ϊ1/3���ɵı��*/
	CalcMotorPeriStep_CPF(M_FRE_START*1.0/3,M_FRE_AA*1.0/3,M_T_AA*1.0/3,M_T_UA*1.0/3,M_T_RA*1.0/3,timetable13,steptable13); 
	  	
}
