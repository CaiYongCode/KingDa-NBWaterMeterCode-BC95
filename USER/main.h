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
#define  SOFTWARE_VERSION       10                 //软件版本V1.0

#define  EEPROM_ADD             0X00001000           //EEPROM 初始地址设置
#define  SOFTWARE_VERSION_ADD   (EEPROM_ADD)         //软件版本地址
#define  SERVER_ADD1_EEPROM_ADD (EEPROM_ADD+10)      //IP地址1
#define  SERVER_ADD2_EEPROM_ADD (EEPROM_ADD+20)      //IP地址2
#define  ADD_FLOW_ADD           (EEPROM_ADD+30)      //累积流量地址
#define  HALL_ERROR_ADD         (EEPROM_ADD+35)      //霍尔状态
#define  CJT_188_ADD            (EEPROM_ADD+40)      //188地址存储
#define  ACCOUNT_FLOW_ADD       (EEPROM_ADD+50)      //结算日流量地址
#define  HISTORY_FLOW_ADD       (EEPROM_ADD+55)      //历史流量地址
#define  SETTLEMENT_DATE_ADD    (EEPROM_ADD+110)     //结算日期地址
#define  SAMPLE_FREQUENCY_ADDR  (EEPROM_ADD+111)     //采样频率地址
#define  REPORT_FREQUENCY_ADDR  (EEPROM_ADD+114)     //上报频率地址
#define  BAT_ALARM_ADD          (EEPROM_ADD+116)     //电池报警值地址
#define  BC95_ERROR_RECORD_ADD  (EEPROM_ADD+122)     //BC95联网错误记录地址

#define  SDCF1_ADDR             (EEPROM_ADD+126)      //上1月结算日流量地址
#define  SDCF2_ADDR             (EEPROM_ADD+130)      //上2月结算日流量地址
#define  SDCF3_ADDR             (EEPROM_ADD+134)      //上3月结算日流量地址
#define  SDCF4_ADDR             (EEPROM_ADD+138)      //上4月结算日流量地址
#define  SDCF5_ADDR             (EEPROM_ADD+142)      //上5月结算日流量地址
#define  SDCF6_ADDR             (EEPROM_ADD+146)      //上6月结算日流量地址
#define  SDCF7_ADDR             (EEPROM_ADD+150)      //上7月结算日流量地址
#define  SDCF8_ADDR             (EEPROM_ADD+154)      //上8月结算日流量地址
#define  SDCF9_ADDR             (EEPROM_ADD+158)      //上9月结算日流量地址
#define  SDCF10_ADDR            (EEPROM_ADD+162)      //上10月结算日流量地址
#define  SDCF11_ADDR            (EEPROM_ADD+166)      //上11月结算日流量地址
#define  SDCF12_ADDR            (EEPROM_ADD+170)      //上12月结算日流量地址
#define  SDCF13_ADDR            (EEPROM_ADD+174)      //上13月结算日流量地址

//#define  HISTORYL_READ_ADDR     (EEPROM_ADD+180)      //历史数据读取索引地址
#define  HISTORYL_SAVE_ADDR     (EEPROM_ADD+180)      //历史数据保存索引地址
#define  HISTORYL_DATA_ADDR     (EEPROM_ADD+181)      //历史数据地址

//#define  VERSION        *((const unsigned char *)(SOFTWARE_VERSION_ADD))
//#define  IP1            ((const union Network_Par_Uni *)(SERVER_ADD1_EEPROM_ADD))  //IP地址1
//#define  IP2            ((const union Network_Par_Uni *)(SERVER_ADD2_EEPROM_ADD))  //IP地址2
//#define  ADD_FLOW       ((const union flow_union *)(ADD_FLOW_ADD))                //累积流量
//#define  CAL_STATE      ((const enum Cal_State_En *)(CAL_STATE_ADD))              //霍尔状态表
//#define  ACCOUNT_FLOW   ((const union flow_union *)(ACCOUNT_FLOW_ADD))            //结算日流量
//#define  HISTORY_FLOW   ((const union flow_union *)(HISTORY_FLOW_ADD))           //历史流量
//#define  SET_DATE       ((const unsigned char *)(SET_DATE_ADD))                  //结算日日期
//#define  READ_DATA      ((const unsigned char *)(READ_DATE_ADD))                 //抄表日日期
//#define  BAT_ALARM      ((const unsigned short *)(BAT_ALARM_ADD))                 //电池报警值
//#define  UP_DATA        ((const struct Up_Date_Str *)(UP_DATE_ADD))               //上传时间
/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
//struct Network_Par_Str
//{
//  unsigned char IP[4];   //连接IP
//  unsigned short Port;   //连接端口
//};
//
//union Network_Par_Uni
//{
//  struct Network_Par_Str Str;
//  unsigned char Byte[6];
//};
//
//struct Up_Date_Str
//{
//  unsigned char Day;
//  unsigned char Hour;
//};
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/

/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
void Led_Green_ON(void);
void Led_Green_OFF(void);
void Sleep(void);
void IWDG_INIT(void);
/********************************************************************************************************/
#endif

/******************************************END********************************************************/
