#include "stm32f10x.h"

u8 cantx_data[8] = {0 ,0 , 0 , 0 , 0 , 0 , 0 , 0};

/*******************************************************************************
* 函数名  : CanWriteData
* 描述    : 发送一帧数据到CAN总线
* 输入    : 数据标识符
* 输出    : None
* 返回    : None
* 注意	  : None
*******************************************************************************/
void CanWriteData1(uint16_t ID , u8 data ,u8 DATA[8])
{
  u8 i;
  CanTxMsg TxMessage;
  TxMessage.StdId = ID;          //标准帧标识符
  //TxMessage.ExtId = ID;
  cantx_data[0] = data;
  cantx_data[1]	= DATA[1];
  cantx_data[2]	= DATA[2];
  cantx_data[3]	= DATA[3];
  cantx_data[4]	= DATA[4];
  cantx_data[5]	= DATA[5];
  cantx_data[6]	= DATA[6];
  cantx_data[7]	= DATA[7];

  TxMessage.RTR = CAN_RTR_DATA;  //数据帧
  TxMessage.IDE = CAN_ID_STD ;   //标准帧模式
  TxMessage.DLC = 8;             //数据长度
  TxMessage.Data[0] = cantx_data[0];//发送数据，作为从机选通标志    
  TxMessage.Data[1] = cantx_data[1];    
  TxMessage.Data[2] = cantx_data[2];    
  TxMessage.Data[3] = cantx_data[3];    
  TxMessage.Data[4] = cantx_data[4];    
  TxMessage.Data[5] = cantx_data[5];     
  TxMessage.Data[6] = cantx_data[6];    
  TxMessage.Data[7] = cantx_data[7]; 
  for(i = 0 ; i < 8 ; i ++)	    	//把待发送数据全部清掉
  {
    cantx_data[i] = 0x00; 
  }
       
  CAN_Transmit(CAN1 , &TxMessage);//发送一帧数据到CAN总线
}

void CanWriteData2(uint16_t ID , u8 data,u8 DATA[8])
{
  u8 i;
  CanTxMsg TxMessage;
  TxMessage.StdId = ID;          //标准帧标识符
  //TxMessage.ExtId = ID;
  cantx_data[0] = data;
  cantx_data[1]	= DATA[1];
  cantx_data[2]	= DATA[2];
  cantx_data[3]	= DATA[3];
  cantx_data[4]	= DATA[4];
  cantx_data[5]	= DATA[5];
  cantx_data[6]	= DATA[6];
  cantx_data[7]	= DATA[7];

  TxMessage.RTR = CAN_RTR_DATA;  //数据帧
  TxMessage.IDE = CAN_ID_STD ;   //标准帧模式
  TxMessage.DLC = 8;             //数据长度
  TxMessage.Data[0] = cantx_data[0];//发送数据，作为从机选通标志    
  TxMessage.Data[1] = cantx_data[1];    
  TxMessage.Data[2] = cantx_data[2];    
  TxMessage.Data[3] = cantx_data[3];    
  TxMessage.Data[4] = cantx_data[4];    
  TxMessage.Data[5] = cantx_data[5];     
  TxMessage.Data[6] = cantx_data[6];    
  TxMessage.Data[7] = cantx_data[7]; 
  for(i = 0 ; i < 8 ; i ++)		   //把待发送数据全部清掉
  {
    cantx_data[i] = 0x00; 
  }     
  CAN_Transmit(CAN2 , &TxMessage);//发送一帧数据到CAN总线
}

