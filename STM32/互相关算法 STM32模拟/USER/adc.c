#include "sys.h"
#include "delay.h"								    
unsigned short AD_Value[256][2];	   //两路，每路存储256个数据
void GPIO_Configuration_adc(void)
{
	//PC4/5 作为模拟通道输入引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;     //模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_DeInit(ADC1); 								//将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;       //模数转换工作在多次模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2; //定时器2触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 2; //顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

   //设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
   //ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期

    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_239Cycles5 );	       //PC4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_239Cycles5 );	  //PC5	 

    // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
   	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1
	ADC_ResetCalibration(ADC1); //复位指定的ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1复位校准寄存器的状态,设置状态则等待
	ADC_StartCalibration(ADC1); //开始指定ADC1的校准状态
	while(ADC_GetCalibrationStatus(ADC1)); //获取指定ADC1的校准程序,设置状态则等待
	ADC_ExternalTrigConvCmd(ADC1, ENABLE); 		//使能指定的ADC1的外部转换启动功能
}

void TIM2_Configuration(void)	     //TIM2控制开启ADC的采集
{	
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_OCInitTypeDef TIM_OCInitStructure; 

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //时钟使能

   TIM_TimeBaseStructure.TIM_Period = 500;		//1秒200次
   TIM_TimeBaseStructure.TIM_Prescaler = 719;//系统主频72M，这里分频720，相当于100K的定时器2时钟
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure); 

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//下面详细说明
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//TIM_OutputState_Disable;
   TIM_OCInitStructure.TIM_Pulse = 250;
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//如果是PWM1要为Low，PWM2则为High
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
	DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值（ADC1）
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = 2*256; //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE); //开传输完中断
	DMA_Cmd(DMA1_Channel1,ENABLE);//允许DMA通道1传输
	DMA_ClearFlag(DMA1_FLAG_TC1);//清除Channel1中断

        NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);	 
} 

void DMA1_Channel1_IRQHandler(void)		//DMA中断函数
{											 
  //   int  i=0,j=0;
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
		printf("dma进入");
		correlation();			//DMA中断函数中运行互相关算法程序（）
    /*   for(i=0;i<2;i++)		
	   {
			for(j=0;j<256;j++)
		 		printf("%d %u\n",i+1,AD_Value[j][i]*3300/4096);
		}*/           
    } 
      DMA_ClearITPendingBit(DMA1_IT_GL1);//清全局中断
      DMA_ClearFlag(DMA1_FLAG_TC1);	 //清传输中断标志位
}	
