#include "stm32f10x.h"
#include "Hardware.h"

ErrorStatus HSEStartUpStatus;

/*******************************************************
*函数名称  ：void GPIO_Configuration(void)
*函数作用  ：GPIO 初始化
*函数参数  ：void
*函数返回值：无
*******************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  /* 配置CAN.RX->PA11引脚，板上黄线*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//CAN总线配置
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  /* 配置CAN.TX->PA12引脚,板上绿线*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	     
/*******************************************************/

/***测试所用串口USART2***/														 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					//USART2管脚定义，测试所用串口
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
/***方向信号PC2、PC3、PC4、PC5*************/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);


}
/*******************************************************
*函数名称  ：void RCC_Configuration(void)
*函数作用  ：RCC设置
*函数参数  ：void
*函数返回值：无
*******************************************************/
void RCC_Configuration(void)
{
  
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO , ENABLE);                         
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_CAN1 , ENABLE);	   //CAN时钟选择APB2，等效为36MHz，通信波特率计算使用
}

/*******************************************************************************
* 函数名  : CAN_Configuration
* 描述    : 配置CAN控制器工作在标准帧模式，并使能接收中断
* 输入    : None
* 输出    : None
* 返回    : None
* 注意 	  : None
*******************************************************************************/
void CAN_Configuration(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  /* CAN 寄存器初始化 */
  CAN_DeInit(CAN1);                            //将CAN1所有寄存器设置为缺省值
  CAN_StructInit(&CAN_InitStructure);          //将结构体参数按缺省值填入

  /* CAN 寄存器初始化 关于CAN通信波特率的计算可以查看STM32中文参考手册*/
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;         //使能自动离线管理，断线重连能自动连接上
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//正常模式
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;	   
  CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
  CAN_InitStructure.CAN_Prescaler = 9;		    //CAN总线波特率设置500Kbit/s	= 36MHz/(1+4+3)*9

  if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED)  //初始化CAN 		
  {
     //这里可以添加初始化失败处理
  }	
  /* CAN 过滤器组初始化 */
  CAN_FilterInitStructure.CAN_FilterNumber=0;			         //待初始化的过滤器1-13 105有28个
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	   //标识符屏蔽位模式
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   //32位过滤器
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			     //过滤器标识符全部为0
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //过滤器关联邮箱0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //激活过滤器
  CAN_FilterInit(&CAN_FilterInitStructure);

  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);                            //使能CAN接收中断
}

/*******************************************************
*函数名称  ：void USART_Configuration(void)
*函数作用  ：测试用串口设置
*函数参数  ：void
*函数返回值：无
*******************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART2, &USART_InitStructure);
  USART_Cmd(USART2, ENABLE);

  //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//设置串口接收中断，当接收到数据时候就发生中断，执行中断函数里面的数据
}

/*******************************************************
*函数名称  ：void CAN_NVIC_Configuration(void)
*函数作用  ：CAN总线接收中断
*函数参数  ：void
*函数返回值：无
*******************************************************/
void CAN_NVIC_Configuration(void) 
{    
	NVIC_InitTypeDef NVIC_InitStructure;    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
	      
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // 主优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************
*函数名称  ：void delay_us(u32 nus) 
*函数作用  ：标准延时1us，很准确
*函数参数  ：u32 nus
*函数返回值：无
*******************************************************/
void delay_us(u32 nus) 
{   
	u32 temp;   
	SysTick->LOAD = 9*nus;   
	SysTick->VAL = 0X00;                        //清空计数器   
	SysTick->CTRL = 0X01;                       //使能，减到零是无动作，采用外部时钟源  
	do  
	{       
	  temp = SysTick->CTRL;                     //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));      //等待时间到达      
	SysTick->CTRL = 0x00;                       //关闭计数器     
	SysTick->VAL = 0X00;                        //清空计数器
 }   			   
 	 			    				
/*******************************************************
*函数名称  ：void delay_ms(u16 nms)
*函数作用  ：ms延时
*函数参数  ：u16 nms
*函数返回值：无
*******************************************************/
void delay_ms(u16 nms)
{            
   delay_us(nms * 1000);
}


















