#include "stm32f10x.h"
#include "printf.h"
#include "hardware.h"

u8 canrx_data[8] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};	    //接收数据存储
extern u32 CAN_ID;                					    //标识符
extern u8  CanFlag;
extern u16 countZqgs;                 					    //计数
extern u16 countJg;
extern u16 countYc;

extern flagWin;
extern flagZqgs;
extern flagJg;
extern flagCjcs;
extern flagYc;

int TZkb = 0; 						    //占空比控制	
int TPl = 0;						    //pwm波频率控制
int TZqgs = 0;						   //周期个数
int TJg = 0;							//间隔时间
int TCjcs = 0;						   //刺激次数
int TYc = 0;							//延迟时间

/*******************************************************************************
* 函数名  : CAN1_RX0_IRQHandler
* 描述    : CAN1接收中断
* 输入    : None
* 输出    : None
* 返回    : None
* 注意	  : None
*******************************************************************************/ 

void CAN1_RX0_IRQHandler(void)
{
	u16 temp = 0;	
	u16 Pl = 0;						    //pwm波频率控制
	u16 Zqgs = 0;						//周期个数
    CanRxMsg RxMessage;

    RxMessage.StdId = 0x00;
	//RxMessage.ExtId=0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;

  	CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);//获取邮箱0数据
 	CAN_ID=RxMessage.StdId;                    //获取标准帧标识符
 	canrx_data[0] = RxMessage.Data[0];         //获取数据
	canrx_data[1] = RxMessage.Data[1];
	canrx_data[2] = RxMessage.Data[2];
	canrx_data[3] = RxMessage.Data[3];
	canrx_data[4] = RxMessage.Data[4];
	canrx_data[5] = RxMessage.Data[5];
	canrx_data[6] = RxMessage.Data[6];
	canrx_data[7] = RxMessage.Data[7];
	CAN_ClearITPendingBit(CAN1 , CAN_IT_FMP0); //清接收中断标志
	
	if(CAN_ID == 0x010)	        			   //单次触发信号的帧ID
	{
		/*开始数据转换*/

		Pl = canrx_data[1] * 256 + canrx_data[2];
		TPl = 1000000 / Pl;
		UART2_Print("频率的数值 %d  %d\n",Pl,TPl);

		UART2_Print("Test Start");
		TZkb = (int)(TPl * ((float)canrx_data[0] / (float)100));   //占空比的数值
		UART2_Print("占空比 %d\n",TZkb);

		Zqgs = canrx_data[3]*256 + canrx_data[4];  			//周期个数
		TZqgs = (int)(((float)Zqgs / (float)Pl) * 1000) ;  //持续时间 现在设定时器1ms为一个基本周期
		UART2_Print("周期个数参数 %d  %d\n",Zqgs,TZqgs);

		TJg = canrx_data[5];
		UART2_Print("间隔时间参数 %d\n",TJg);
			 
		TCjcs = canrx_data[6];   //无需定时器 直接在函数中递减 到0时停止刺激	
		UART2_Print("刺激次数参数 %d\n",TCjcs);

		TYc = canrx_data[7];	   //延时单位s
		UART2_Print("延时时间 %d\n",TYc);

		/*开始初始化*/
		CanFlag = 0x01;
		flagWin = 1;	
		countYc = 0; 	 
	}
}

void CAN2_RX0_IRQHandler(void)
{
  	CanRxMsg RxMessage;

    RxMessage.StdId = 0x00;
	//RxMessage.ExtId=0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;

	CAN_Receive(CAN2 , CAN_FIFO0 , &RxMessage);//获取邮箱0数据
	CAN_ID=RxMessage.StdId;                    //获取标准帧标识符
	canrx_data[0] = RxMessage.Data[0];         //获取数据
	canrx_data[1] = RxMessage.Data[1];
    canrx_data[2] = RxMessage.Data[2];
    canrx_data[3] = RxMessage.Data[3];
	canrx_data[4] = RxMessage.Data[4];
	canrx_data[5] = RxMessage.Data[5];
	canrx_data[6] = RxMessage.Data[6];
	canrx_data[7] = RxMessage.Data[7];
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);//清接收中断标志   
  
	if(CAN_ID == 0x010)	        //单次触发信号的帧ID
	{
		CanFlag = 0x02;
		TIM_Cmd(TIM4,ENABLE);  	 //开启定时器
	//	count=0;
	}	       
}
