/*********************************************************************************************************
//概述：
//作者：随风飘跃    时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/
#ifndef __INCLUDE_H__
#define __INCLUDE_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "stm8l15x.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_rtc.h"
#include "stm8l15x_itc.h"
#include "stm8l15x_pwr.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_lcd.h"
#include "stm8l15x_exti.h"
#include "stm8l15x_tim1.h"
#include "stm8l15x_tim2.h"
#include "stm8l15x_tim3.h"
#include "stm8l15x_tim4.h"
#include "stm8l15x_adc.h"
#include "stm8l15x_flash.h"
#include "main.h"
#include "mcu_init.h"
#include "Pulse_Acquire.h"
#include "save.h"
#include "rtc.h"
#include "uart.h"
#include "protocol.h"
#include "CJT-188-2004.h"
#include "BC95.h"
#include "Sys_timer.h" 
#include "string.h"
#include "Globaldata.h"
#include "Temperature.h"
#include "stdlib.h"
#include "Debug.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
/**********************端口声明**************************/

/***************低功耗引脚设置****************/
#define GPIO_LOW_POWER_MODE  GPIO_Mode_In_FL_No_IT

#define Cai1_PORT          GPIOD                                 //霍尔计数 cai1
#define Cai1_Pin           GPIO_Pin_0
#define Cai1_Mode          GPIO_Mode_In_FL_IT
#define Cai1               GPIO_ReadInputDataBit (Cai1_PORT,Cai1_Pin)

#define Cai2_PORT          GPIOD                                 //霍尔计数 cai2
#define Cai2_Pin           GPIO_Pin_1
#define Cai2_Mode          GPIO_Mode_In_FL_IT
#define Cai2               GPIO_ReadInputDataBit (Cai2_PORT,Cai2_Pin)

#define Weak_Up_PORT       GPIOF                                 //唤醒霍尔
#define Weak_Up_Pin        GPIO_Pin_0
#define Weak_Up_Mode       GPIO_Mode_In_FL_IT
#define Weak_Up            GPIO_ReadInputDataBit (Weak_Up_PORT,Weak_Up_Pin)

//
///*******************led引脚设置*****************/
//#define Led_Green_PORT     GPIOD                               //绿色LED
//#define Led_Green_Pin      GPIO_Pin_6
//#define Led_Green_Mode     GPIO_Mode_Out_PP_Low_Slow
//#define Led_Green_SET      GPIO_SetBits (Led_Green_PORT,Led_Green_Pin)
//#define Led_Green_RESET    GPIO_ResetBits (Led_Green_PORT, Led_Green_Pin)
//
//#define Led_Yellow_PORT    GPIOD                             //黄色LED
//#define Led_Yellow_Pin     GPIO_Pin_7
//#define Led_Yellow_Mode    GPIO_Mode_Out_PP_Low_Slow
//#define Led_Yellow_SET     GPIO_SetBits (Led_Yellow_PORT,Led_Yellow_Pin)
//#define Led_Yellow_RESET   GPIO_ResetBits (Led_Yellow_PORT, Led_Yellow_Pin)
//
///*******************ADC引脚定义************************/
//
//#define NTC_Temp_PORT      GPIOA                                 //NTC adc引脚输入端
//#define NTC_Temp_Pin       GPIO_Pin_5
//#define NTC_Temp_Mode      GPIO_Mode_In_PU_No_IT
//#define NTC_Temp           GPIO_ReadInputDataBit (NTC_Temp_PORT,NTC_Temp_Pin)
//#define NTC_Temp_Channel   ADC_Channel_1
//
///*******************模块引脚设置********************/
//
//#define _RI_PORT       GPIOE                                 //振铃输入引脚
//#define _RI_Pin        GPIO_Pin_0
//#define _RI_Mode       GPIO_Mode_In_PU_No_IT
//#define _RI            GPIO_ReadInputDataBit (_RI_PORT,_RI_Pin)
//
//#define _RESET_PORT    GPIOE                               //复位信号输出
//#define _RESET_Pin     GPIO_Pin_1
//#define _RESET_Mode    GPIO_Mode_Out_PP_Low_Slow
//#define _RESET_SET     GPIO_SetBits (_RESET_PORT,_RESET_Pin)
//#define _RESET_RESET   GPIO_ResetBits (_RESET_PORT, _RESET_Pin)
//
//#define _PWR_EN_PORT   GPIOE                             //
//#define _PWR_EN_Pin    GPIO_Pin_2
//#define _PWR_EN_Mode   GPIO_Mode_Out_PP_Low_Slow
//#define _PWR_EN_SET    GPIO_SetBits (_PWR_EN_PORT,_PWR_EN_Pin)
//#define _PWR_EN_RESET  GPIO_ResetBits (_PWR_EN_PORT, _PWR_EN_Pin)
//
///**********************串口引脚设置**********************/
//#define UART2_TX_PORT      GPIOE                                 //串口2TXD
//#define UART2_TX_Pin       GPIO_Pin_4
//#define UART2_TX_Mode      GPIO_Mode_Out_PP_High_Fast
//#define UART2_TX_SET       GPIO_SetBits (UART2_TX_PORT,UART2_TX_Pin)
//#define UART2_TX_RESET     GPIO_ResetBits (UART2_TX_PORT, UART2_TX_Pin)
//
//#define UART2_RX_PORT      GPIOE                                 //串口2RXD
//#define UART2_RX_Pin       GPIO_Pin_3
//#define UART2_RX_Mode      GPIO_Mode_In_PU_No_IT
//#define UART2_RX           GPIO_ReadInputDataBit (UART2_RX_PORT,UART2_RX_Pin)
//
//
//#define UART3_TX_PORT      GPIOE                                 //串口3TXD
//#define UART3_TX_Pin       GPIO_Pin_6
//#define UART3_TX_Mode      GPIO_Mode_Out_PP_High_Fast
//#define UART3_TX_SET       GPIO_SetBits (UART3_TX_PORT,UART3_TX_Pin)
//#define UART3_TX_RESET     GPIO_ResetBits (UART3_TX_PORT, UART3_TX_Pin)
//
//#define UART3_RX_PORT      GPIOE                                 //串口3RXD
//#define UART3_RX_Pin       GPIO_Pin_7
//#define UART3_RX_Mode      GPIO_Mode_In_PU_No_IT
//#define UART3_RX           GPIO_ReadInputDataBit (UART3_RX_PORT,UART3_RX_Pin)


