/*******************************************************************************
Copyright: 
File name: common.h
Description: 常用相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
#define DEVICE_ID               0x01    //NB霍尔阀控表	                  
//#define SOFTWARE_VERSION        100     //软件版本

#define SampleDataEachSize      9            //采样数据每条大小
#define SampleDataMax           200          //采样数据最大条数 1小时一次，可存储50天
/*******************************************************************************
数据类型定义
*******************************************************************************/

enum Device_Status_EN
{
  SLEEP,  //睡眠
  WAKE     //运行
};
enum Device_Event_EN
{
  FREE,  //释放
  PEND   //挂起
};

  
/*循环队列结构体定义*/
typedef struct    
{
  uint16_t Total;               //总数
  uint16_t Front;               //首址
  uint16_t Rear;                //尾址
}CircularQueue_TypeDef;

/*时间结构体定义*/
typedef struct    
{
  uint8_t Year;         
  uint8_t Month;           
  uint8_t Day;     
  uint8_t Hour;         
  uint8_t Minute;           
  uint8_t Second;  
}Time_TypeDef;

/*水量共用体类型*/
typedef union                                            
{
  uint32_t flow32;
  uint8_t flow8[4];
}FlowUnion; 
/*设备单元联合体定义*/
typedef union 
{ 
  uint16_t All;
  struct
  {
    uint16_t PeriodicReport:1;   
    uint16_t PeriodicSample:1;
    uint16_t ManualWake:1;
    uint16_t ManualReport:1;
    uint16_t ManualSample:1;
    uint16_t ManualDebug:1; 
    uint16_t AlarmReport:1;
    uint16_t ValveCtrl:1;
    uint16_t MaintainValve:1;
    uint16_t DayFreeze:1;
    uint16_t MonthFreeze:1;
    uint16_t WakeTimeoutRst:1;
    uint16_t ReportTimeoutRst:1;
    uint16_t ManualRst:1;
    uint16_t RereadParas:1;
    uint16_t Reverse:1;
  };
}Device_UnitUnion;
/*设备状态联合体定义*/
typedef union 
{ 
  uint16_t All;
  struct
  {
    uint16_t Interfere:1;       //磁干扰告警，0:正常,1:告警
    uint16_t LowVoltage:1;      //低压告警，0:正常,1:告警
    uint16_t Separation:1;      //分离告警，0:正常,1:告警
    uint16_t Sensor1:1;         //传感器1告警，0:正常,1:告警
    uint16_t Sensor2:1;         //传感器2告警，0:正常,1:告警
    uint16_t Sensor3:1;         //传感器3告警，0:正常,1:告警
    uint16_t OverFlow:1;        //过流告警，0:正常,1:告警
    uint16_t HighPress:1;       //高压告警，0:正常,1:告警
    uint16_t LowPress:1;        //低压告警，0:正常,1:告警
    uint16_t EmptyPipe:1;       //空管告警，0:正常,1:告警
    uint16_t Excitation:1;      //励磁告警，0:正常,1:告警
    uint16_t Electrode:1;       //电极告警，0:正常,1:告警
    uint16_t MeterLose:1;       //基表失联告警，0:正常,1:告警
    uint16_t Memory:1;          //存储器告警，0:正常,1:告警
    uint16_t Reverse:1;         //预留
  };
}Device_AlarmUnion;
/*采样结构体定义*/
typedef  struct
{
  CircularQueue_TypeDef Queue;
  uint16_t Frequency;
  uint16_t Timer;
  bool Valid;
}SampleParas_TypeDef;

/*上报相关参数结构体定义*/
typedef struct 
{ 
  uint16_t Frequency;
  uint8_t StartTimeHour;       //起始时间时位 
  uint8_t StartTimeMinute;     //起始时间分位
  uint16_t DRDuration;          //离散上报时长,m
  bool StartTimeValid;
  uint16_t Timer;               //计时器,m
  uint32_t Timeout;             //超时计时
}ReportParas_TypeDef;

typedef enum 
{
 NORMAL,
 SENSOR1,
 SENSOR2,
 INTERFERE
}SensorError_TypeDef;

/*设备相关参数结构体定义*/
typedef struct 
{ 
  uint16_t WeekTime;                    //运行时间，s
  Device_UnitUnion Mode;                //模式
  Device_UnitUnion Event;               //事件
  Device_AlarmUnion AlarmMark;          //报警标记
  SensorError_TypeDef SensorError;      //传感器故障
  FlowUnion ForwardFlow;                //正向水量
  ReportParas_TypeDef ReportParas;      //上报相关参数
  SampleParas_TypeDef SampleParas;      //采样相关参数
  uint16_t Voltage;                     //电压          
  int8_t Temp;                          //温度
  bool IsRereadParas;                   //重新读取参数
}DevicePara_TypeDef;
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
extern DevicePara_TypeDef DevicePara;  
/*******************************************************************************
外部变量声明区
*******************************************************************************/
/*******************************************************************************
功能代码定义区
*******************************************************************************/
uint8_t Int_to_ASCLL(uint8_t data);
uint8_t ASCLL_to_Int(uint8_t data);
uint8_t BCD_to_Int(uint8_t data);
//char* strnstr(char* str1,char* str2,uint16_t len);
uint8_t Checksum8(uint8_t *buff,uint16_t length);
//uint16_t CRC16_NB(uint8_t* data,uint16_t length);
uint16_t CRC16_Modbus(uint8_t *buff, uint16_t lenth);
//uint8_t XORCheck(uint8_t *buff,uint16_t length);
//uint8_t Byte_Reverse(uint8_t data);
uint16_t GetOffsetTime(uint8_t *buff);
void GetDeviceId(uint8_t *buff);
/******************************************************************************/
#endif
/*************************************END**************************************/