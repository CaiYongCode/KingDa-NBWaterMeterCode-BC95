/*********************************************************************************************************
//概述：
//作者：随风飘跃    时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "include.h"
/*********************************************************************************
常量定义区
*********************************************************************************/

/*********************************************************************************
公共变量定义区
*********************************************************************************/
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
/*********************************************************************************
 Function:      //
 Description:   //向ROM写数据
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void WriteRom (unsigned short addr, void *pbuff, unsigned char length)
{
 unsigned char itemp;
 unsigned char cnt;
 unsigned char *p; 
 unsigned short itemp16;
 do
 {FLASH_Unlock(FLASH_MemType_Data); }//开启EEPROM编程
 while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET); 
 itemp = 0;
 p = pbuff;
 cnt =0 ;
 while (itemp < length)
 {
   FLASH_ProgramByte(addr ,p[itemp]);
   itemp16 = 0xffff;
   while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == RESET)
   {
    itemp16 --;
    if(itemp16 <= 1)
    {break;}
   }
   itemp16 = FLASH_ReadByte(addr);
   if(p[itemp] != itemp16)
   {
    if(++cnt > 50)
    {
     FLASH_Lock(FLASH_MemType_Data);
    }
    continue ; 
   }
   else
   {cnt = 0;itemp ++;addr ++;}
 }
 FLASH_Lock(FLASH_MemType_Data);
}
/*********************************************************************************
 Function:      //
 Description:   //读取水表参数
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Read_Meter_Parameter(void)
{
  //读取表号
  MeterParameter.MeterNumber[0] = *((const unsigned char *)(CJT_188_ADD));
  MeterParameter.MeterNumber[1] = *((const unsigned char *)(CJT_188_ADD+1));
  MeterParameter.MeterNumber[2] = *((const unsigned char *)(CJT_188_ADD+2));
  MeterParameter.MeterNumber[3] = *((const unsigned char *)(CJT_188_ADD+3));
  MeterParameter.MeterNumber[4] = *((const unsigned char *)(CJT_188_ADD+4));
  MeterParameter.MeterNumber[5] = *((const unsigned char *)(CJT_188_ADD+5));
  MeterParameter.MeterNumber[6] = *((const unsigned char *)(CJT_188_ADD+6));
  //读取告警电压
  MeterParameter.AlarmVoltage = *((const unsigned short *)(BAT_ALARM_ADD));
  if( (MeterParameter.AlarmVoltage < 300)||(MeterParameter.AlarmVoltage > 360))        //默认告警电压3.00V
  {
    MeterParameter.AlarmVoltage = 300;
  }
  //读取结算日
  MeterParameter.SettleDate = *((const unsigned char *)(SETTLEMENT_DATE_ADD));
  if((MeterParameter.SettleDate == 0)||(MeterParameter.SettleDate > 31))//默认结算日期1号
  {
    MeterParameter.SettleDate = 1;
  }
  //读取上报频率
  MeterParameter.ReportFrequency = *((const unsigned short *)(REPORT_FREQUENCY_ADDR));
  if(MeterParameter.ReportFrequency < 5) //默认上报频率24小时
  {
    MeterParameter.ReportFrequency = 1440;
  }
  //读取采样频率
  MeterParameter.SampleFrequency = *((const unsigned short *)(SAMPLE_FREQUENCY_ADDR));
  if(MeterParameter.SampleFrequency < 15) //默认不采集
  {
    MeterParameter.SampleFrequency = 0;
  }
  
}
/*********************************************************************************
 Function:      //
 Description:   //存储水表参数
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Save_Meter_Parameter(void)
{
  //存储表号
  WriteRom (CJT_188_ADD,MeterParameter.MeterNumber,7);
  //存储电压告警值
  WriteRom (BAT_ALARM_ADD,&MeterParameter.AlarmVoltage,2);
  //存储结算日期
  WriteRom (SETTLEMENT_DATE_ADD,&MeterParameter.SettleDate,1);
  //存储上报频率
  WriteRom (REPORT_FREQUENCY_ADDR,&MeterParameter.ReportFrequency,2);
  //存储采样频率
  WriteRom (SAMPLE_FREQUENCY_ADDR,&MeterParameter.SampleFrequency,2);
}

/*********************************************************************************
 Function:      //
 Description:   //读取累积水量
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Read_ACUM_Flow(unsigned short addr,union flow_union *Flow)       
{
  union flow_union *flow;
  flow = (union flow_union *)(addr);
  Flow->flow32 = flow->flow32;
}
/*********************************************************************************
 Function:      //
 Description:   //存储累积水量
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Save_Add_Flow(u16 addr,union flow_union *Flow)       
{
    WriteRom (addr,Flow->flow8,4);      
}
/*********************************************************************************
 Function:      //
 Description:   //存储结算日累积水量
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Save_SDCF_Flow(union flow_union *Flow)    
{
  union flow_union *Water;
  
  Water = (union flow_union *)(SDCF12_ADDR); 
  WriteRom (SDCF13_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF11_ADDR); 
  WriteRom (SDCF12_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF10_ADDR); 
  WriteRom (SDCF11_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF9_ADDR); 
  WriteRom (SDCF10_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF8_ADDR); 
  WriteRom (SDCF9_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF7_ADDR); 
  WriteRom (SDCF8_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF6_ADDR); 
  WriteRom (SDCF7_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF5_ADDR); 
  WriteRom (SDCF6_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF4_ADDR); 
  WriteRom (SDCF5_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF3_ADDR); 
  WriteRom (SDCF4_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF2_ADDR); 
  WriteRom (SDCF3_ADDR,Water->flow8,4);      //写累积流量
  
  Water = (union flow_union *)(SDCF1_ADDR); 
  WriteRom (SDCF2_ADDR,Water->flow8,4);      //写累积流量
  
  WriteRom (SDCF1_ADDR,Flow->flow8,4);      //写累积流量
}
/*********************************************************************************
 Function:      //
 Description:   //读取BC95错误记录
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Read_BC95_ErrorRecord(void)          
{
  BC95.ErrorRecord = *((const unsigned char *)(BC95_ERROR_RECORD_ADD));
}
/*********************************************************************************
 Function:      //
 Description:   //保存BC95错误记录
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        // 
*********************************************************************************/
void Save_BC95_ErrorRecord(void)    
{
  WriteRom(BC95_ERROR_RECORD_ADD,&BC95.ErrorRecord,1);
}

