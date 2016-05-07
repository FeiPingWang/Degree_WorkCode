/*Tim1 完成两个刺激间隔时间计时功能*/

#include "stm32f10x.h"
int countYc = 0;
	  
void Time2_Init(u16 arr,u16 psc)		//定时器1
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 //不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
							 
}

void TIM2_IRQHandler(void)   //TIM1中断函数
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET) 
	{
	    UART2_Print("进入定时器2中断\n");
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		countYc++;
		UART2_Print("countYc %d\n",countYc);
	}
}
