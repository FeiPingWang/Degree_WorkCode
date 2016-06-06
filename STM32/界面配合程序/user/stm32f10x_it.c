#include "stm32f10x.h"
#include "printf.h"
#include "hardware.h"

u8 canrx_data[8] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};	    //�������ݴ洢
extern u32 CAN_ID;                					    //��ʶ��
extern u8  CanFlag;
extern u16 countZqgs;                 					    //����
extern u16 countJg;
extern u16 countYc;

extern flagWin;
extern flagZqgs;
extern flagJg;
extern flagCjcs;
extern flagYc;

int TZkb = 0; 						    //ռ�ձȿ���	
int TPl = 0;						    //pwm��Ƶ�ʿ���
int TZqgs = 0;						   //���ڸ���
int TJg = 0;							//���ʱ��
int TCjcs = 0;						   //�̼�����
int TYc = 0;							//�ӳ�ʱ��

/*******************************************************************************
* ������  : CAN1_RX0_IRQHandler
* ����    : CAN1�����ж�
* ����    : None
* ���    : None
* ����    : None
* ע��	  : None
*******************************************************************************/ 

void CAN1_RX0_IRQHandler(void)
{
	u16 temp = 0;	
	u16 Pl = 0;						    //pwm��Ƶ�ʿ���
	u16 Zqgs = 0;						//���ڸ���
    CanRxMsg RxMessage;

    RxMessage.StdId = 0x00;
	//RxMessage.ExtId=0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;

  	CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);//��ȡ����0����
 	CAN_ID=RxMessage.StdId;                    //��ȡ��׼֡��ʶ��
 	canrx_data[0] = RxMessage.Data[0];         //��ȡ����
	canrx_data[1] = RxMessage.Data[1];
	canrx_data[2] = RxMessage.Data[2];
	canrx_data[3] = RxMessage.Data[3];
	canrx_data[4] = RxMessage.Data[4];
	canrx_data[5] = RxMessage.Data[5];
	canrx_data[6] = RxMessage.Data[6];
	canrx_data[7] = RxMessage.Data[7];
	CAN_ClearITPendingBit(CAN1 , CAN_IT_FMP0); //������жϱ�־
	
	if(CAN_ID == 0x010)	        			   //���δ����źŵ�֡ID
	{
		/*��ʼ����ת��*/

		Pl = canrx_data[1] * 256 + canrx_data[2];
		TPl = 1000000 / Pl;
		UART2_Print("Ƶ�ʵ���ֵ %d  %d\n",Pl,TPl);

		UART2_Print("Test Start");
		TZkb = (int)(TPl * ((float)canrx_data[0] / (float)100));   //ռ�ձȵ���ֵ
		UART2_Print("ռ�ձ� %d\n",TZkb);

		Zqgs = canrx_data[3]*256 + canrx_data[4];  			//���ڸ���
		TZqgs = (int)(((float)Zqgs / (float)Pl) * 1000) ;  //����ʱ�� �����趨ʱ��1msΪһ����������
		UART2_Print("���ڸ������� %d  %d\n",Zqgs,TZqgs);

		TJg = canrx_data[5];
		UART2_Print("���ʱ����� %d\n",TJg);
			 
		TCjcs = canrx_data[6];   //���趨ʱ�� ֱ���ں����еݼ� ��0ʱֹͣ�̼�	
		UART2_Print("�̼��������� %d\n",TCjcs);

		TYc = canrx_data[7];	   //��ʱ��λs
		UART2_Print("��ʱʱ�� %d\n",TYc);

		/*��ʼ��ʼ��*/
		CanFlag = 0x01;
		flagWin = 1;	
		countYc = 0; 	 
	}
}

void CAN2_RX0_IRQHandler(void)
{
  	CanRxMsg RxMessage;

    RxMessage.StdId = 0x00;
	//RxMessage.ExtId=0x00;
	RxMessage.IDE = 0;
	RxMessage.DLC = 0;
	RxMessage.FMI = 0;
	RxMessage.Data[0] = 0x00;
	RxMessage.Data[1] = 0x00;
	RxMessage.Data[2] = 0x00;
	RxMessage.Data[3] = 0x00;
	RxMessage.Data[4] = 0x00;
	RxMessage.Data[5] = 0x00;
	RxMessage.Data[6] = 0x00;
	RxMessage.Data[7] = 0x00;

	CAN_Receive(CAN2 , CAN_FIFO0 , &RxMessage);//��ȡ����0����
	CAN_ID=RxMessage.StdId;                    //��ȡ��׼֡��ʶ��
	canrx_data[0] = RxMessage.Data[0];         //��ȡ����
	canrx_data[1] = RxMessage.Data[1];
    canrx_data[2] = RxMessage.Data[2];
    canrx_data[3] = RxMessage.Data[3];
	canrx_data[4] = RxMessage.Data[4];
	canrx_data[5] = RxMessage.Data[5];
	canrx_data[6] = RxMessage.Data[6];
	canrx_data[7] = RxMessage.Data[7];
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);//������жϱ�־   
  
	if(CAN_ID == 0x010)	        //���δ����źŵ�֡ID
	{
		CanFlag = 0x02;
		TIM_Cmd(TIM4,ENABLE);  	 //������ʱ��
	//	count=0;
	}	       
}
