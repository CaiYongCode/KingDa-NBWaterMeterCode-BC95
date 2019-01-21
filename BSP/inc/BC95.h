#ifndef __BC95_H__
#define __BC95_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
#define         RECV_BUFF_SIZE               256//接收缓冲区大小
#define         SEND_BUFF_SIZE               128//发送缓冲区大小
#define         BC95_TIMEROUT_NUM            10  //超时次数
#define         BC95_TIMEROUT_TIME           2 //超时时间 单位s

/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
enum Start_Process_En   //启动流程
{
  BC95_POWER_DOWN,      //掉电
  BC95_POWER_UP,        //上电
  BC95_RECONNECT,       //重连
  
  NRB,                  //重启
  AT,                   //同步波特率
  CMEE,                 //报告移动终端错误
  CGSN,                 //查询IMEI 
  CCID,                 //查询CCID
  CFUN,                 //查询全功能
  NBAND,                //查询频段
  CSQ,                  //查询信号强度
  CGATT,                //查询入网
  CEREG,                //查询网络注册状态
  CSCON,                //查询信令连接状态
  CCLK,                 //查询实时时间
  NCDP,                 //设置CDP服务器
  NSMI,                 //设置发送消息指示
  NNMI,                 //设置接收消息指示
  NMGS,                 //发送消息
  BC95_CONNECT_ERROR,   //启动错误
};
  
struct BC95_Str//BC95 总结构体
{
  char R_Buffer[RECV_BUFF_SIZE];        //接收缓冲区
  unsigned short Recv_Length;         //接收长度
  enum Start_Process_En Start_Process;  //连接进程
  u8 Report_Bit;                        //发送位
  unsigned char TimeoutNum;         //超时计数
  unsigned char Rssi;                 //信号强度
  bool Incident_Pend;                  //事件挂起标志
  unsigned char IPOpt;                //IP选项
  unsigned char Reconnect_Times;      //重连次数
  unsigned char FailTimes;            //失败次数
  unsigned char ICCID[20];
  unsigned char IMEI[15];
  unsigned char ErrorStep;        //故障步骤
  unsigned char ErrorCode;        //故障代码
};
 
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/
extern struct BC95_Str BC95;//BC95 用的寄存器
/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
void BC95_Power_On(void); 
void BC95_Power_Off(void);
void BC95_Reset(void);
void BC95_Process(void);
void BC95_Data_Send(unsigned char *Data,unsigned short Len);

void BC95_Start(void);
void BC95_Recv_Timeout_CallBack(void);
void BC95_Delay_CallBack(void);

void Recv_Data_Process(unsigned char* buff);
void Send_Data_Process(void);
void ACK(u8 messageId,u8 errcode,u8 mid[4]);
void Report_All_Parameters(void);
void Report_HC_Flow(void);

unsigned char Report_History_Data(void);

/********************************************************************************/
#endif

/******************************************END********************************************************/