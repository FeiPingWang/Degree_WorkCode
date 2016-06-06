#include "delay.h"
#include "sys.h"
#include "ad9854.h"	
#include "tim.h"
#include "hxg.h"

//extern unsigned short AD_Value[2];
int i=0;
extern int flag;  
				  
void main(void)
{

	delay_init(72);	 		 //系统时钟72MHZ
	//tim_init();       		//一分钟读取1000
	TIM2_Configuration();

	////USRT函数部分//////
	RCC_Configuration();
	GPIO_Configuration_usrt();
	NVIC_Configuration();
	USART_Config();

	///ad9854函数声明
	Init_Port_1();
	Init_AD9854_1();
	single_wave_1();

	Init_Port_2();
	Init_AD9854_2();
	single_wave_2();	 		  

	//adc函数声明
	GPIO_Configuration_adc();
	ADC_Configuration();
	DMA_Configuration();
	DMA1_Channel1_IRQHandler();  

	while(1)
	{
	//	printf("dd");
	}
}
