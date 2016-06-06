#ifndef _PWM_H
#define _PWM_H
#include "stm32f10x.h"

extern int stepcnt;
extern int step_haven;


void running_S(int pulse_given);

#endif
