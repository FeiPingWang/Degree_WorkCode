#include "modelS.h"
#include "virtualS.h"

//unsigned int acc_step = 0;    //加速过程总步数
//unsigned int dec_step = 0;    //减速过程总步数
unsigned int acc_array_length = STEP_AA+STEP_UA+STEP_RA;  //加速过程的离散点数  包括了一个最高点（离散点）
unsigned int dec_array_length = STEP_AA+STEP_UA+STEP_RA;    //减速过程的离散点数

//uint16_t *time_table; //周期数组的的指针索引 
//int *step_table;   //步数数组的指针索引

motor_s motor1;
motor_s motor2;
motor_s motor3;
motor_s motor4;

//int RevetDot = 0;  //减速开始时已经走过的步数 也称为反转点
//int RevetIndex = 0; 
////unsigned int step_given;
//int maxdex = 0;


//根据给定的实际步数 生成对应的S型曲线 
void virtual_s(int id)
{
	int i;
	int j = 0;
	unsigned int stepcount = 0;
	//int step_given = 0;
	motor_s *motor;
	
	
  	if(id & 0x01)
		motor = &motor1;
	if(id & 0x02)
		motor = &motor2;
	if(id & 0x04)
		motor = &motor3;
	if(id & 0x08)
		motor = &motor4;
		
	motor->acc_step = 0;
	motor->dec_step = 0;
	motor->time_table = timetable; //周期数组的的指针索引 
  	motor->step_table = steptable;   //步数数组的指针索引
	if(motor->num_pwm == 0)
	{ 		  	 
		return;
	}
	
	for(i=0; i < acc_array_length; i++)      //计算出表格中加速总步数、减速总步数并赋值给成员变量
      	motor->acc_step += steptable[i];     //包括了加速过程的所有步数 
  	for(i = 1; i <= dec_array_length; i++)
	    motor->dec_step += steptable[i + acc_array_length];
	
	if(motor->num_pwm > motor->acc_step + motor->dec_step)
	{		
	  	motor->step_table[STEP_AA+STEP_UA+STEP_RA] = motor->num_pwm - motor->acc_step - motor->dec_step ;
//	  RevetIndex = acc_array_length + 1;
//	  RevetDot = motor->num_pwm - motor->dec_step;
	}
	else                                 // 2/3曲线
	{
		motor->acc_step = 0;
	  	motor->dec_step = 0;
		motor->time_table = timetable23;
		motor->step_table = steptable23;
		
		for(i = 0; i < acc_array_length; i++)      
      		motor->acc_step += steptable23[i];       
    	for(i = 1; i <= dec_array_length; i++)
	    	motor->dec_step += steptable23[i + acc_array_length];
		
		if (motor->num_pwm > motor->acc_step + motor->dec_step)
	  	{
			motor->step_table[STEP_AA+STEP_UA+STEP_RA] = motor->num_pwm - motor->acc_step - motor->dec_step  ;
//	    RevetIndex = acc_array_length + 1;
//	    RevetDot = motor->num_pwm - motor->dec_step;
	  	}
	  	else                             // 1/3曲线
	  	{
			motor->acc_step = 0;
	    	motor->dec_step = 0;
		  	motor->time_table = timetable13;
	  		motor->step_table = steptable13;
	   
		  	for(i = 0; i < acc_array_length; i++)      
        		motor->acc_step += steptable13[i];       
      		for(i = 1; i <= dec_array_length; i++)
	      		motor->dec_step += steptable13[i + acc_array_length];
		  	if (motor->num_pwm > motor->acc_step + motor->dec_step)
	    	{
			  motor->step_table[STEP_AA+STEP_UA+STEP_RA] = motor->num_pwm - motor->acc_step - motor->dec_step;
//	      RevetIndex = acc_array_length + 1;
//	      RevetDot = motor->num_pwm - motor->dec_step;
	   	 	}
			else                          //1/3不完整曲线
			{
				motor->acc_step = 0;
	      		motor->dec_step = 0;
		    	motor->time_table = timetable13;
	    		motor->step_table = steptable13;
				i= 0;
				while(stepcount + motor->step_table[i] < (motor->num_pwm >> 1))
				{
					stepcount +=  motor->step_table[i];
					i++;
				}
				motor->maxdex = i;
				motor->step_table[motor->maxdex] = (motor->num_pwm >> 1) - stepcount;
				motor->step_table[2 * acc_array_length - motor->maxdex] = (motor->num_pwm >> 1) - stepcount;
				for(j = 0; j <= motor->maxdex; j++)      
          			motor->acc_step += steptable13[j];      
				for(j = 2 * acc_array_length - motor->maxdex; j <= 2 * acc_array_length; j++)      
         			motor->dec_step += steptable13[j];   
				for(j = motor->maxdex + 1; j <= 2 * acc_array_length - (motor->maxdex + 1); j++)
				  	motor->step_table[j] = 0;
			}
		}
 	}	  
}
