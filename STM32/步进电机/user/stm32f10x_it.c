//#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "printf.h"
#include "virtualS.h"
#include "running.h"

u8 canrx_data[8] = {0,0 ,0 ,0 ,0 ,0 ,0 ,0};	  //�������ݴ洢
extern u32 CAN_ID;           						  //��ʶ��
extern u8 CanFlag;

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	int i;
    CanRxMsg RxMessage;
    RxMessage.StdId = 0x00;
	//RxMessage.ExtId=0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;

  CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);//��ȡ����0����
  CAN_ID=RxMessage.StdId;                    //�ӻ�����ֻ��Ҫ��ȡ�������͹���������ID����(��ȡ��׼֡��ʶ��)
  canrx_data[0] = RxMessage.Data[0];         //��ȡһ���ֽڵ����ݣ�������Ϊ�ӻ������־
  canrx_data[1] = RxMessage.Data[1];
  canrx_data[2] = RxMessage.Data[2];
  canrx_data[3] = RxMessage.Data[3];
  canrx_data[4] = RxMessage.Data[4];
  canrx_data[5] = RxMessage.Data[5];
  canrx_data[6] = RxMessage.Data[6];
  canrx_data[7] = RxMessage.Data[7];
	
  CAN_ClearITPendingBit(CAN1 , CAN_IT_FMP0);//������жϱ�־
  CanFlag = 0x01;                           //�ý�����ɱ�־
  UART_Print("�����ж�\n");
   for(i = 0;i<8;i++)
   {
  		UART_Print("canrx %d\n",canrx_data[i]);                  //�ý�����ɱ�־
    }
}
 
void TIM2_IRQHandler(void)
{
	//����ж�
	if(TIM2->SR&(1<<0))                //��ʱ���봮�ڶ���Ҫ���ж��жϱ�־  ���Ҫ����ж�
	{
	 //	UART_Print("inter %d",count);    //�жϺ�������ò�Ҫ�д�ӡ��ռʱ��ĳ���  ��֮�жϷ�������Խ���Խ�á�
		motor1.stepcnt++;
		motor1.step_haven++;
  	}
	TIM2->SR = (u16)~TIM_FLAG_Update;  
}
void TIM3_IRQHandler(void)
{
	//����ж�
	if(TIM3->SR&(1<<0))                //��ʱ���봮�ڶ���Ҫ���ж��жϱ�־  ���Ҫ����ж�
	{
	// UART_Print("inter%d",count);    //�жϺ�������ò�Ҫ�д�ӡ��ռʱ��ĳ���  ��֮�жϷ�������Խ���Խ�á�
		motor2.stepcnt++;
		motor2.step_haven++;
  	}
	TIM3->SR = (u16)~TIM_FLAG_Update;  
}
void TIM4_IRQHandler(void)
{
	//����ж�
	if(TIM4->SR&(1<<0))                //��ʱ���봮�ڶ���Ҫ���ж��жϱ�־  ���Ҫ����ж�
	{
	// UART_Print("inter%d",count);    //�жϺ�������ò�Ҫ�д�ӡ��ռʱ��ĳ���  ��֮�жϷ�������Խ���Խ�á�
		motor3.stepcnt++;
		motor3.step_haven++;
  	}
	TIM4->SR = (u16)~TIM_FLAG_Update;  
}
void TIM5_IRQHandler(void)
{
	//����ж�
	if(TIM5->SR&(1<<0))                //��ʱ���봮�ڶ���Ҫ���ж��жϱ�־  ���Ҫ����ж�
	{
	// UART_Print("inter%d",count);    //�жϺ�������ò�Ҫ�д�ӡ��ռʱ��ĳ���  ��֮�жϷ�������Խ���Խ�á�
		motor4.stepcnt++;
		motor4.step_haven++;
  	}
	TIM5->SR = (u16)~TIM_FLAG_Update;  
}