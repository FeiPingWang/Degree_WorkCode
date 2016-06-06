#ifndef  PWM_H
#define  PWM_H
#include "stm32f10x.h"

void TIM2_period_set(uint16_t period);
void TIM2_Init(void);
void TIM2_CMD(void);

void TIM3_period_set(uint16_t period);
void TIM3_Init(void);
void TIM3_CMD(void);

void TIM4_period_set(uint16_t period);
void TIM4_Init(void);
void TIM4_CMD(void);

void TIM5_period_set(uint16_t period);
void TIM5_Init(void);
void TIM5_CMD(void);

#endif
