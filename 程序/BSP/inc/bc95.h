/*******************************************************************************
Copyright: 
File name: BC95.h
Description: BC95相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
#ifndef __BC95_H__
#define __BC95_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
//BC95电源引脚
#define BC95_PWR_Set        GPIO_SetBits(GPIOE,GPIO_Pin_2);
#define BC95_PWR_Rst        GPIO_ResetBits(GPIOE,GPIO_Pin_2);
//BC95复位引脚
#define BC95_RST_Set        GPIO_ResetBits(GPIOE,GPIO_Pin_1);
#define BC95_RST_Rst        GPIO_SetBits(GPIOE,GPIO_Pin_1);
//BC95状态指示灯
//#define BC95_LED_ON        GPIO_SetBits(GPIOD, GPIO_Pin_6)
#define BC95_LED_OFF        GPIO_ResetBits(GPIOD, GPIO_Pin_6)

#define         RECV_BUFF_SIZE               256//接收缓冲区大小
#define         SEND_BUFF_SIZE               1050//发送缓冲区大小
#define         BC95_TIMEROUT_NUM            10  //超时次数
#define         BC95_TIMEROUT_TIME           2000 //超时时间 单位ms

/*******************************************************************************
数据类型定义
*******************************************************************************/
/*BC95联网流程枚举定义*/
typedef enum 
{
  BC95_IDLE,            //空闲
  BC95_SHUTDOWN,        //关机
  BC95_RECONNECT,       //重连

  NRB,                  //重启
  AT,                   //同步波特率
  CMEE,                 //报告移动终端错误
  CFUN0,                //开启最小功能
  NCSEARFCN,            //清除先验频点
  CFUN1,                //开启全功能
  CGSN,                 //查询IMEI 
  NCCID,                //查询CCID
  CIMI,                 //查询IMSI
  NCDP,                 //设置CDP服务器
  NSMI,                 //关闭发送消息指示
  NNMI,                 //关闭接收消息指示
  CGATT1,               //触发网络附着
  CGATT,                //查询网络附着
  CEREG,                //查询网络注册
  CSQ,                  //查询信号强度
  NUESTATS,             //查询模块状态
  CCLK,                 //查询实时时间
  NMSTATUS,             //查询消息注册状态
  QLWULDATAEX,          //发送CON/NON消息
  NMGS,                 //发送消息
  NQMGR,                //查询消息接收状态
  NMGR                  //接收消息
}BC95_ProcessStruct;

struct BC95_Str//BC95 总结构体
{
//  bool FirmwareUpdate;                         //FALSE:空闲；TRUE:固件升级 
  bool IncidentPend;                           //FALSE:空闲；TRUE:事件挂起
  BC95_ProcessStruct Process;                   //连接进程
  uint8_t RxBuffer[RECV_BUFF_SIZE];             //接收缓冲区
  uint16_t RxLength;                            //接收长度
//  uint8_t TxBuffer[SEND_BUFF_SIZE];           //接收缓冲区
//  uint16_t TxLength;                          //发送长度
  uint8_t CCID[20];                             //CCID  
  uint8_t IMEI[15];                             //IMEI        
  uint8_t IMSI[15];                             //IMSI
  uint8_t CSQ;                                  //信号强度
  int16_t RSRP;                                 //信号接收功率
  int16_t SNR;                                  //信噪比
  uint8_t ECL;                                  //增强覆盖等级
  uint32_t CELLID;                              //小区ID
  uint32_t EARFCN;                              //频点    Range 0-262143
  uint16_t PCI;                                 //物理小区标识 Range 0-503
  uint8_t ErrorStep;                            //故障步骤
  uint16_t ErrorCode;                           //故障代码
  uint8_t TimeoutNum;                           //超时计数
  uint8_t ReconnectTimes;                       //重连次数
};
 
/*******************************************************************************
外部变量声明区
*******************************************************************************/
extern struct BC95_Str BC95;//BC95 用的寄存器
/*******************************************************************************
函数声明区
*******************************************************************************/
void BC95_Init(void); 
void BC95_Reset(void);
void BC95_Start(void);
void BC95_DeInit(void);
void BC95_Reconnect(void);
void BC95_ShutDown(void);
void BC95_Process(void);
void BC95_TxStr(unsigned char *Data,unsigned short Len);
void BC95_TxMessage_NMGS(uint8_t *buff,uint16_t length);
void BC95_RxData(uint8_t *buff,uint16_t length);
void BC95_GetErrorInfo(uint8_t *buff,uint16_t length);
void BC95_Timeout(void);
void BC95_Delay_CallBack(void);
void BC95_InquireMsgRecv(void);
void BC95_GetSignalParas(uint8_t *buff, uint16_t length);
void BC95_ACK(uint8_t mid[4]);
/******************************************************************************/
#endif
/*************************************END**************************************/