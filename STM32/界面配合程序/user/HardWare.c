#include "stm32f10x.h"

ErrorStatus HSEStartUpStatus;

void GPIO_Configuration(void)
{
  	 GPIO_InitTypeDef GPIO_InitStructure;

  	/*����CAN1.RX->PA11����*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//CAN1��������  
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);   
  /* ����CAN1.TX->PA12����*/
  	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   	 GPIO_Init(GPIOA, &GPIO_InitStructure);	     

  /* ����CAN2.RX->PB12����*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			 //CAN2��������
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	 GPIO_Init(GPIOB, &GPIO_InitStructure);   
  /* ����CAN2.TX->PB13����*/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	    
   

	/***�������ô���USART1***/														 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					//USART1�ܽŶ��壬�������ô���
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//TX
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 			//RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/***�������ô���USART2***/														 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					//USART2�ܽŶ��壬�������ô���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*pwm�����PA6*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
											    
}

/*******************************************************
*��������  ��void RCC_Configuration(void)
*��������  ��RCC����
*��������  ��void
*��������ֵ����
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
  /****************	����GPIOA,GPIOB,AFIO,CAN1,CAN2,USART1,USART2ʱ��*****************/
                           
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_CAN1| RCC_APB1Periph_CAN2 , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |RCC_APB1Periph_TIM5,ENABLE);  //������ʱ��2,3,4,5��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |RCC_APB2Periph_TIM1, ENABLE);	//
 
}

/*************usart����*****************/
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

  //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//���ô��ڽ����жϣ������յ�����ʱ��ͷ����жϣ�ִ���жϺ������������

}

/*******************************************************************************
* ������  : CAN1_Configuration
* ����    : ����CAN�����������ڱ�׼֡ģʽ����ʹ�ܽ����ж�
* ����    : None
* ���    : None
* ����    : None
* ע�� 	  : None
*******************************************************************************/
void CAN1_Configuration(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  /* CAN �Ĵ�����ʼ�� */
  CAN_DeInit(CAN1);                            //��CAN1���мĴ�������Ϊȱʡֵ
  CAN_StructInit(&CAN_InitStructure);          //���ṹ�������ȱʡֵ����

  /* CAN �Ĵ�����ʼ�� ����CANͨ�Ų����ʵļ�����Բ鿴STM32���Ĳο��ֲ�*/
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;         //ʹ���Զ����߹��������������Զ�������
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//����ģʽ
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;	   
  CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
  CAN_InitStructure.CAN_Prescaler = 9;		    //CAN���߲���������500Kbit/s	= 36MHz/(1+4+3)*9

  if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED)  //��ʼ��CAN 		
  {
     //���������ӳ�ʼ��ʧ�ܴ���
  }	
  /* CAN ���������ʼ�� */
  CAN_FilterInitStructure.CAN_FilterNumber=0;			         //����ʼ���Ĺ�����1-13 105��28��
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	   //��ʶ������λģʽ
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;   //32λ������
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;			     //��������ʶ��ȫ��Ϊ0
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0; //��������������0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;               //���������
  CAN_FilterInit(&CAN_FilterInitStructure);

  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);                            //ʹ��CAN�����ж�
}


/*******************************************************************************
* ������  : CAN2Configuration
* ����    : ����CAN�����������ڱ�׼֡ģʽ����ʹ�ܽ����ж�
* ����    : None
* ���    : None
* ����    : None
* ע�� 	  : None
*******************************************************************************/
void CAN2_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  	CAN_DeInit(CAN2);                            //��CAN1���мĴ�������Ϊȱʡֵ
  	CAN_StructInit(&CAN_InitStructure);          //���ṹ�������ȱʡֵ����
	CAN_InitStructure.CAN_TTCM=DISABLE;                      //��ʱ�䴥��ͨ��ģʽ  //
    CAN_InitStructure.CAN_ABOM=DISABLE;                      //����Զ����߹���  //
    CAN_InitStructure.CAN_AWUM=DISABLE;                      //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
    CAN_InitStructure.CAN_NART=DISABLE;                          //��ֹ�����Զ����� //
    CAN_InitStructure.CAN_RFLM=DISABLE;                      //���Ĳ�����,�µĸ��Ǿɵ� //
    CAN_InitStructure.CAN_TXFP=DISABLE;                      //���ȼ��ɱ��ı�ʶ������ //
    CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;             //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
    //���ò�����
    CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;              //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1=CAN_BS1_4tq;    //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;   //Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~   CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler=9;            //��Ƶϵ��(Fdiv)Ϊbrp+1    //
    CAN_Init(CAN2, &CAN_InitStructure);            // ��ʼ��CAN2
    CAN_FilterInitStructure.CAN_FilterNumber=14;      //������0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
 
    CAN_FilterInit(&CAN_FilterInitStructure);    //�˲�����ʼ��
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);       //FIFO0��Ϣ�Һ��ж�����. 
}  
/*******************************************************
*��������  ��void CAN_NVIC_Configuration(void)
*��������  ��CAN���߽����ж�
*��������  ��void
*��������ֵ����
*******************************************************/
void NVIC_Configuration(void) 
{    
	NVIC_InitTypeDef NVIC_InitStructure;    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  
	     
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);	

	/*��ʱ��4�ж�*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  
}

/*******************************************************
*��������  ��void delay_us(u32 nus) 
*��������  ����׼��ʱ1us����׼ȷ
*��������  ��u32 nus
*��������ֵ����
*******************************************************/
void delay_us(u32 nus) 
{   
	u32 temp;   
	SysTick->LOAD = 9*nus;   
	SysTick->VAL = 0X00;                        //��ռ�����   
	SysTick->CTRL = 0X01;                       //ʹ�ܣ����������޶����������ⲿʱ��Դ  
	do  
	{       
	  temp = SysTick->CTRL;                     //��ȡ��ǰ������ֵ
	}
	while((temp&0x01)&&(!(temp&(1<<16))));      //�ȴ�ʱ�䵽��      
	SysTick->CTRL = 0x00;                       //�رռ�����     
	SysTick->VAL = 0X00;                        //��ռ�����
}   			   
 	 			    				
/*******************************************************
*��������  ��void delay_ms(u16 nms)
*��������  ��ms��ʱ
*��������  ��u16 nms
*��������ֵ����
*******************************************************/
void delay_ms(u16 nms)
{             
   delay_us(nms * 1000);
}