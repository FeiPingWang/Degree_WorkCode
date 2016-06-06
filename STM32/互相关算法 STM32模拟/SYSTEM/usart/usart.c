#include "delay.h"
#include "sys.h"
#include "stdio.h"

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif

void GPIO_Configuration_usrt(void)
{				 
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //RS485输入输出控制
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_1);		                     //RS485发送 不输出
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	          //USART2 TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 //复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 //A端口 
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         	 	 //USART2 RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   	 //复用开漏输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 //A端口 
}

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;	
	RCC_DeInit(); //RCC 系统复位
	RCC_HSEConfig(RCC_HSE_ON); //开启HSE
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); //等待HSE准备好
	if(HSEStartUpStatus == SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Enable Prefetch Buffer
		FLASH_SetLatency(FLASH_Latency_2); //Set 2 Latency cycles
		RCC_HCLKConfig(RCC_SYSCLK_Div1); //AHB clock = SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1); //APB2 clock = HCLK
		RCC_PCLK1Config(RCC_HCLK_Div2); //APB1 clock = HCLK/2
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); //PLLCLK = 12MHz * 6 = 72 MHz
		RCC_PLLCmd(ENABLE); //Enable PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //Wait till PLL is ready
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //Select PLL as system clock source
		while(RCC_GetSYSCLKSource() != 0x08); //Wait till PLL is used as system clock source
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1| RCC_APB2Periph_AFIO, ENABLE ); //使能ADC1通道时钟，各个管脚时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC最大时间不能超过14M
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA传输
	}
}

void NVIC_Configuration(void)
{
  
  	  NVIC_InitTypeDef NVIC_InitStructure;  
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	    
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			     	//设置串口2中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	     	//抢占优先级 0
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//子优先级为0
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
						
}  

void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;						//速率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
 
    USART_Init(USART2, &USART_InitStructure);							//配置串口参数函数
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能串口2接受中断
    USART_Cmd(USART2, ENABLE);	
}
