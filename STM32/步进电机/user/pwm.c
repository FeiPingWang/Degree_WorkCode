#include "pwm.h"

void TIM2_Init(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;  //��������ṹ�� ʱ����ʼ��
	TIM_OCInitTypeDef  TIM_OCInitStruct;          //��������ṹ�� ��ʱ�����ģʽ��ʼ��
	
	GPIO_InitTypeDef GPIO_InitStructure;             
	/* TIM2��TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* GPIOA and AFIO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	/*GPIOA Configuration: TIM3 channel 0 and 6 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 ;     	//PA0��TIM2_CH1_ETR    PA6��TIM3_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		// �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_DeInit(TIM2);
	//TIM3�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//Ԥ��Ƶֵ ÿ10us����һ��
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//����ֵ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse = 500;//�����˴�װ�벶��Ĵ���1������ֵΪTIM3Compare1
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);   //OC1ͨ����ʼ��
	 
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
	TIM_Cmd(TIM2, DISABLE); 
}

void TIM2_period_set(uint16_t period)
{
	TIM2->ARR = period;
	TIM2->CCR1 = period >> 1;
}

void TIM2_CMD(void)
{
	TIM_Cmd(TIM2, ENABLE); 
}
 
 
void TIM3_Init(void) 
{
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;  //��������ṹ�� ʱ����ʼ��
	TIM_OCInitTypeDef  TIM_OCInitStruct;          //��������ṹ�� ��ʱ�����ģʽ��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;             
	/* TIM2��TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  	/* GPIOA and AFIO clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
  	/*GPIOA Configuration: TIM3 channel 0 and 6 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;     //PA0��TIM2_CH1_ETR    PA6��TIM3_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_DeInit(TIM3);
	//TIM3�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//Ԥ��Ƶֵ ÿ10us����һ��
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//����ֵ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse = 500;//�����˴�װ�벶��Ĵ���1������ֵΪTIM3Compare1
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);   //OC1ͨ����ʼ��
	 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
	TIM_Cmd(TIM3, DISABLE); 
}

void TIM3_period_set(uint16_t period)
{
	TIM3->ARR = period;
	TIM3->CCR1 = period >> 1;
}

void TIM3_CMD(void)
{
	TIM_Cmd(TIM3, ENABLE); 
}

void TIM4_Init(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;  //��������ṹ�� ʱ����ʼ��
	TIM_OCInitTypeDef  TIM_OCInitStruct;          //��������ṹ�� ��ʱ�����ģʽ��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;             
	/* TIM2��TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOA and AFIO clock enable */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 
  /*GPIOA Configuration: TIM3 channel 0 and 6 as alternate function push-pull */
 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;     //PA0��TIM2_CH1_ETR    PA6��TIM3_CH1   PB6��TIM4_CH1 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	TIM_DeInit(TIM4);
	//TIM3�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//Ԥ��Ƶֵ ÿ10us����һ��
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//����ֵ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse = 500;//�����˴�װ�벶��Ĵ���1������ֵΪTIM3Compare1
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);   //OC1ͨ����ʼ��
	 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
	TIM_Cmd(TIM4, DISABLE); 
}

void TIM4_period_set(uint16_t period)
{
	TIM4->ARR = period;
	TIM4->CCR1 = period >> 1;
}

void TIM4_CMD(void)
{
	TIM_Cmd(TIM4, ENABLE); 
}

void TIM5_Init(void) 
{
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;  //��������ṹ�� ʱ����ʼ��
	TIM_OCInitTypeDef  TIM_OCInitStruct;          //��������ṹ�� ��ʱ�����ģʽ��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;             
	/* TIM2��TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOA and AFIO clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
  /*GPIOA Configuration: TIM3 channel 0 and 6 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 ;     //PA0��TIM2_CH1_ETR    PA6��TIM3_CH1  PA1��TIM5_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_DeInit(TIM5);
	//TIM3�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;//Ԥ��Ƶֵ ÿ10us����һ��
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//����ֵ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse = 500;//�����˴�װ�벶��Ĵ���1������ֵΪTIM3Compare1
	TIM_OC2Init(TIM5,&TIM_OCInitStruct);   //OC2ͨ����ʼ��
	 
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM5, ENABLE);
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	//ʹ��TIM1�ж�Դ
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 
	TIM_Cmd(TIM5, DISABLE); 
}

void TIM5_period_set(uint16_t period)
{
	TIM5->ARR = period;
	TIM5->CCR2 = period >> 1;
}

void TIM5_CMD(void)
{
	TIM_Cmd(TIM5, ENABLE); 
}