#include "running.h"
#include "stm32f10x.h"
#include "virtualS.h"
#include "pwm.h"

//int stepcnt = 0;
//int step_haven = 0;
//int CurrentIndex = 0;


//void running_S(int pulse_given)
//{
//	if (step_haven >= pulse_given)
//	{
//		step_haven = 0;
//		stepcnt = 0;
//		CurrentIndex = 0;
//		TIM_Cmd(TIM3, DISABLE);
//	}
//	/*运行*/

//	/*分两种情况  一种maxdex = 0说明有完整的S型曲线    另一种 maxdex != 0说明 不完整的S型曲线*/
//	/*判断索引的位置*/
//  if (maxdex == 0 )
//	{
//	  if(stepcnt >= step_table[CurrentIndex])
//			if (CurrentIndex <= 2 * acc_array_length)
//			{
//				CurrentIndex++;
//				stepcnt = 0;
//				if(CurrentIndex >= acc_array_length * 2)
//						CurrentIndex = acc_array_length * 2;
//			}
////			if(CurrentIndex > 2 * acc_array_length )
////				TIM_Cmd(TIM3, DISABLE);
//   }
//	
//	else 
//	{
//		if(stepcnt >= step_table[CurrentIndex])
//		{ 
//			 if(step_haven <= acc_step) 
//			{
//				CurrentIndex++;
//				if (CurrentIndex > maxdex)
//					CurrentIndex = 2 * acc_array_length - maxdex;
//				stepcnt = 0;
//			}
//			
//   	  if(step_haven > acc_step)
//				{ 
//					CurrentIndex++;
//					stepcnt = 0;
//					/*越界控制*/
//					if(CurrentIndex >= acc_array_length * 2)
//						CurrentIndex = acc_array_length * 2;
////					if(CurrentIndex > 2 * acc_array_length )
////				    TIM_Cmd(TIM3, DISABLE);
//				}  		
//		}
//	}
//	TIM3_period_set(time_table[CurrentIndex]);
//}

void running_S(int id)
{
	motor_s *motor;
	
	if(id & 0x01)
	{
	  motor = &motor1;
		
		TIM2_period_set(motor->time_table[motor->CurrentIndex]);
		
		if (motor->step_haven >= motor->num_pwm)
	  {
		  motor->step_haven = 0;
		  motor->stepcnt = 0;
		  motor->CurrentIndex = 0;
		  TIM_Cmd(TIM2, DISABLE);
	  }
	}
	if(id & 0x02)
	{
	  motor = &motor2;
		
		TIM3_period_set(motor->time_table[motor->CurrentIndex]);
		
		if (motor->step_haven >= motor->num_pwm)
	  {
		  motor->step_haven = 0;
		  motor->stepcnt = 0;
		  motor->CurrentIndex = 0;
		  TIM_Cmd(TIM3, DISABLE);
	  }
	}
	if(id & 0x04)
	{
	  motor = &motor3;
		
		TIM4_period_set(motor->time_table[motor->CurrentIndex]);
		
		if (motor->step_haven >= motor->num_pwm)
	  {
		  motor->step_haven = 0;
		  motor->stepcnt = 0;
		  motor->CurrentIndex = 0;
		  TIM_Cmd(TIM4, DISABLE);
	  }
	}
	if(id & 0x08)
	{
	  motor = &motor4;
		
		TIM5_period_set(motor->time_table[motor->CurrentIndex]);
		
		if (motor->step_haven >= motor->num_pwm)
	  {
		  motor->step_haven = 0;
		  motor->stepcnt = 0;
		  motor->CurrentIndex = 0;
		  TIM_Cmd(TIM5, DISABLE);
	  }
	}
	
	/*运行*/

	/*分两种情况  一种maxdex = 0说明有完整的S型曲线    另一种 maxdex != 0说明 不完整的S型曲线*/
	/*判断索引的位置*/
  if ( motor->maxdex == 0 )
	{
	  if( motor->stepcnt >= motor->step_table[ motor->CurrentIndex])
			if ( motor->CurrentIndex <= 2 * acc_array_length)
			{
				 motor->CurrentIndex++;
				 motor->stepcnt = 0;
				if( motor->CurrentIndex >= acc_array_length * 2)
						 motor->CurrentIndex = acc_array_length * 2;
			}
//			if(CurrentIndex > 2 * acc_array_length )
//				TIM_Cmd(TIM3, DISABLE);
   }
	
	else 
	{
		if( motor->stepcnt >=  motor->step_table[motor->CurrentIndex])
		{ 
			 if( motor->step_haven <=  motor->acc_step) 
			{
				 motor->CurrentIndex++;
				if ( motor->CurrentIndex >  motor->maxdex)
					 motor->CurrentIndex = 2 * acc_array_length -  motor->maxdex;
				 motor->stepcnt = 0;
			}
			
   	  if( motor->step_haven >  motor->acc_step)
				{ 
					 motor->CurrentIndex++;
					 motor->stepcnt = 0;
					/*越界控制*/
					if( motor->CurrentIndex >= acc_array_length * 2)
						 motor->CurrentIndex = acc_array_length * 2;
//					if(CurrentIndex > 2 * acc_array_length )
//				    TIM_Cmd(TIM3, DISABLE);
				}  		
		}
	}
}
