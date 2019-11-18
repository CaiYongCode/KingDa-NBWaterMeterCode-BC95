/*********************************************************************************************************
//概述：
//作者：随风飘跃    时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/

#ifndef __MAIN_H__
#define __MAIN_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
//#define  APP_VERSION       "NB_APP_V1.0"                 //软件版本V1.0
//#define  APP_VALID          0xAA                        //APP应用程序有效
////用户代码的起始地址
//#define APP_START_ADDR     ((uint32_t)0xD000)

#define  EEPROM_ADDR                             0x00001000              //EEPROM 初始地址设置
#define  CJT_188_ADD                            (EEPROM_ADDR+2)      //188地址存储
#define  ADD_FLOW_ADD                           (EEPROM_ADDR+9)      //累积流量地址
#define  SETTLE_DATE_ADD                        (EEPROM_ADDR+13)     //结算日期地址
#define  SAMPLE_FREQUENCY_ADDR                  (EEPROM_ADDR+14)     //采样频率地址
#define  REPORT_FREQUENCY_ADDR                  (EEPROM_ADDR+16)     //上报频率地址
#define  FIRST_REPORT_ADDR                      (EEPROM_ADDR+18)     //首发时间
#define  BC95_ERROR_RECORD_ADD                  (EEPROM_ADDR+22)     //BC95联网错误记录地址

#define  SDCF1_ADDR                             (EEPROM_ADDR+25)      //上1月结算日流量地址
#define  SDCF2_ADDR                             (EEPROM_ADDR+29)      //上2月结算日流量地址
#define  SDCF3_ADDR                             (EEPROM_ADDR+33)      //上3月结算日流量地址
#define  SDCF4_ADDR                             (EEPROM_ADDR+37)      //上4月结算日流量地址
#define  SDCF5_ADDR                             (EEPROM_ADDR+41)      //上5月结算日流量地址
#define  SDCF6_ADDR                             (EEPROM_ADDR+45)      //上6月结算日流量地址
#define  SDCF7_ADDR                             (EEPROM_ADDR+49)      //上7月结算日流量地址
#define  SDCF8_ADDR                             (EEPROM_ADDR+53)      //上8月结算日流量地址
#define  SDCF9_ADDR                             (EEPROM_ADDR+57)     //上9月结算日流量地址
#define  SDCF10_ADDR                            (EEPROM_ADDR+61)     //上10月结算日流量地址
#define  SDCF11_ADDR                            (EEPROM_ADDR+65)     //上11月结算日流量地址
#define  SDCF12_ADDR                            (EEPROM_ADDR+69)     //上12月结算日流量地址
#define  SDCF13_ADDR                            (EEPROM_ADDR+73)     //上13月结算日流量地址

#define  DEBUG_RESET_RECORD_ADDR                (EEPROM_ADDR+80)     //复位记录地址
#define  DEBUG_REPORT_STATISTICS_ADDR           (EEPROM_ADDR+88)     //上传统计地址
#define  DEBUG_REPORT_RECORD_ADDR               (EEPROM_ADDR+94)     //上传记录地址

#define  HISTORY_DATA_FRONT_ADDR                (EEPROM_ADDR+128)      //历史数据头
#define  HISTORY_DATA_REAR_ADDR                 (EEPROM_ADDR+129)      //历史数据尾
#define  HISTORY_DATA_TOTAL_ADDR                (EEPROM_ADDR+130)      //历史数据总数
#define  HISTORY_DATA_START_ADDR                (EEPROM_ADDR+131)      //历史数据起始地址






/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/

/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/

/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
void Event_Process(void);
/********************************************************************************************************/
#endif

/******************************************END********************************************************/
