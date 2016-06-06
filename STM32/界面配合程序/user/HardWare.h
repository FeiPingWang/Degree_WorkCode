#ifndef HARDWARE_H
#define HARDWARE_H

void RCC_Configuration(void);
void GPIO_Configuration(void);
void CAN1_Configuration(void);
void CAN2_Configuration(void);
void USART_Configuration(void);
void CAN_NVIC_Configuration(void);
void delay_ms(u16 nms);

#endif