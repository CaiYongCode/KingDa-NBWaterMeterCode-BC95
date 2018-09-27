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
#define  APP_VALID          0xAA                        //APP应用程序有效
//用户代码的起始地址
#define APP_START_ADDR     ((uint32_t)0xD000)

#define  EEPROM_ADD                             0x00001000              //EEPROM 初始地址设置
#define  INTERRUPT_VECTOR_ADD                   (EEPROM_ADD)             //中断向量表存储地址
#define  APP_VERSION_ADD                        (EEPROM_ADD+128)        //应用程序软件版本地址
#define  APP_VALID_ADD                          (EEPROM_ADD+128+12)      //应用程序有效标志地址
#define  Upgrade_Process_ADD                    (EEPROM_ADD+128+23)      //升级进程地址
#define  UPGRADE_VERSION_ADD                    (EEPROM_ADD+128+24)      //升级程序软件版本地址
#define  UPGRADE_PACKAGE_SINGLE_SIZE            (EEPROM_ADD+128+36)      //升级包大小
#define  UPGRADE_PACKAGE_TOTAL_NUMBER           (EEPROM_ADD+128+38)      //升级包总数
#define  UPGRADE_PACKAGE_CHECK_CODE             (EEPROM_ADD+128+40)      //升级包校验码

#define  CJT_188_ADD                            (EEPROM_ADD+128+42)      //188地址存储
#define  ADD_FLOW_ADD                           (EEPROM_ADD+128+49)      //累积流量地址
#define  SETTLE_DATE_ADD                        (EEPROM_ADD+128+53)     //结算日期地址
#define  SAMPLE_FREQUENCY_ADDR                  (EEPROM_ADD+128+54)     //采样频率地址
#define  REPORT_FREQUENCY_ADDR                  (EEPROM_ADD+128+56)     //上报频率地址
#define  BAT_ALARM_ADD                          (EEPROM_ADD+128+58)     //电池报警值地址
#define  BC95_ERROR_RECORD_ADD                  (EEPROM_ADD+128+60)     //BC95联网错误记录地址
#define  HALL_ERROR_ADD                         (EEPROM_ADD+128+61)      //霍尔状态

#define  SDCF1_ADDR                             (EEPROM_ADD+128+65)      //上1月结算日流量地址
#define  SDCF2_ADDR                             (EEPROM_ADD+128+69)      //上2月结算日流量地址
#define  SDCF3_ADDR                             (EEPROM_ADD+128+73)      //上3月结算日流量地址
#define  SDCF4_ADDR                             (EEPROM_ADD+128+77)      //上4月结算日流量地址
#define  SDCF5_ADDR                             (EEPROM_ADD+128+81)      //上5月结算日流量地址
#define  SDCF6_ADDR                             (EEPROM_ADD+128+85)      //上6月结算日流量地址
#define  SDCF7_ADDR                             (EEPROM_ADD+128+89)      //上7月结算日流量地址
#define  SDCF8_ADDR                             (EEPROM_ADD+128+93)      //上8月结算日流量地址
#define  SDCF9_ADDR                             (EEPROM_ADD+128+97)     //上9月结算日流量地址
#define  SDCF10_ADDR                            (EEPROM_ADD+128+101)     //上10月结算日流量地址
#define  SDCF11_ADDR                            (EEPROM_ADD+128+105)     //上11月结算日流量地址
#define  SDCF12_ADDR                            (EEPROM_ADD+128+109)     //上12月结算日流量地址
#define  SDCF13_ADDR                            (EEPROM_ADD+128+113)     //上13月结算日流量地址


#define  HISTORYL_SAVE_ADDR     (EEPROM_ADD+256)      //历史数据保存索引地址
#define  HISTORYL_DATA_ADDR     (EEPROM_ADD+256)      //历史数据地址






/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/

/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/

/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
void Sleep(void);
void IWDG_INIT(void);
/********************************************************************************************************/
#endif

/******************************************END********************************************************/
