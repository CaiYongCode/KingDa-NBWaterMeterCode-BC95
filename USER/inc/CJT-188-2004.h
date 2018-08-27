/*********************************************************************************************************
//概述：
//作者：大胡子书生     时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/
#ifndef  __CJT_188_2004_H
#define  __CJT_188_2004_H
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
#define PNULL  (void*)(0x0000)

#define  Locall_MeterType     ColdWaterMeter
#define  Locall_FactoryID     0x0000//('K' *10) + 'D'



#define  CJT_188_Preamble                0xFE
#define  CJT_188_PreambleLength          2
#define  CJT_188_StartCharacter          0x68
#define  CJT_188_Pause                   0x16


#define  CTR_ReadData_ASK       0x01          //读数据 （请求）
#define  CTR_ReadData_ACK       0x81          //读数据 （应答）
#define  CTR_ReadData_ERR       0xC1          //读数据 （错误）

#define  CTR_ReadVerNo_ASK      0x09          //读秘钥版本号 （请求）
#define  CTR_ReadVerNo_ACK      0x89          //读秘钥版本号 （应答）
#define  CTR_ReadVerNo_ERR      0xC9          //读秘钥版本号 （错误）

#define  CTR_ReadAddress_ASK    0x03          //读地址 （请求）
#define  CTR_ReadAddress_ACK    0x83          //读地址 （应答）
#define  CTR_ReadAddress_ERR    0xC3          //读地址 （错误）

#define  CTR_WriteData_ASK      0x04          //写数据 （请求）
#define  CTR_WriteData_ACK      0x84          //写数据 （应答）
#define  CTR_WriteData_ERR      0xC4          //写数据 （错误）

#define  CTR_WriteAddress_ASK    0x15          //写地址 （请求）
#define  CTR_WriteAddress_ACK    0x95          //写地址 （应答）
#define  CTR_WriteAddress_ERR    0xD5          //写地址 （错误）

#define  CTR_WriteOffset_ASK     0x16          //写机电同步数据（请求）
#define  CTR_WriteOffset_ACK     0x96          //写机电同步数据 （应答）
#define  CTR_WriteOffset_ERR     0xD6          //写机电同步数据 （错误）

#define  DI_ReadData          0x901F      //计量数据
#define  DI_ReadHistData_1    0xD120      //历史计量数据1
#define  DI_ReadHistData_2    0xD121      //历史计量数据2
#define  DI_ReadHistData_3    0xD122      //历史计量数据3
#define  DI_ReadHistData_4    0xD123      //历史计量数据4
#define  DI_ReadHistData_5    0xD124      //历史计量数据5
#define  DI_ReadHistData_6    0xD125      //历史计量数据6
#define  DI_ReadHistData_7    0xD126      //历史计量数据7
#define  DI_ReadHistData_8    0xD127      //历史计量数据8
#define  DI_ReadHistData_9    0xD128      //历史计量数据9
#define  DI_ReadHistData_10   0xD129      //历史计量数据10
#define  DI_ReadHistData_11   0xD12A      //历史计量数据11
#define  DI_ReadHistData_12   0xD12B      //历史计量数据12
#define  DI_ReadPriceList     0x8102      //读价格表
#define  DI_ReadSelDate       0x8103      //读结算日
#define  DI_ReadRecordDate    0x8104      //读抄表日
#define  DI_ReadRMoney        0x8105      //读购入金额
#define  DI_ReadVerNo         0x8106      //读秘钥版本号
#define  DI_ReadTemp          0x8108      //读表内温度
#define  DI_ReadAddress       0x810A      //读地址
#define  DI_ReadIP1           0x8209      //读取IP1
#define  DI_ReadIP2           0x820A      //读取IP2
#define  DI_ReadBattey        0x820B      //读取电池电压
#define  DI_ReadBatteyAlarm   0x820C      //读低电压报警值
#define  DI_ReadUpdataTime    0x820D      //读上传时间
#define  DI_ReadRSSI          0x820E      //读信号强度S

#define  DI_WritePriceList     0xA010      //写价格表
#define  DI_WriteSelDate       0xA011      //写结算日期
#define  DI_WriteRecordDate    0xA012      //写抄表日
#define  DI_WriteRMoney        0xA013      //读购入金额
#define  DI_WriteSecretKey     0xA014      //写秘钥版本号
#define  DI_WriteTime          0xA015      //写标准时间
#define  DI_WriteValveState    0xA017      //写阀门控制
#define  DI_Lock               0xA019      //出厂启用
#define  DI_WriteAddress       0xA018      //写地址
#define  DI_WriteOffset        0xA016      //写机电同步
#define  DI_WriteIP1           0xA201      //设置上传IP1
#define  DI_WriteIP2           0xA202      //设置上传IP2
#define  DI_WriteBatteyAlarm   0xA203      //设置电池报警值
#define  DI_WriteUpdataTime    0xA204      //设置上传周期
#define  DI_AotoUpData         0xA205      //设置自动上传数据

#define  CJT8_188ValveOpenCmd        0x55     //开 阀 控 制 操作 :55H
#define  CJT8_188ValveCloseCmd       0x99     //关 阀 控 制 操作 :99H
#define  CJT8_188ValveMaintainCmd    0xAA     //活 动 阀门 :AAH
#define  CJT8_188ValveHalfCmd        0x77     //阀门半开
/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
typedef unsigned char           CJT_188_SER_Type;
typedef unsigned short          CJT_188_DI_Type;

typedef enum{ASK_CJT_188 = 0, ACK_CJT_188 = 1  }CJT_188_DirType;


  
typedef enum{
  ColdWaterMeter  = 0x10,   //冷水表
  HeatWaterMeter  = 0x11,   //生活热水表
  DrinkWaterMeter = 0x12,   //直饮水表
  RecycledWaterMeter = 0x13,   //中水表
  UnknownMeterType   = 0xAA 
}CJT_188_MeterType;

typedef enum{
  Wh        = 0x02,   //冷水表
  KWh       = 0x05,   //生活热水表
  MWh       = 0x08,
  MWh_100   = 0x0a,
  J         = 0x01,
  KJ        = 0x0B,
  MJ        = 0x0E, 
  GJ        = 0x11,
  GJ_100    = 0x13,
  W         = 0x14,
  KW        = 0x17,
  MW        = 0x1A,
  L         = 0x29,
  m3        = 0x2C,
  L_h       = 0x32,
  m3_h      = 0x35,
  V         = 0x36
}CJT_188_UnitType;

typedef struct{
  unsigned char MeterID[7];
  //unsigned char MeterID[5];
  //unsigned short FactoryID;
}CJT_188_AddresStruct;

typedef struct
{
  CJT_188_UnitType     Flow_Offse_Unit;            //设置机电同步单位
  unsigned char      Flow_Offse[4];              //设置机电同步流量
}CJT_188_WriteOffsetStruct;

typedef union{
  unsigned char Byte;
  struct{
    unsigned char Infr : 6;
    unsigned char CommFlg : 1;
    unsigned char DIR : 1;
  }Bit;
}CJT_188_CTRStruct;

typedef struct 
{
  unsigned char       StartCharacter;
  CJT_188_MeterType    Type;
  CJT_188_AddresStruct Addr;
  CJT_188_CTRStruct    CTR;
  unsigned char       Length;
}CJT_188_FrameHeadStruct;

typedef struct{
  CJT_188_DI_Type   DI;
  CJT_188_SER_Type  SER;
}CJT_188_DataHeadStruct;

typedef union {
   unsigned short Word;
   struct{
      unsigned short Custom :3;     //阀门详细状态
      unsigned short Magnetism :1;   //磁攻击标志 0:无磁攻击，1：有磁攻击
      unsigned short Fault :1;   //故障标志 0:无故障，1：有故障
      unsigned short Reserved :3;   //预留
      unsigned short Valve_State :2;    //阀门状态 00：开， 01 关， 11：异常
      unsigned short Bat_Flg: 1;    //电池电压   0：正常  1：欠压
      unsigned short CN: 2;          //保留
      unsigned short F3: 1;          //厂商自定义3
      unsigned short F2: 1;          //厂商自定义2
      unsigned short F1: 1;          //厂商自定义1
    }Bit;
}CJT_188_ST_Stuct;

//实时时钟格式
typedef struct{
  unsigned char   Sec;
  unsigned char   Min;
  unsigned char   Hour;
  unsigned char   Day;
  unsigned char   Mon;
  unsigned char  Year_L;
  unsigned char  Year_H;
}CJT_188_Time_Struct;

//读数据 格式
typedef struct
{
  unsigned char       Flow_PV[4];              //当前累积流量
  CJT_188_UnitType     Flow_PV_Unit;            //当前累积流量单位
  unsigned char       Flow_Accounts[4];        //结算日累积流量
  CJT_188_UnitType     Flow_Accounts_Unit;      //结算日累积流量单位
  CJT_188_Time_Struct  Time;                    //实时时间
  CJT_188_ST_Stuct     ST;                      //状态ST
}CJT_188_MeterData_Struct;  

//主动上传格式
typedef struct
{
  unsigned char       Flow_PV[4];              //当前累积流量
  CJT_188_UnitType     Flow_PV_Unit;            //当前累积流量单位
  unsigned char       Flow_Accounts[4];        //结算日累积流量
  CJT_188_UnitType     Flow_Accounts_Unit;      //结算日累积流量单位
  CJT_188_Time_Struct  Time;                    //实时时间
  unsigned char      BatteyData[2];              //电池电压
  CJT_188_UnitType     BatteyData_Unit;            //电池电压单位
  unsigned char RSSI;                         //信号强度
  signed char Temp;                            //温度信息
  CJT_188_ST_Stuct     ST;                      //状态ST
}CJT_188_AotuUpData_Struct;  

//读历史 格式
typedef struct
{
  unsigned char       Flow_History[4];              //历史流量
  CJT_188_UnitType     Flow_History_Unit;            //历史流量单位
}CJT_188_HistoryData_Struct;
  
//读温度格式
typedef struct 
{
  signed char Temp;
  CJT_188_ST_Stuct    ST;
}CJT_188_TempData_Struct;

//读IP格式
typedef struct 
{
  unsigned char PORT_L;
  unsigned char PORT_H;
  unsigned char IP_4;
  unsigned char IP_3;
  unsigned char IP_2;
  unsigned char IP_1;
  CJT_188_ST_Stuct    ST;
}CJT_188_IPData_Struct;  

//读电池电压格式
typedef struct
{
  unsigned char      BatteyData[2];              //电池电压
  CJT_188_UnitType     BatteyData_Unit;            //电池电压单位
  CJT_188_ST_Stuct    ST;
}CJT_188BatteyData_Struct;

//读上传周期
typedef struct
{
  unsigned char Hour;
  unsigned char Day;
  CJT_188_ST_Stuct    ST;
}CJT_188UpDate_Struct;

//读信号强度
typedef struct
{
  unsigned char RSSI;
  CJT_188_ST_Stuct    ST;
}CJT_188RSSI_Struct;

//正常应帧格式
typedef struct
{
  CJT_188_DataHeadStruct    DataHead;
  union
  {
   CJT_188_MeterData_Struct MeterData;     //读数据结构体
   CJT_188_HistoryData_Struct HistoryData; //读历史流量结构体
   CJT_188_ST_Stuct         ST;           //ST状态
   unsigned char Read_Date;              //抄表日期
   unsigned char Set_Date;              //结算日日期
   CJT_188_TempData_Struct Temp;          //读温度结构体
   CJT_188_IPData_Struct IP;              //读IP的结构体
   CJT_188BatteyData_Struct Battey;       //读电池的结构体
   CJT_188UpDate_Struct UpDate;           //上传周期结构体
   CJT_188RSSI_Struct RSSI;               //上传信号强度结构体
   CJT_188_AotuUpData_Struct Aotu ;       //主动上传结构体
  }Data;  
}CJT_188_OkACK_Struct;

//错误应答帧格式
typedef struct{
  CJT_188_SER_Type         SER;
  CJT_188_ST_Stuct         ST;
}CJT8_188_ErrACK_Struct;


typedef struct{
  CJT_188_SER_Type         SER;
  CJT_188_ST_Stuct         ST;
  unsigned char           ValveCmd;
}CJT8_188_ValveAsk_Struct;
  
typedef struct{
CJT_188_DataHeadStruct  DataHead;
CJT_188_AddresStruct    Addres;
}CJT_188_Address_OkAckStruct; 

//接收的函数
typedef struct
{
  CJT_188_FrameHeadStruct Head;
  CJT_188_DataHeadStruct  DataHead;
  union
  {
   unsigned char buff[16];              //普通缓冲区
   unsigned char Valve_State;           //阀门状态
   unsigned char Read_Date;             //抄表日期
   unsigned char Set_Date;              //结算日日期
   CJT_188_Time_Struct  Time;             //实时时间
   CJT_188_IPData_Struct IP;              //读IP的结构体
   CJT_188BatteyData_Struct Battey;       //读电池的结构体
   CJT_188UpDate_Struct UpDate;           //上传周期结构体
  }Data;  
}CJT_188_AskFrameData_Struct;

typedef enum
{
  NoErr   = 0,
  Busy = 1,
  Length_err   = 2,
  FramePreamble_err = 3,
  FrameSync_err = 4,
  Verify_err = 5,
  OperateCmd_err    = 6,
  DataRomWrite_err  = 7,
  FrameInvalid   = 8,        //无效数据帧
  CounterFault =9 ,         //计数器故障
  
  PassWordErr = 10,
  SendErr  = 11,
}ErrCodeType;
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/

/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
ErrCodeType CJT_188_2004_InPut (void *pbuff, unsigned length);
ErrCodeType send_AotuUpMeterData (void);
/********************************************************************************************************/
#endif

/******************************************END********************************************************/