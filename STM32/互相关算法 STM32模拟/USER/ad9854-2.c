#include "delay.h"
#include "sys.h"
#include "ad9854.h"					

unsigned char ControlRegister2[]={0x00,0x04,0x00,0x40};  
unsigned  char  FTW2[]={0x00,0x10,0x62,0x4D,0xD2,0xF2};
		
void Init_Port_2(void)	//引脚配置
{
	GPIO_InitTypeDef GPIO_InitStructure;   //DATA的引脚输入 PF0-PF7 通用推免输出 50MHZ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	  //ADDR的引脚输入 PE0-PE5 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}  

void AD9852_Send_2(u16 addr,u16 data)
{
	ad9854_wr2=1;
	delay_us(2); 
	AD9854_ADDR2 &= 0xffc0;		  //读取地址数据
	AD9854_ADDR2 |= addr;

	ad9854_wr2=0;
	delay_us(2);
	AD9854_DATA2 &= 0xff00;		   //读取数据
	AD9854_DATA2 |= 0x00ff&data;
	delay_us(2);
	ad9854_wr2=1;
	delay_us(2);

    ad9854_updata2=0;
	delay_us(20);
	ad9854_updata2=1;
	delay_us(20);
	ad9854_updata2=0;
}

void Init_AD9854_2(void)
{
	u8 i;
	u16 addr;
	ad9854_sp2=1;
	ad9854_reset2=0;
	delay_us(5);
	ad9854_reset2=1;	   //产生一个高电平脉冲
	delay_us(1);
	ad9854_reset2=0;
	addr=0x1d;
	AD9852_Send_2(0x20,0x40); 		//osk 地址0x20;
	for(i=4;i>0;i--) 
	{	
		AD9852_Send_2(addr,ControlRegister2[4-i]);
		addr++;
	}
	 ad9854_updata2=0;
	 delay_us(2);
	 ad9854_updata2=1;
	 delay_us(2);
	 ad9854_updata2=0;
}

void single_wave_2(void)
{
	u8 counter;
	u16 addr;
	for(addr=0x04,counter=0;counter<6;counter++)	 //频率字控制
	{	
		AD9852_Send_2(addr,FTW2[counter]);
		addr++;
	}
	ad9854_updata2=0;
	delay_us(2);
	ad9854_updata2=1;
	delay_us(2);
	ad9854_updata2=0;
}