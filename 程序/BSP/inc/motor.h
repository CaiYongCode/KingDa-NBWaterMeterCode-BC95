/*******************************************************************************
Copyright: 
File name: valveCtrl.h
Description: 阀门控制相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
#ifndef __MOTOR_H__
#define __MOTOR_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
//电机电源
#define Motor_PWR_PORT       GPIOB                                 
#define Motor_PWR_Pin        GPIO_Pin_1
#define Motor_PWR_Mode       GPIO_Mode_Out_PP_High_Slow
#define Motor_PWR_Set        GPIO_SetBits(Motor_PWR_PORT,Motor_PWR_Pin);
#define Motor_PWR_Rst        GPIO_ResetBits(Motor_PWR_PORT,Motor_PWR_Pin);
//电机A线
#define Motor_IA_PORT       GPIOB                                 
#define Motor_IA_Pin        GPIO_Pin_0
#define Motor_IA_Mode       GPIO_Mode_Out_PP_Low_Slow
#define Motor_IA_Set        GPIO_SetBits(Motor_IA_PORT,Motor_IA_Pin);
#define Motor_IA_Rst        GPIO_ResetBits(Motor_IA_PORT,Motor_IA_Pin);
//电机B线
#define Motor_IB_PORT       GPIOB                                 
#define Motor_IB_Pin        GPIO_Pin_2
#define Motor_IB_Mode       GPIO_Mode_Out_PP_Low_Slow
#define Motor_IB_Set        GPIO_SetBits(Motor_IB_PORT,Motor_IB_Pin);
#define Motor_IB_Rst        GPIO_ResetBits(Motor_IB_PORT,Motor_IB_Pin);
//电机开限位
#define Motor_OL_PORT       GPIOB                                 
#define Motor_OL_Pin        GPIO_Pin_4
#define Motor_OL_Mode       GPIO_Mode_In_FL_IT
#define Motor_OL_Set        GPIO_SetBits(Motor_OL_PORT,Motor_OL_Pin);
#define Motor_OL_Rst        GPIO_ResetBits(Motor_OL_PORT,Motor_OL_Pin);
#define Motor_OL_Data       GPIO_ReadInputDataBit(Motor_OL_PORT,Motor_OL_Pin)
//电机关限位
#define Motor_CL_PORT       GPIOB                                 
#define Motor_CL_Pin        GPIO_Pin_5
#define Motor_CL_Mode       GPIO_Mode_In_FL_IT
#define Motor_CL_Set        GPIO_SetBits(Motor_CL_PORT,Motor_CL_Pin);
#define Motor_CL_Rst        GPIO_ResetBits(Motor_CL_PORT,Motor_CL_Pin);
#define Motor_CL_Data       GPIO_ReadInputDataBit(Motor_CL_PORT,Motor_CL_Pin)
//电机OCP信号
//#define Motor_OC_PORT       GPIOE                                 
//#define Motor_OC_Pin        GPIO_Pin_5
//#define Motor_OC_Mode       GPIO_Mode_In_PU_IT
//#define Motor_OC_Set        GPIO_SetBits(Motor_OC_PORT,Motor_OC_Pin);
//#define Motor_OC_Rst        GPIO_ResetBits(Motor_OC_PORT,Motor_OC_Pin);
//#define Motor_OC_Data       GPIO_ReadInputDataBit(Motor_OC_PORT,Motor_OC_Pin)

/*******************************************************************************
数据类型定义
*******************************************************************************/
typedef enum 
{
  MotorIdle,
  CW , 
  CCW
}MotorDir;       //电机方向

typedef struct 
{
  MotorDir Direction;           //电机方向
  FunctionalState State;        //电机状态
}Motor_TypeDef;  
/*******************************************************************************
外部变量声明区 
*******************************************************************************/
extern Motor_TypeDef Motor;
/*******************************************************************************
函数声明区
*******************************************************************************/
void Motor_Init(void);
void Motor_DeInit(void);
void Motor_ExtiInit(void);
void Motor_ExtiDeInit(void);
void Motor_Run(void);
void Motor_LimitIT(void);
void Motor_OCPIT(void);
/******************************************************************************/
#endif
/*************************************END**************************************/