/*******************************************************************************
Copyright: 
File name: uplink_protocol.h
Description: 上行通信协议相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
#ifndef __UPLINK_PROTOCOL_H__
#define __UPLINK_PROTOCOL_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
#define UPLINK_RX_MAX           64     //上行接收最大字节数
#define UPLINK_TX_MAX           200     //上行发送最大字节数
#define UPLINK_TIMEROUT_TIME    10000    //上行超时时间10s
/*******************************************************************************
数据类型定义
*******************************************************************************/
/*消息码定义*/
typedef enum    
{
  MessageId_Idle        = 0x0000,       //空闲
  MessageId_0001        = 0x0001,       //上报状态数据
  MessageId_0002        = 0x0002,       //上报采样数据
}UplinkProtocol_MessageId_TypeDef;

/*上行协议结构体定义*/
typedef  struct
{
  bool IncidentPend;                           //事件挂起标志 
  UplinkProtocol_MessageId_TypeDef MsgId;       //消息ID
//  uint8_t RxBuffer[UPLINK_RX_MAX];      //接收缓冲区
//  uint8_t RxLength;                     //接收长度
  uint8_t TxBuffer[UPLINK_TX_MAX];      //发送缓冲区
  uint16_t TxLength;                    //发送长度
  uint8_t TimeoutTimes;                 //超时次数
}UplinkProtocol_Struct;
/*******************************************************************************
外部变量声明区
*******************************************************************************/
extern UplinkProtocol_Struct UP;
/*******************************************************************************
函数声明区
*******************************************************************************/
void UplinkProtocol_Init(void);
void UplinkProtocol_DeInit(void);
void UplinkProtocol_TimeoutEnd(void);
void UplinkProtocol_StartReport(void);
void UplinkProtocol_TxProcess(void);
void UplinkProtocol_TxSuccess(void);
void UplinkProtocol_RxProcess(uint8_t *buff,uint16_t length);
void UplinkProtocol_ReportMessageId_0001(void);
void UplinkProtocol_ReportMessageId_0002(void);
void UplinkProtocol_Delay(void);
void UplinkProtocol_Timeout(void);
bool UplinkProtocol_IsReporting(void);

/******************************************************************************/
#endif
/*************************************END**************************************/


