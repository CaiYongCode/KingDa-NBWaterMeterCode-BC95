/*******************************************************************************
Copyright: 
File name: pulse.h
Description: 脉冲相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
#ifndef __PULSE_H__
#define __PULSE_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
#define Pulse_Cal1_Port         GPIOD                                 //脉冲计数1
#define Pulse_Cal1_Pin          GPIO_Pin_1
#define Pulse_Cal1_Mode         GPIO_Mode_In_FL_IT
#define Pulse_Cal1_Data()       GPIO_ReadInputDataBit(Pulse_Cal1_Port,Pulse_Cal1_Pin)

#define Pulse_Cal2_Port         GPIOD                                 //脉冲计数2
#define Pulse_Cal2_Pin          GPIO_Pin_0
#define Pulse_Cal2_Mode         GPIO_Mode_In_FL_IT
#define Pulse_Cal2_Data()       GPIO_ReadInputDataBit(Pulse_Cal2_Port,Pulse_Cal2_Pin)

#define Pulse_Weak_Port         GPIOF                                 //脉冲唤醒
#define Pulse_Weak_Pin          GPIO_Pin_0
#define Pulse_Weak_Mode         GPIO_Mode_In_PU_IT
#define Pulse_Weak_Data()       GPIO_ReadInputDataBit(Pulse_Weak_Port,Pulse_Weak_Pin)
/*******************************************************************************
数据类型定义
*******************************************************************************/
/*脉冲状态枚举*/
typedef enum 
{ 
  PulseIdle,
  PulseStatus1,
  PulseStatus2,
  PulseStatus3,
  PulseStatus4
}Pulse_StatusEnum;
/*脉冲结构体*/
typedef struct
{
  Pulse_StatusEnum ForwardStatus;       //正转状态
  Pulse_StatusEnum ReverseStatus;       //反转状态
  uint8_t Sensor1LostTimes;             //脉冲1丢失次数
  uint8_t Sensor2LostTimes;             //脉冲2丢失次数
  uint8_t Sensor3LostTimes;             //脉冲3丢失次数
}Pulse_Struct;
/*******************************************************************************
外部变量声明区
*******************************************************************************/
extern Pulse_Struct Pulse;
/*******************************************************************************
函数声明区
*******************************************************************************/
void Pulse_Config(void);
void Pulse_Calculate1(void);
void Pulse_Calculate2(void);
uint8_t Pulse_Sensor1Check(void);
uint8_t Pulse_Sensor2Check(void);
uint8_t Pulse_MgtIfrCheck(void);
void Pulse_ManualWake(void);
void Pulse_ManualReport(void);
void Pulse_ManualDebug(void);
void Pulse_ManualReset(void);
void Pulse_ManualEnd(void);
/******************************************************************************/
#endif
/*************************************END**************************************/
