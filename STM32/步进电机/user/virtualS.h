#ifndef VIRTUALS_H
#define VIRTUALS_H
#include "modelS.h"
#include "stm32f10x.h"

extern unsigned int acc_step ;    //���ٹ����ܲ���
extern unsigned int dec_step;    //���ٹ����ܲ���
extern unsigned int acc_array_length ;  //���ٹ��̵���ɢ����  ������һ����ߵ㣨��ɢ�㣩
extern unsigned int dec_array_length ;    //���ٹ��̵���ɢ����
//extern uint16_t *time_table; //��������ĵ�ָ������ 
//extern int *step_table;   //���������ָ������

typedef struct{
	int num_pwm;
	int maxdex;
	int CurrentIndex;
	int stepcnt;
	int step_haven;
	int *step_table;
 
	uint16_t *time_table;
	int acc_step ;
	int dec_step ;
}motor_s;

extern motor_s motor1;
extern motor_s motor2;
extern motor_s motor3;
extern motor_s motor4;
//extern int maxdex ;
extern int RevetDot ;  //���ٿ�ʼʱ�Ѿ��߹��Ĳ��� Ҳ��Ϊ��ת��
extern int RevetIndex; 
//extern unsigned int step_given;

void virtual_s(int id );

#endif
