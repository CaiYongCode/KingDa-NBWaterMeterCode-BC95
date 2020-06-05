/*******************************************************************************
Copyright: 
File name: valveCtrl.h
Description: 阀门控制相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
#ifndef __VALVE_CTRL_H__
#define __VALVE_CTRL_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
#define FULL_CTRL_TIME  10000           //全开定时时间
#define CWHALF_CTRL_TIME  4000          //正转半开定时时间
#define CCWHALF_CTRL_TIME  3000         //反转半开定时时间
/*******************************************************************************
数据类型定义
*******************************************************************************/
typedef enum{
  IdleCmd,
  FullOpenCmd,
  HalfOpenCmd,
  FullCloseCmd,
  MaintainCmd
}ValveCtrlCmd;
  
typedef enum{
  UnknownStatus,
  FullOpenStatus,
  HalfOpenStatus,
  FullCloseStatus,
  OCPStatus
}ValveCtrlStatus;

typedef struct 
{
  ValveCtrlStatus Status;
  ValveCtrlCmd LastCmd;
  ValveCtrlCmd NextCmd;
}ValveCtrl_TypeDef;  
/*******************************************************************************
外部变量声明区
*******************************************************************************/
extern ValveCtrl_TypeDef ValveCtrl;
/*******************************************************************************
函数声明区
*******************************************************************************/
uint8_t ValveCtrl_GetStatus(void);
void ValveCtrl_Init(void);
void ValveCtrl_DeInit(void);
void ValveCtrl_Process(uint8_t cmd);
void ValveCtrl_FullOpen(void);
void ValveCtrl_HalfOpen(void);
void ValveCtrl_FullClose(void);
void ValveCtrl_Maintain(void);
void ValveCtrl_TimeoutCallback(void);
void ValveCtrl_FullOpenHandler(void);
void ValveCtrl_FullCloseHandler(void);
void ValveCtrl_OCPHandler(void);
/******************************************************************************/
#endif
/*************************************END**************************************/