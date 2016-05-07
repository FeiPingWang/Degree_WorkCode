#include "stm32f10x.h"

u8 cantx_data[8] = {0 ,0 , 0 , 0 , 0 , 0 , 0 , 0};

/*******************************************************************************
* ������  : CanWriteData
* ����    : ����һ֡���ݵ�CAN����
* ����    : ���ݱ�ʶ��
* ���    : None
* ����    : None
* ע��	  : None
*******************************************************************************/
void CanWriteData1(uint16_t ID , u8 data ,u8 DATA[8])
{
  u8 i;
  CanTxMsg TxMessage;
  TxMessage.StdId = ID;          //��׼֡��ʶ��
  //TxMessage.ExtId = ID;
  cantx_data[0] = data;
  cantx_data[1]	= DATA[1];
  cantx_data[2]	= DATA[2];
  cantx_data[3]	= DATA[3];
  cantx_data[4]	= DATA[4];
  cantx_data[5]	= DATA[5];
  cantx_data[6]	= DATA[6];
  cantx_data[7]	= DATA[7];

  TxMessage.RTR = CAN_RTR_DATA;  //����֡
  TxMessage.IDE = CAN_ID_STD ;   //��׼֡ģʽ
  TxMessage.DLC = 8;             //���ݳ���
  TxMessage.Data[0] = cantx_data[0];//�������ݣ���Ϊ�ӻ�ѡͨ��־    
  TxMessage.Data[1] = cantx_data[1];    
  TxMessage.Data[2] = cantx_data[2];    
  TxMessage.Data[3] = cantx_data[3];    
  TxMessage.Data[4] = cantx_data[4];    
  TxMessage.Data[5] = cantx_data[5];     
  TxMessage.Data[6] = cantx_data[6];    
  TxMessage.Data[7] = cantx_data[7]; 
  for(i = 0 ; i < 8 ; i ++)	    	//�Ѵ���������ȫ�����
  {
    cantx_data[i] = 0x00; 
  }
       
  CAN_Transmit(CAN1 , &TxMessage);//����һ֡���ݵ�CAN����
}

void CanWriteData2(uint16_t ID , u8 data,u8 DATA[8])
{
  u8 i;
  CanTxMsg TxMessage;
  TxMessage.StdId = ID;          //��׼֡��ʶ��
  //TxMessage.ExtId = ID;
  cantx_data[0] = data;
  cantx_data[1]	= DATA[1];
  cantx_data[2]	= DATA[2];
  cantx_data[3]	= DATA[3];
  cantx_data[4]	= DATA[4];
  cantx_data[5]	= DATA[5];
  cantx_data[6]	= DATA[6];
  cantx_data[7]	= DATA[7];

  TxMessage.RTR = CAN_RTR_DATA;  //����֡
  TxMessage.IDE = CAN_ID_STD ;   //��׼֡ģʽ
  TxMessage.DLC = 8;             //���ݳ���
  TxMessage.Data[0] = cantx_data[0];//�������ݣ���Ϊ�ӻ�ѡͨ��־    
  TxMessage.Data[1] = cantx_data[1];    
  TxMessage.Data[2] = cantx_data[2];    
  TxMessage.Data[3] = cantx_data[3];    
  TxMessage.Data[4] = cantx_data[4];    
  TxMessage.Data[5] = cantx_data[5];     
  TxMessage.Data[6] = cantx_data[6];    
  TxMessage.Data[7] = cantx_data[7]; 
  for(i = 0 ; i < 8 ; i ++)		   //�Ѵ���������ȫ�����
  {
    cantx_data[i] = 0x00; 
  }     
  CAN_Transmit(CAN2 , &TxMessage);//����һ֡���ݵ�CAN����
}