/*********************************************************************************
 Function:      //
 Description:   //读取历史数据存储索引
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Read_History_Save_Index(void)
{
  HistoryData.SaveIndex = *((const unsigned char *)HISTORYL_SAVE_ADDR);
}
/*********************************************************************************
 Function:      //
 Description:   //读取历史数据
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
unsigned char Read_History_Data(unsigned char* buff)
{
  unsigned char i = 0,j = 0;
  
  if(HistoryData.ReadIndex >= HistoryDataMaxNum)
  {
    HistoryData.ReadIndex = 0;
  }
  i = HistoryData.ReadIndex;

  while(i < HistoryDataMaxNum)
  { 
    for(j = 0;j < 9;j++)
    {    
      buff[j] = *((const unsigned char *)(HISTORYL_DATA_ADDR + i*9+j));
    }
    if( (buff[4] <= 99)                                 //年有效
          &&(1 <= buff[5])&&(buff[5] <= 12)             //月有效
            &&(1 <= buff[6])&&(buff[6] <= 31)           //日有效
              &&(buff[7] <= 23)                         //时有效
                &&(buff[8] <= 59)  )                    //分有效
    {
      HistoryData.ReadIndex = i;
      return 1;
    }
    
    if(i == HistoryData.SaveIndex)
    {
      break;
    }
    i++;
    if(i >= HistoryDataMaxNum)
    {
      i = 0;
    }
  }
  return 0;
}
/*********************************************************************************
 Function:      //
 Description:   //保存历史数据
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Save_History_Data(void)
{
  unsigned char j = 0;
  unsigned char buff[9] = {0};
  
  //若水量与上次相同，则不存储
  for(j = 0;j < 4;j++)
  { 
    buff[j] = *((const unsigned char *)(HISTORYL_DATA_ADDR + HistoryData.SaveIndex*9+j));
  }
  if( (buff[0] == Cal.Water_Data.flow8[0])
        &&(buff[1] == Cal.Water_Data.flow8[1])
          &&(buff[2] == Cal.Water_Data.flow8[2])
            &&(buff[3] == Cal.Water_Data.flow8[3]) )
  {
    return;
  }
  
  memcpy(buff,0,9);
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
  
  buff[0] = Cal.Water_Data.flow8[0];
  buff[1] = Cal.Water_Data.flow8[1]; 
  buff[2] = Cal.Water_Data.flow8[2];
  buff[3] = Cal.Water_Data.flow8[3];
  buff[4] = RTC_DateStr.RTC_Year;
  buff[5] = RTC_DateStr.RTC_Month;
  buff[6] = RTC_DateStr.RTC_Date;
  buff[7] = RTC_TimeStr.RTC_Hours;
  buff[8] = RTC_TimeStr.RTC_Minutes;
  
  HistoryData.SaveIndex++;
  if(HistoryData.SaveIndex >= HistoryDataMaxNum)
  {
    HistoryData.SaveIndex = 0;
  }
  WriteRom(HISTORYL_SAVE_ADDR,&HistoryData.SaveIndex,1);
  WriteRom((HISTORYL_DATA_ADDR + HistoryData.SaveIndex*9),buff,9);
}
/*********************************************************************************
 Function:      //
 Description:   //清除单个历史数据
 Input:         //
                //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void Clear_Single_History_Data(void)
{
  unsigned char buff[9] = {0};
  
  WriteRom((HISTORYL_DATA_ADDR + HistoryData.ReadIndex*9),buff,9);
}
///*********************************************************************************
// Function:      //
// Description:   //清除全部历史数据
// Input:         //
//                //
// Output:        //
// Return:	//
// Others:        //
//*********************************************************************************/
//void Clear_Single_History_Data(void)
//{
//  unsigned char buff[9] = {0};
//  
//  WriteRom((HISTORYL_DATA_ADDR + HistoryData.ReadIndex*9),buff,9);
//}
/******************************************END********************************************************/
