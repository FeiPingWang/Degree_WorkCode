#ifndef PRINTF_H
#define PRINTF_H

#define MAX_SIZE 255
#define Print_Flag 1

extern unsigned char size;
extern unsigned char Read_Buffer[MAX_SIZE];

void Usart1_Send_String(char *buf, unsigned short n);
void UART1_Print(char *format,...);
void Usart2_Send_String(char *buf, unsigned short n);
void UART2_Print(char *format,...);


#endif

