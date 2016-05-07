#include "stm32f10x.h"
#include "printf.h"
#include "math.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char size;
unsigned char Read_Buffer[MAX_SIZE];
void Usart2_Send_String(char *buf, unsigned short n)
{
    unsigned short i;
    for(i = 0; i < n; i ++){
    while((USART2->SR & USART_FLAG_TXE) == RESET);	//判断串口接收数据是否完成，如果没有完成则继续等待，不知道这个地方是否需要将标志清掉
    USART2->DR=buf[i];        						//将buf里面的数据从串口发送
    }

}

void UART_Print(char *format,...)					//任何形式的数据都可以发送
{
    char buf[200];
    va_list ap;
    unsigned short n;
    if(Print_Flag==0)
        return;
    va_start(ap,format);
    memset(buf,0,sizeof(buf));
    n=vsprintf(buf,format,ap);
    Usart2_Send_String(buf,n);
    va_end(ap);
}

