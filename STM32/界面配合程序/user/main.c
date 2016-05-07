#include "stm32f10x.h"
#include "Hardware.h"
#include "printf.h"
					  
u8  CanFlag;		     		   //接收完数据标志
u32 CAN_ID; 

extern u8 cantx_data[8];
extern u8 canrx_data[8];
extern int countZqgs;
extern int countJg;
extern int countYc;

u8 flagWin = 0;
u8 flagZqgs = 0;
u8 flagYc = 0;
u8 flagCjcs = 0;

u8 Empty[8]={0,0,0,0,0,0,0,0};
u8 DATA[8]= {0,1,2,3,4,5,6,7};

extern int TZqgs;						  //周期个数
extern int TJg;							 //间隔时间
extern int TCjcs;						//刺激次数
extern int TYc;						   //延迟时间
extern int TPl;	
extern int TZkb;	
														
int main(void)
{
	float temp;
	int  t;
  	RCC_Configuration();
  	GPIO_Configuration();
  	CAN1_Configuration();
  	CAN2_Configuration();
  	USART_Configuration();
  	NVIC_Configuration();
//	TIM3_PWM_Init(TPl,TZkb);	//debug
//	TIM_Cmd(TIM3,ENABLE);  	      //开启定时器3
	Time2_Init(10000,7199);		 //定时器1的计数单位为1s。
	Time4_Init(100,719);        //定时器4的计数单位为1ms	
		
  	while(1)
  	{
		if(CanFlag == 0x01 && flagWin == 1)
		{
			TIM3_PWM_Init(TPl,TZkb); 		 //初始化PWM波
			flagYc = 1;
			TIM_Cmd(TIM2,ENABLE);  	      	 //开启定时器2
			if(countYc == TYc && flagYc == 1)
			{
				TIM_Cmd(TIM2,DISABLE);	 	 //关闭定时器2
				flagYc = 0;
				flagWin = 0;
				flagCjcs = 1; 
				countYc = 0;
				while(TCjcs > 0)
				{	
					if(flagCjcs == 1)
					{
						//UART2_Print("TCjcs %d\n",TCjcs); 	
						flagCjcs = 0;
						flagZqgs = 1;
						countZqgs = 0;
						TIM_Cmd(TIM4,ENABLE);  	      //开启定时器4
						TIM_Cmd(TIM3,ENABLE);  	      //开启定时器3
					}
					if(countZqgs == TZqgs && flagZqgs == 1)
					{
				 		flagZqgs = 0;
						TCjcs--;
						flagCjcs = 1;
				 		TIM_Cmd(TIM3,DISABLE);  	      //关闭定时器3，PWM波停止
						TIM_Cmd(TIM4,DISABLE);  	      //关闭定时器4
						//delay_ms(TJg *1000); 			 //间隔时间两个刺激间
						countZqgs = 0;
					}
				}
			}	
		} 
	}  				  
  	return 0;
}
																		   