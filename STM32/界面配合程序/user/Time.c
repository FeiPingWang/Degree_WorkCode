#include "stm32f10x.h"

int countZqgs=0;	          			 //�����Ķ�ʱ����

void Time4_Init(u16 arr,u16 psc)	//��ʱ��4
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 //����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 							 
}

void TIM4_IRQHandler(void)   //TIM3�жϺ���
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)!= RESET) 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		countZqgs++;  
	}
}
