#include "stm32f10x.h"
#include "Hardware.h"

ErrorStatus HSEStartUpStatus;

/*******************************************************
*��������  ��void GPIO_Configuration(void)
*��������  ��GPIO ��ʼ��
*��������  ��void
*��������ֵ����
*******************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  /* ����CAN.RX->PA11���ţ����ϻ���*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//CAN��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
  /* ����CAN.TX->PA12����,��������*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	     
/*******************************************************/

/***�������ô���USART2***/														 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					//USART2�ܽŶ��壬�������ô���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
/***�����ź�PC2��PC3��PC4��PC5*************/

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
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_CAN1 , ENABLE);	   //CANʱ��ѡ��APB2����ЧΪ36MHz��ͨ�Ų����ʼ���ʹ��
}

/*******************************************************************************
* ������  : CAN_Configuration
* ����    : ����CAN�����������ڱ�׼֡ģʽ����ʹ�ܽ����ж�
* ����    : None
* ���    : None
* ����    : None
* ע�� 	  : None
*******************************************************************************/
void CAN_Configuration(void)
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

/*******************************************************
*��������  ��void USART_Configuration(void)
*��������  �������ô�������
*��������  ��void
*��������ֵ����
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

  //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//���ô��ڽ����жϣ������յ�����ʱ��ͷ����жϣ�ִ���жϺ������������
}

/*******************************************************
*��������  ��void CAN_NVIC_Configuration(void)
*��������  ��CAN���߽����ж�
*��������  ��void
*��������ֵ����
*******************************************************/
void CAN_NVIC_Configuration(void) 
{    
	NVIC_InitTypeDef NVIC_InitStructure;    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
	      
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
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


















