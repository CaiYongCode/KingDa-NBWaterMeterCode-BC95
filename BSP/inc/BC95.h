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
#define         CONNECT_ERROR_NUM            3  //连接错误次数
#define         SEND_ERROR_NUM               3  //发送错误次数

#define         BC95_POWER_UP_TIME           5//BC95上电时间 单位ms
#define         BC95_R_TIMEROUT_TIME         5 //接收超时 单位ms

#define         BC95_S_TIMEROUT_TIME         6000 //发送数据超时 单位ms

/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
struct Error_Connter_Str
{
  unsigned char Send;
  unsigned char Connect;
};
 

enum Start_Process_En   //启动流程
{
  BC95_POWER_DOWN,      //掉电
  BC95_POWER_UP,        //上电
  BC95_RECONNECT,       //重连
  
  NRB,                  //重启
  AT,                   //同步波特率
  GETNBAND,             //查询频段
  SETNBAND,             //设置频段
  GETCFUN,              //查询电话功能
  SETCFUN,              //设置电话功能
  CIMI,                 //查询IMSI
  CGSN,                 //查询IMEI  
  CCID,                //查询CCID
  CSQ,                  //查询信号强度
  GETCGDCONT,           //查询APN
  SETCGDCONT,           //设置APN  
  GETCGATT,             //查询网络激活状态
  SETCGATT,             //激活网络
  CEREG,                //查询网络注册状态
  CCLK,                 //查询实时时间
  GETNCDP,              //查询CDP服务器
  SETNCDP,              //设置CDP服务器
  NSMI,                 //设置发送消息指示
  NNMI,                 //设置接收消息指示
  NMGS,                 //发送消息
  NQMGR,                //查询消息接收
  NMGR,                 //接收消息
  BC95_CONNECT_ERROR,      //启动错误
};
  
struct BC95_Str//BC95 总结构体
{
  char R_Buffer[RECV_BUFF_SIZE];        //接收缓冲区
  unsigned short Recv_Length;         //接收长度
  enum Start_Process_En Start_Process;  //连接进程
  u8 Report_Bit;                        //发送位
  struct Error_Connter_Str Err_Conner; //错误计数
  unsigned char ErrorRecord;          //错误记录
  unsigned char Rssi;                 //信号强度
  bool Incident_Pend;                  //事件挂起标志

  unsigned char Reconnect_Times;      //重连次数
  unsigned char FailTimes;            //失败次数
  unsigned char ICCID[20];
  unsigned char IMEI[15];
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