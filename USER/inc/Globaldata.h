#ifndef __GLOBALDATA_H__
#define __GLOBALDATA_H__
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "include.h"
/*********************************************************************************
宏定义区
*********************************************************************************/
#define HistoryDataMaxNum       200
#define HistoryDataSize         9
/*********************************************************************************
数据类型定义
*********************************************************************************/
enum Device_Status_EN
{
 SLEEP,  //睡眠
 WAKE    //唤醒
};
enum Device_Event_EN
{
  FREE,  //释放
  PEND   //挂起
};
/*设备单元联合体定义*/
typedef union 
{ 
  uint8_t All;
  struct
  {
    uint8_t bc95:1;   
    uint8_t eeprom:1;
    uint8_t debug:1;
    uint8_t reverse:5;
  };
}Device_UnitUnion;

struct Meter_Parameter_EN
{ 
  Device_UnitUnion Mode;                //模式
  Device_UnitUnion Event;               //事件
  u8 MeterNumber[7];                    //表号
  u16 AlarmVoltage;                     //电池告警电压
  u8 SettleDate;                        //结算日期
  u16 ReportFrequency;                  //上报频率，分
  u16 SampleFrequency;                  //采样频率, 分
  u8 DRStartTimeHour;                   //离散上报起始时间时位 Discrete report
  u8 DRStartTimeMinute;                 //离散上报起始时间分位 Discrete report
  u16 DRDuration;                       //离散上报时长 Discrete report
  bool DRValid;                        //离散上报有效
  u32 ReportRandTime;                   //上报随机时间，秒
  u32 ReportRandTiming;                 //上报随机计时，秒
  u32 ReportTiming;                     //上报计时，秒
  u32 SampleTiming;                     //采样计时，秒
  u32 SaveFlowTiming;                   //保存水量计时，秒
  signed char Temp;                   //温度
  u16 Voltage;                          //电压 
};

typedef struct 
{ 
  u8 Front;     //头
  u8 Rear;      //尾
  u8 Total;     //总数
}History_Data_TypeDef;
/*********************************************************************************
常量定义区
*********************************************************************************/
/*********************************************************************************
公共变量定义区
*********************************************************************************/
extern RTC_TimeTypeDef   RTC_TimeStr;        //RTC时间结构体
extern RTC_DateTypeDef   RTC_DateStr;        //RTC日期结构体
extern struct Meter_Parameter_EN MeterParameter;
extern History_Data_TypeDef HistoryData;
/*********************************************************************************
外部变量声明区
*********************************************************************************/
/*********************************************************************************
私有变量定义区
*********************************************************************************/ 
/*********************************************************************************
测试变量定义区
*********************************************************************************/
/*********************************************************************************
内部函数定义区
*********************************************************************************/
/*********************************************************************************
功能代码定义区
*********************************************************************************/
unsigned short CRC16(unsigned char* data,unsigned short length);
unsigned char Sum_Check(unsigned char *sdata,unsigned short NUM);                //计算和校验
unsigned char Int_to_ASCLL(unsigned char data);
unsigned char ASCLL_to_Int(unsigned char data);
unsigned char BCD_to_Int(unsigned char data);
char* strnstr(char* str1,char* str2,unsigned char len);
unsigned char Check_Sum8(unsigned char *data,unsigned short length);
/*********************************************************************************/
#endif
/******************************************END********************************************************/