///**********************调试用宏定义**************************/
//#define HARDWARE  10     //硬件版本1.0
//
//#define LOW_POWER 1           //定义是否将至低功耗模式 0否 1是
//
///**********************运行状态宏定义**************************/
//#define RUN_MODE  0         //运行模式
//#define SLEEP_MODE 1         //睡眠模式
//#define MOTOR_MODE 2         //电机运行模式
//#define DE_SLEEP_MODE 3      //延时睡眠模式
//#define UART_MODE 4          //串口活跃模式
///**********************电机状态宏定义**************************/
//#define OPEN_MODE 1          //阀门打开
//#define CLOSE_MODE 2         //阀门关闭
//#define HALF_MODE 3          //阀门半开
///**********************刷卡的状态**************************/
//#define CARD_WATE 0          //等待读卡
//#define CARD_BEGIN 1         //开始读卡
//#define CARD_OVER 2          //结束读卡
/**********************EEPROM宏定义**************************/
//#define EEPROM_ADD           0X00001000     //EEPROM 初始地址设置
//#define USER_DATA_ADD        EEPROM_ADD  //用户数据区地址
//#define OPEN_USER_ADD        EEPROM_ADD  //开户标志存储地址
//#define CLEAR_FLAG_ADD       (EEPROM_ADD+1)//清零标志地址
//#define USER_NUM_ADD         (EEPROM_ADD+2)//用户号地址
//
//#define SURPLUS_FLOW_ADD     (EEPROM_ADD+9)//剩余流量地址
//#define BUY_COUNT_ADD        (EEPROM_ADD+13)//购买次数地址
//#define LIMIT_FLOW_ADD       (EEPROM_ADD+14)//限购流量地址
//#define DIS_ALARM_ADD        (EEPROM_ADD+16)//显示报警
//#define CLO_ALARM_ADD        (EEPROM_ADD+17)//关阀报警
//#define SUBLIST_ADD          (EEPROM_ADD+18)//子表号地址
//#define MINUS_FLAG_ADD       (EEPROM_ADD+19)//负数标志
//#define ADD_BUY_ADD          (EEPROM_ADD+20)//累积购买地址
//
//#define SYS_DATA_ADD         (EEPROM_ADD+251)//系统数据使能
//#define PASSWORD_MAIN_1_ADD  (EEPROM_ADD+251)//主密码1使能
//#define PASSWORD_MAIN_2_ADD  (EEPROM_ADD+252)//主密码2使能
//#define PASSWORD_SLAVE_1_ADD (EEPROM_ADD+253)//备选密码2使能
//#define PASSWORD_SLAVE_2_ADD (EEPROM_ADD+254)//备选密码2使能
//#define HARDWARE_ADD         (EEPROM_ADD+255)//硬件版本
/***********************EEPROM映射地址常量********************************/
//#define USER_DATA    ((union User_Data_Uni *)(USER_DATA_ADD))  //用户数据区总结构体
//#define OPEN_USER    ((bool *)(OPEN_USER_ADD))                 //开户标志
//#define CLEAR_FLAG   ((bool *)(CLEAR_FLAG_ADD))                //清零标志
//#define USER_NUM     ((unsigned char *)(USER_NUM_ADD))       //开户用户号
//#define ADD_FLOW     ((union flow_union *)(ADD_FLOW_ADD))      //累积流量
//#define SURPLUS_FLOW ((union flow_union *)(SURPLUS_FLOW_ADD))  //剩余流量
//#define BUY_COUNT    ((unsigned char *)(BUY_COUNT_ADD))       //购买次数
//#define LIMIT_FLOW   ((unsigned short *)(LIMIT_FLOW_ADD))     //限购量
//#define DIS_ALARM    ((unsigned char *)(DIS_ALARM_ADD))       //显示报警
//#define CLO_ALARM    ((unsigned char *)(CLO_ALARM_ADD))       //关阀报警
//#define SUBLIST      ((unsigned char *)(SUBLIST_ADD))         //子表号
//#define MINUS_FLAG   ((bool *)(MINUS_FLAG_ADD))                //负数标志
//#define ADD_BUY      ((union flow_union *)(ADD_BUY_ADD))        //累积购买   
//
//#define SYS_DATA     ((struct Sys_Data_Str *)(SYS_DATA_ADD))  //系统数据区总结构体
//
//#define PASSWORD_MAIN_1  ((FunctionalState *)(PASSWORD_MAIN_1_ADD))   //主加密1使能
//#define PASSWORD_MAIN_2  ((FunctionalState *)(PASSWORD_MAIN_2_ADD))   //主加密2使能
//#define PASSWORD_SLAVE_1 ((FunctionalState *)(PASSWORD_SLAVE_1_ADD))   //从加密2使能
//#define PASSWORD_SLAVE_2 ((FunctionalState *)(PASSWORD_SLAVE_2_ADD))   //从加密2使能
//#define HARDWARE_DATA    ((unsigned char *)(HARDWARE_ADD))          //硬件版本说明

