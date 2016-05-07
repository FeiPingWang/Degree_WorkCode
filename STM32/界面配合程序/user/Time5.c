/*定时器5完成延时刺激时间控制*/

#include "stm32f10x.h"

u8 countYcsj = 0;
void Time5_Init(u16 arr,u16 psc)		    //定时器4
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 //不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); 							 
}

void TIM5_IRQHandler(void)   //TIM3中断函数
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update)!= RESET) 
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		countYcsj++;  
	}
}
