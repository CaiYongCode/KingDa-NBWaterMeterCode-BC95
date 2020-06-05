/*******************************************************************************
Copyright: 
File name: uplink_protocol.c
Description: 上行通信协议相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
#ifndef  __DATA_PROCESS_H
#define  __DATA_PROCESS_H
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
/*MRS256地址分配 0x0000--0x7FFF*/
#define  INTERNAL_EEPROM_START_ADDR             0x00001000              //EEPROM 起始地址
#define  INTERNAL_EEPROM_END_ADDR               0x000017FF              //EEPROM 结束地址

#define  METER_NUMBER_ADDR                      (INTERNAL_EEPROM_START_ADDR+2)      //表号地址，7字节
#define  FORWARD_FLOW_ADDR                      (INTERNAL_EEPROM_START_ADDR+9)      //累积流量地址，4字节
#define  SETTLE_DATE_ADD                        (INTERNAL_EEPROM_START_ADDR+13)     //结算日期地址，1字节
#define  SAMPLE_FREQUENCY_ADDR                  (INTERNAL_EEPROM_START_ADDR+14)     //采样频率地址，2字节
#define  SAMPLE_DATA_TOTAL_ADDR                 (INTERNAL_EEPROM_START_ADDR+16)     //采样数据总数，2字节
#define  SAMPLE_DATA_FRONT_ADDR                 (INTERNAL_EEPROM_START_ADDR+18)     //采样数据头，2字节
#define  SAMPLE_DATA_REAR_ADDR                  (INTERNAL_EEPROM_START_ADDR+20)     //采样数据尾，2字节
#define  REPORT_FREQUENCY_ADDR                  (INTERNAL_EEPROM_START_ADDR+22)     //上报频率地址，2字节
#define  FIRST_REPORT_ADDR                      (INTERNAL_EEPROM_START_ADDR+24)     //首发时间，4字节
#define  BC95_ERROR_RECORD_ADD                  (INTERNAL_EEPROM_START_ADDR+28)     //BC95联网错误记录地址，1字节

#define  IMEI_ADDR                              (INTERNAL_EEPROM_START_ADDR+30)     //IMEI地址，15字节   

#define  DEBUG_RESET_RECORD_ADDR                (INTERNAL_EEPROM_START_ADDR+80)     //复位记录地址，8字节
#define  DEBUG_REPORT_STATISTICS_ADDR           (INTERNAL_EEPROM_START_ADDR+88)     //上传统计地址，6字节
#define  DEBUG_REPORT_RECORD_ADDR               (INTERNAL_EEPROM_START_ADDR+94)     //上传记录地址，10字节
#define  DEBUG_RESET_WAKE_TIMEOUT_ADDR          (INTERNAL_EEPROM_START_ADDR+104)     //唤醒超时复位记录地址，6字节
#define  DEBUG_RESET_REPORT_TIMEOUT_ADDR        (INTERNAL_EEPROM_START_ADDR+110)     //上报超时复位记录地址，6字节

#define  SAMPLE_DATA_START_ADDR                (INTERNAL_EEPROM_START_ADDR+120)      //历史数据起始地址

/*******************************************************************************
管脚定义
*******************************************************************************/
/*******************************************************************************
数据类型定义
*******************************************************************************/
/*******************************************************************************
外部变量声明区
*******************************************************************************/
/*******************************************************************************
函数声明区
*******************************************************************************/
void DataProcess_ReadData(uint32_t addr, uint8_t *buff, uint16_t length);
void DataProcess_WriteData(uint32_t addr, uint8_t *buff, uint16_t length);
void DataProcess_Clear64Bytes(void);
void DataProcess_WriteFlow(void);
void DataProcess_WriteIMEI(void);
void DataProcess_CheckRereadParas(void);
void DataProcess_ReadDevicePara(void);
void DataProcess_ReadReportParas(void);
void DataProcess_ReadSampleParas(void);
void DataPocess_WriteSampleData(void);
void DataPocess_ReadSampleData(uint8_t *buff,uint8_t number);
void DataPocess_ClearSampleData(uint8_t number);
/*************************************DEBUG************************************/
void DataPocess_WriteDebugResetRecord(void);
void DataPocess_ReadDebugResetRecord(uint8_t *buff);
void DataPocess_WriteDebugReportStatistics(uint8_t flag);
void DataPocess_ReadDebugReportStatistics(uint8_t *buff);
void DataPocess_WriteDebugReportRecord(uint8_t flag);
void DataPocess_ReadDebugReportRecord(uint8_t *buff);
void DataPocess_WriteWakeTimeoutResetRecord(void);
void DataPocess_WriteReportTimeoutResetRecord(void);
/******************************************************************************/
#endif
/*************************************END**************************************/