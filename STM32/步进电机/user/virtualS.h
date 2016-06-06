#ifndef VIRTUALS_H
#define VIRTUALS_H
#include "modelS.h"
#include "stm32f10x.h"

extern unsigned int acc_step ;    //加速过程总步数
extern unsigned int dec_step;    //减速过程总步数
extern unsigned int acc_array_length ;  //加速过程的离散点数  包括了一个最高点（离散点）
extern unsigned int dec_array_length ;    //减速过程的离散点数
//extern uint16_t *time_table; //周期数组的的指针索引 
//extern int *step_table;   //步数数组的指针索引

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
extern int RevetDot ;  //减速开始时已经走过的步数 也称为反转点
extern int RevetIndex; 
//extern unsigned int step_given;

void virtual_s(int id );

#endif