/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
//union card_union
//{                                                           //用于存储射频卡的数据共用体
//	 unsigned long int data32[7];
//	 unsigned char data8[28];
//}; 
//union user_id                                            //用户ID信息共用体
//{
//	 unsigned int id16;
//	 unsigned char id8[2];
//};
//union add_buy                                               //购买总量和限制购买共用体
//{
//	 unsigned int buy16;
//	 unsigned char buy8[2];
//};
//union buy_num                                               //购买次数共用体
//{
//	 unsigned int num16;
//	 unsigned char num8[2];
//};
//union Error_Data
//{
//  unsigned char Error_Data8;
//  struct
//  {
//    unsigned char Close_Timeout:1;//关阀超时
//    unsigned char Close_Overcurrent:1;//关阀过流
//    unsigned char Valve_Leak:1;     //阀门漏水
//    unsigned char Magnetism:1;      //磁干扰
//    unsigned char Low_Power:1;      //欠压
//    unsigned char bad_Switch:1;     //干簧管损坏
//  }Error_Bit;
//};
//union User_Data_Uni
//{
//  unsigned char Data8[20];
//  struct
//  {
//    bool Open_Falg;//开户标志
//    bool Clear_Falg;//清零标志
//    unsigned char User_Num[3];//用户号
//    union flow_union Add_Flow;//累积流量
//    union flow_union Surplus_Flow;//剩余流量
//    unsigned char Buy_Count;//购买次数计数
//    unsigned short Limit_Flow;//限购流量
//    unsigned char Dis_Alarm;//显示报警量
//    unsigned char Clo_Alarm;//关阀报警量
//    unsigned char Sublist;//子表号
//    bool Minus_Falg;//负数标志位
//  }Str;
//};
//struct Sys_Data_Str
//{
//  FunctionalState Password_Main_1;//主加密1使能
//  FunctionalState Password_Main_2;//主加密2使能
//  FunctionalState Slave_Main_1;   //备选加密1使能
//  FunctionalState Slave_Main_2;   //备选加密1使能
//  unsigned char Hardware;      //硬件版本说明
//};

/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/
/*********************************************************************************************************
函数声明区
*********************************************************************************************************/

/********************************************************************************************************/
#endif

/******************************************END********************************************************/
