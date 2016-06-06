#include "stm32f10x.h"

ErrorStatus HSEStartUpStatus;

void GPIO_Configuration(void)
{
  	 GPIO_InitTypeDef GPIO_InitStructure;

  	/*配置CAN1.RX->PA11引脚*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//CAN1总线配置  
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);   
  /* 配置CAN1.TX->PA12引脚*/
  	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   	 GPIO_Init(GPIOA, &GPIO_InitStructure);	     

  /* 配置CAN2.RX->PB12引脚*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			 //CAN2总线配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	 GPIO_Init(GPIOB, &GPIO_InitStructure);   
  /* 配置CAN2.TX->PB13引脚*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	    
   

	/***测试所用串口USART1***/														 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					//USART1管脚定义，测试所用串口
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//TX
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 			//RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/***测试所用串口USART2***/														 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					//USART2管脚定义，测试所用串口
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*pwm波输出PA6*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
											    
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
    FLASH_SetLatency(FLASH_Latency_1);

    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);

    RCC_PREDIV2Config(RCC_PREDIV2_Div2);     //4M
	RCC_PLL2Config(RCC_PLL2Mul_10); 		     //40M
	RCC_PLL2Cmd(ENABLE);

    while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
	{
	}

	RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2,RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);   //72M
	RCC_PLLCmd(ENABLE);

    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }	 	
  /****************	开启GPIOA,GPIOB,AFIO,CAN1,CAN2,USART1,USART2时钟*****************/
                           
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_CAN1| RCC_APB1Periph_CAN2 , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |RCC_APB1Periph_TIM5,ENABLE);  //开启定时器2,3,4,5的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |RCC_APB2Periph_TIM1, ENABLE);	//
 
}

/*************usart配置*****************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;  

  //usart1
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE); 

  //usart2
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART2, &USART_InitStructure);
  USART_Cmd(USART2,ENABLE);

  //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//设置串口接收中断，当接收到数据时候就发生中断，执行中断函数里面的数据

}

/*******************************************************************************
* 函数名  : CAN1_Configuration
* 描述    : 配置CAN控制器工作在标准帧模式，并使能接收中断
* 输入    : None
* 输出    : None
* 返回    : None
* 注意 	  : None
*******************************************************************************/
void CAN1_Configuration(void)
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


/*******************************************************************************
* 函数名  : CAN2Configuration
* 描述    : 配置CAN控制器工作在标准帧模式，并使能接收中断
* 输入    : None
* 输出    : None
* 返回    : None
* 注意 	  : None
*******************************************************************************/
void CAN2_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  	CAN_DeInit(CAN2);                            //将CAN1所有寄存器设置为缺省值
  	CAN_StructInit(&CAN_InitStructure);          //将结构体参数按缺省值填入
	CAN_InitStructure.CAN_TTCM=DISABLE;                      //非时间触发通信模式  //
    CAN_InitStructure.CAN_ABOM=DISABLE;                      //软件自动离线管理  //
    CAN_InitStructure.CAN_AWUM=DISABLE;                      //睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)//
    CAN_InitStructure.CAN_NART=DISABLE;                          //禁止报文自动传送 //
    CAN_InitStructure.CAN_RFLM=DISABLE;                      //报文不锁定,新的覆盖旧的 //
    CAN_InitStructure.CAN_TXFP=DISABLE;                      //优先级由报文标识符决定 //
    CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;             //模式设置： mode:0,普通模式;1,回环模式; //
    //设置波特率
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;              //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1=CAN_BS1_4tq;    //Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;   //Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~   CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler=9;            //分频系数(Fdiv)为brp+1    //
    CAN_Init(CAN2, &CAN_InitStructure);            // 初始化CAN2
    CAN_FilterInitStructure.CAN_FilterNumber=14;      //过滤器0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32位
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器0
 
    CAN_FilterInit(&CAN_FilterInitStructure);    //滤波器初始化
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);       //FIFO0消息挂号中断允许. 
}  
/*******************************************************
*函数名称  ：void CAN_NVIC_Configuration(void)
*函数作用  ：CAN总线接收中断
*函数参数  ：void
*函数返回值：无
*******************************************************/
void NVIC_Configuration(void) 
{    
	NVIC_InitTypeDef NVIC_InitStructure;    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  
	     
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // 主优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // 主优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // 次优先级为0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);	

	/*定时器4中断*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
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