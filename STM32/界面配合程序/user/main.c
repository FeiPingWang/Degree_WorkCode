#include "stm32f10x.h"
#include "Hardware.h"
#include "printf.h"
					  
u8  CanFlag;		     		   //���������ݱ�־
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

extern int TZqgs;						  //���ڸ���
extern int TJg;							 //���ʱ��
extern int TCjcs;						//�̼�����
extern int TYc;						   //�ӳ�ʱ��
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
//	TIM_Cmd(TIM3,ENABLE);  	      //������ʱ��3
	Time2_Init(10000,7199);		 //��ʱ��1�ļ�����λΪ1s��
	Time4_Init(100,719);        //��ʱ��4�ļ�����λΪ1ms	
		
  	while(1)
  	{
		if(CanFlag == 0x01 && flagWin == 1)
		{
			TIM3_PWM_Init(TPl,TZkb); 		 //��ʼ��PWM��
			flagYc = 1;
			TIM_Cmd(TIM2,ENABLE);  	      	 //������ʱ��2
			if(countYc == TYc && flagYc == 1)
			{
				TIM_Cmd(TIM2,DISABLE);	 	 //�رն�ʱ��2
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
						TIM_Cmd(TIM4,ENABLE);  	      //������ʱ��4
						TIM_Cmd(TIM3,ENABLE);  	      //������ʱ��3
					}
					if(countZqgs == TZqgs && flagZqgs == 1)
					{
				 		flagZqgs = 0;
						TCjcs--;
						flagCjcs = 1;
				 		TIM_Cmd(TIM3,DISABLE);  	      //�رն�ʱ��3��PWM��ֹͣ
						TIM_Cmd(TIM4,DISABLE);  	      //�رն�ʱ��4
						//delay_ms(TJg *1000); 			 //���ʱ�������̼���
						countZqgs = 0;
					}
				}
			}	
		} 
	}  				  
  	return 0;
}
																		   