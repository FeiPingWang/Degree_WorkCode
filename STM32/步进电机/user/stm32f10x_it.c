//#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "printf.h"
#include "virtualS.h"
#include "running.h"

u8 canrx_data[8] = {0,0 ,0 ,0 ,0 ,0 ,0 ,0};	  //接收数据存储
extern u32 CAN_ID;           						  //标识符
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

  CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);//获取邮箱0数据
  CAN_ID=RxMessage.StdId;                    //从机里面只需要获取主机发送过来的请求ID即可(获取标准帧标识符)
  canrx_data[0] = RxMessage.Data[0];         //获取一个字节的数据，用来作为从机请求标志
  canrx_data[1] = RxMessage.Data[1];
  canrx_data[2] = RxMessage.Data[2];
  canrx_data[3] = RxMessage.Data[3];
  canrx_data[4] = RxMessage.Data[4];
  canrx_data[5] = RxMessage.Data[5];
  canrx_data[6] = RxMessage.Data[6];
  canrx_data[7] = RxMessage.Data[7];
	
  CAN_ClearITPendingBit(CAN1 , CAN_IT_FMP0);//清接收中断标志
  CanFlag = 0x01;                           //置接收完成标志
  UART_Print("进入中断\n");
   for(i = 0;i<8;i++)
   {
  		UART_Print("canrx %d\n",canrx_data[i]);                  //置接收完成标志
    }
}
 
void TIM2_IRQHandler(void)
{
	//清除中断
	if(TIM2->SR&(1<<0))                //定时器与串口都需要先判断中断标志  最后要清除中断
	{
	 //	UART_Print("inter %d",count);    //中断函数中最好不要有打印等占时间的程序  总之中断服务函数中越简短越好。
		motor1.stepcnt++;
		motor1.step_haven++;
  	}
	TIM2->SR = (u16)~TIM_FLAG_Update;  
}
void TIM3_IRQHandler(void)
{
	//清除中断
	if(TIM3->SR&(1<<0))                //定时器与串口都需要先判断中断标志  最后要清除中断
	{
	// UART_Print("inter%d",count);    //中断函数中最好不要有打印等占时间的程序  总之中断服务函数中越简短越好。
		motor2.stepcnt++;
		motor2.step_haven++;
  	}
	TIM3->SR = (u16)~TIM_FLAG_Update;  
}
void TIM4_IRQHandler(void)
{
	//清除中断
	if(TIM4->SR&(1<<0))                //定时器与串口都需要先判断中断标志  最后要清除中断
	{
	// UART_Print("inter%d",count);    //中断函数中最好不要有打印等占时间的程序  总之中断服务函数中越简短越好。
		motor3.stepcnt++;
		motor3.step_haven++;
  	}
	TIM4->SR = (u16)~TIM_FLAG_Update;  
}
void TIM5_IRQHandler(void)
{
	//清除中断
	if(TIM5->SR&(1<<0))                //定时器与串口都需要先判断中断标志  最后要清除中断
	{
	// UART_Print("inter%d",count);    //中断函数中最好不要有打印等占时间的程序  总之中断服务函数中越简短越好。
		motor4.stepcnt++;
		motor4.step_haven++;
  	}
	TIM5->SR = (u16)~TIM_FLAG_Update;  
}