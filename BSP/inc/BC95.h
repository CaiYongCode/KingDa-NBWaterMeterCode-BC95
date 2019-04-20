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
enum StartProcess_En   //启动流程
{
  IDLE,                 //空闲
  BC95_POWER_DOWN,      //掉电
  BC95_RECONNECT,       //重连
  
  NRB,                  //重启
  CMEE,                 //报告移动终端错误
  CFUN0,                //开启最小功能
  NCSEARFCN,            //清除先验频点
  CFUN1,                //开启全功能
  CGSN,                 //查询IMEI 
  CCID,                 //查询CCID
  NCONFIG,              //设置手动入网
  NCDP,                 //设置CDP服务器
  EDRX,                 //关闭模组eDRX功能
  NSMI1,                //设置发送消息指示
  NNMI0,                //设置接收消息指示
  CGATT1,               //触发网络附着
  CSQ,                  //查询信号强度
  NUESTATS,             //查询模块状态
  CGATT,                //查询网络附着
  CEREG,                //查询网络注册状态
  CCLK,                 //查询实时时间
  NNMI1,                //设置接收消息指示
  NMGS,                 //发送消息
};
  
struct BC95_Str//BC95 总结构体
{
  uint8_t RxBuffer[RECV_BUFF_SIZE];        //接收缓冲区
  unsigned short RxLength;         //接收长度
  enum StartProcess_En StartProcess;  //连接进程
  u8 ReportBit;                        //发送位
  unsigned char TimeoutNum;         //超时计数
  unsigned char Rssi;                 //信号强度
  bool IncidentPend;                  //事件挂起标志
  unsigned char ReconnectTimes;      //重连次数
  unsigned char ICCID[20];
  unsigned char IMEI[15];
  unsigned char ErrorStep;        //故障步骤
  unsigned short ErrorCode;        //故障代码
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

void BC95_Timeout_CallBack(void);
void BC95_Delay_CallBack(void);

void Recv_Data_Process(unsigned char* buff);
void Send_Data_Process(void);
void ACK(u8 messageId,u8 errcode,u8 mid[4]);
void Report_All_Parameters(void);
void Report_HC_Flow(void);
void Report_History_Data(void);

/********************************************************************************/
#endif

/******************************************END********************************************************/