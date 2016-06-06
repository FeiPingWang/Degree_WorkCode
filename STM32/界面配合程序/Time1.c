/*Tim1 ��������̼����ʱ���ʱ����*/

#include "stm32f10x.h"
int countYc = 0;
	  
void Time2_Init(u16 arr,u16 psc)		//��ʱ��1
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 //����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
							 
}

void TIM2_IRQHandler(void)   //TIM1�жϺ���
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET) 
	{
	    UART2_Print("���붨ʱ��2�ж�\n");
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		countYc++;
		UART2_Print("countYc %d\n",countYc);
	}
}
