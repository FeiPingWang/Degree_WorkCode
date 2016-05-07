#include "modelS.h"
#include "virtualS.h"

//unsigned int acc_step = 0;    //���ٹ����ܲ���
//unsigned int dec_step = 0;    //���ٹ����ܲ���
unsigned int acc_array_length = STEP_AA+STEP_UA+STEP_RA;  //���ٹ��̵���ɢ����  ������һ����ߵ㣨��ɢ�㣩
unsigned int dec_array_length = STEP_AA+STEP_UA+STEP_RA;    //���ٹ��̵���ɢ����

//uint16_t *time_table; //��������ĵ�ָ������ 
//int *step_table;   //���������ָ������

motor_s motor1;
motor_s motor2;
motor_s motor3;
motor_s motor4;

//int RevetDot = 0;  //���ٿ�ʼʱ�Ѿ��߹��Ĳ��� Ҳ��Ϊ��ת��
//int RevetIndex = 0; 
////unsigned int step_given;
//int maxdex = 0;


//���ݸ�����ʵ�ʲ��� ���ɶ�Ӧ��S������ 
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
	motor->time_table = timetable; //��������ĵ�ָ������ 
  	motor->step_table = steptable;   //���������ָ������
	if(motor->num_pwm == 0)
	{ 		  	 
		return;
	}
	
	for(i=0; i < acc_array_length; i++)      //���������м����ܲ����������ܲ�������ֵ����Ա����
      	motor->acc_step += steptable[i];     //�����˼��ٹ��̵����в��� 
  	for(i = 1; i <= dec_array_length; i++)
	    motor->dec_step += steptable[i + acc_array_length];
	
	if(motor->num_pwm > motor->acc_step + motor->dec_step)
	{		
	  	motor->step_table[STEP_AA+STEP_UA+STEP_RA] = motor->num_pwm - motor->acc_step - motor->dec_step ;
//	  RevetIndex = acc_array_length + 1;
//	  RevetDot = motor->num_pwm - motor->dec_step;
	}
	else                                 // 2/3����
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
	  	else                             // 1/3����
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
			else                          //1/3����������
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
