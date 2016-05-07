#include "stm32f10x.h"
#include "pwm.h"
#include "Hardware.h"
#include "printf.h"
#include "cantx.h"
#include "modelS.h"
#include "virtualS.h"
#include "running.h"
#include <string.h>

u8 CanFlag;			   	//接收完数据标志
u32 CAN_ID;             //标识符

int	Pulse_Num_PWM = 0;
extern u8 cantx_data[8];
extern u8 canrx_data[8];

int main(void)
{
		int i, id = 0;
		motor_s *motor;
		RCC_Configuration();
		GPIO_Configuration();
		CAN_Configuration();
		USART_Configuration();
		CAN_NVIC_Configuration();
		
		MotorRunParaInitial();
	    for(i = 0; i < 10; i++)
		 	UART_Print("%d  ", i);
//	UART_Print("\n\n");
//	 for(i = 0; i < 121; i++)
//  UART_Print("%d  ", steptable[i]);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", timetable23[i]);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", steptable23[i]);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", timetable13[i]);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", steptable13[i]);
//	UART_Print("\n\n");
//	//UART_Print("%d", timetable13[0]);
//	virtual_s(Pulse_Num_PWM);
//	UART_Print(" step_table[STEP_AA+STEP_UA+STEP_RA]= %d \n ",  step_table[STEP_AA+STEP_UA+STEP_RA]);
//	UART_Print(" time_table[STEP_AA+STEP_UA+STEP_RA]= %d \n ",  time_table[STEP_AA+STEP_UA+STEP_RA]);
//	UART_Print(" acc_step = %d \n ",  acc_step);
//	UART_Print(" dec_step = %d \n ",  dec_step);
//	UART_Print("motor->maxdex = %d  ", motor->maxdex);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", time_table[i]);
//	UART_Print("\n\n");
//	for(i = 0; i < 121; i++)
//	  UART_Print("%d  ", step_table[i]);
//	UART_Print("\n\n");
		TIM2_Init(); 
		TIM3_Init(); 
		TIM4_Init(); 
		TIM5_Init(); 
	
	//TIM3_period_set(time_table[0]);
 // TIM3_CMD();
//	GPIO_SetBits(GPIOC, GPIO_Pin_2);  

		while(1)
		{
			 if(CanFlag == 0x01)							//表示接收到了主机发送过来的数据请求
			 {
				CanFlag = 0; 
				id = canrx_data[0];
				//id = 0x02;
				//UART_Print("%d\n", id);
				
				if(id & 0x01)		 		//步进电机1
				{
					motor1.num_pwm = canrx_data[4] * 10000 + canrx_data[5] * 100 + canrx_data[6];
					UART_Print("%d\n", motor1.num_pwm);
					virtual_s(id);
					TIM2_period_set(motor1.time_table[0]);
					TIM2_CMD();
				}
				if(id & 0x02)			   //步进电机2
				{
					motor2.num_pwm = canrx_data[4] * 10000 + canrx_data[5] * 100 + canrx_data[6];
					//motor2.num_pwm = 10000;
					UART_Print("%d\n", motor2.num_pwm);
					virtual_s(id);
					TIM3_period_set(motor2.time_table[0]);
					TIM3_CMD();
				}	
				if(id & 0x04)			 //步进电机3
				{
					motor3.num_pwm = canrx_data[4] * 10000 + canrx_data[5] * 100 + canrx_data[6];
					UART_Print("%d\n", motor3.num_pwm);
					virtual_s(id);
					TIM4_period_set(motor3.time_table[0]);
					TIM4_CMD();
				}	
				if(id & 0x08)			 //步进电机4
				{
					motor4.num_pwm = canrx_data[4] * 6000 + canrx_data[5] * 100 + canrx_data[6];
					//motor4.num_pwm = 60000;
					UART_Print("%d\n", motor4.num_pwm);
					virtual_s(id);
					TIM5_period_set(motor4.time_table[0]);
					TIM5_CMD();
				}	
								
				if(canrx_data[1] & 0x01)
					GPIO_SetBits(GPIOC, GPIO_Pin_2);        	//1高电平正转   
				else 
					GPIO_ResetBits(GPIOC, GPIO_Pin_2);			//1低电平反转		
				
				if(canrx_data[1] & 0x02)
					GPIO_SetBits(GPIOC, GPIO_Pin_3);        	//2高电平正传   
				else 
					GPIO_ResetBits(GPIOC, GPIO_Pin_3);			//2低电平反转	
				
				if(canrx_data[1] & 0x04)
					GPIO_SetBits(GPIOC, GPIO_Pin_4);        	//3高电平正传   
				else 
					GPIO_ResetBits(GPIOC, GPIO_Pin_4);			//3低电平反转	
				
				if(canrx_data[1] & 0x08)
					GPIO_SetBits(GPIOC, GPIO_Pin_5);        	//4高电平正传   
				else 
					GPIO_ResetBits(GPIOC, GPIO_Pin_5);			//4低电平反转	
			}
			if(id == 0x01)
				running_S(0x01);
			if(id == 0x02)
				running_S(0x02);
			if(id == 0x04)
				running_S(0x04);
			if(id == 0x08)
				running_S(0x08);
		//memset(canrx_data, 0, sizeof(u8));	
		}
}
