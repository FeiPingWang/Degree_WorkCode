#include "sys.h"
#include "delay.h"								    
unsigned short AD_Value[256][2];	   //��·��ÿ·�洢256������
void GPIO_Configuration_adc(void)
{
	//PC4/5 ��Ϊģ��ͨ����������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;     //ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_DeInit(ADC1); 								//������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;       //ģ��ת�������ڶ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2; //��ʱ��2����
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2; //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

   //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
   //ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����

    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_239Cycles5 );	       //PC4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_239Cycles5 );	  //PC5	 

    // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
   	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1); //��λָ����ADC1��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�
	ADC_StartCalibration(ADC1); //��ʼָ��ADC1��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1)); //��ȡָ��ADC1��У׼����,����״̬��ȴ�
	ADC_ExternalTrigConvCmd(ADC1, ENABLE); 		//ʹ��ָ����ADC1���ⲿת����������
}

void TIM2_Configuration(void)	     //TIM2���ƿ���ADC�Ĳɼ�
{	
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_OCInitTypeDef TIM_OCInitStructure; 

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //ʱ��ʹ��

   TIM_TimeBaseStructure.TIM_Period = 500;		//1��200��
   TIM_TimeBaseStructure.TIM_Prescaler = 719;//ϵͳ��Ƶ72M�������Ƶ720���൱��100K�Ķ�ʱ��2ʱ��
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure); 

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//������ϸ˵��
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//TIM_OutputState_Disable;
   TIM_OCInitStructure.TIM_Pulse = 250;
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//�����PWM1ҪΪLow��PWM2��ΪHigh
   TIM_OC2Init(TIM2, &TIM_OCInitStructure);

   TIM_Cmd(TIM2, ENABLE);
   TIM_InternalClockConfig(TIM2);
   TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
   TIM_UpdateDisableConfig(TIM2, DISABLE);

}


void DMA_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ��ADC1��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = 2*256; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE); //���������ж�
	DMA_Cmd(DMA1_Channel1,ENABLE);//����DMAͨ��1����
	DMA_ClearFlag(DMA1_FLAG_TC1);//���Channel1�ж�

        NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);	 
} 

void DMA1_Channel1_IRQHandler(void)		//DMA�жϺ���
{											 
  //   int  i=0,j=0;
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
		printf("dma����");
		correlation();			//DMA�жϺ��������л�����㷨���򣨣�
    /*   for(i=0;i<2;i++)		
	   {
			for(j=0;j<256;j++)
		 		printf("%d %u\n",i+1,AD_Value[j][i]*3300/4096);
		}*/           
    } 
      DMA_ClearITPendingBit(DMA1_IT_GL1);//��ȫ���ж�
      DMA_ClearFlag(DMA1_FLAG_TC1);	 //�崫���жϱ�־λ
}	
