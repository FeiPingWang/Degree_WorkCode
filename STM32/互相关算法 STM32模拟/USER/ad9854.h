#ifndef __AD9854_H
#define __AD9854_H
#define AD9854_DATA1  GPIOG->ODR	     //ad9854-1八位可并行数据输入
#define AD9854_ADDR1  GPIOB->ODR        // 六位地址输入

#define AD9854_DATA2  GPIOF->ODR	   //ad9854-2八位可并行数据输入
#define AD9854_ADDR2  GPIOE->ODR       //六位地址输入

#define ad9854_sp2	   PDout(0)
#define ad9854_reset2  PDout(1)
#define ad9854_SK2     PDout(2)
#define ad9854_FBH2    PDout(3)
#define ad9854_rd2     PDout(4)
#define ad9854_wr2     PDout(5)
#define ad9854_updata2 PDout(6)

#define ad9854_SK1     PDout(8)
#define ad9854_FBH1    PDout(9)
#define ad9854_rd1     PDout(10)
#define ad9854_reset1  PDout(11)
#define ad9854_sp1	   PDout(12)
#define ad9854_wr1     PDout(13)
#define ad9854_updata1 PDout(14)

void single_wave_1(void);
void Init_AD9854_1(void);
void AD9852_Send_1(u16 addr,u16 data);
void Init_Port_1(void);

void single_wave_2(void);
void Init_AD9854_2(void);
void AD9852_Send_2(u16 addr,u16 data);
void Init_Port_2(void);

#endif