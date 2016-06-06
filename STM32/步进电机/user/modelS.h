#ifndef MODELS_H
#define MODELS_H

#include "stm32f10x.h"


#define M_FRE_START 500
#define M_FRE_AA 20000
#define M_T_AA 0.3
#define M_T_UA 0.6
#define M_T_RA 0.3

#define STEP_AA 15
#define STEP_UA 30
#define STEP_RA 15

#define F2TIME_PARA 1000000
#define STEP_PARA 1

extern uint16_t timetable[2*(STEP_AA+STEP_UA+STEP_RA)+1];
extern int steptable[2*(STEP_AA+STEP_UA+STEP_RA)+1];

extern uint16_t timetable23[2*(STEP_AA+STEP_UA+STEP_RA)+1];
extern int steptable23[2*(STEP_AA+STEP_UA+STEP_RA)+1];

extern uint16_t timetable13[2*(STEP_AA+STEP_UA+STEP_RA)+1];
extern int steptable13[2*(STEP_AA+STEP_UA+STEP_RA)+1];

void MotorRunParaInitial(void);





#endif
