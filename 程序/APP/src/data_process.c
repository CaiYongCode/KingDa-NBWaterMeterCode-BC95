/*******************************************************************************
Copyright: 
File name: uplink_protocol.h
Description: 上行通信协议相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "data_process.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
/*******************************************************************************
外部变量声明区
*******************************************************************************/
/*******************************************************************************
私有变量定义区
*******************************************************************************/ 
/*******************************************************************************
测试变量定义区
*******************************************************************************/
/*******************************************************************************
内部函数定义区
*******************************************************************************/
/*******************************************************************************
功能代码定义区
*******************************************************************************/
/*******************************************************************************
 Function:      //
 Description:   //读数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_ReadData(uint32_t addr, uint8_t *buff, uint16_t length)
{
  Flash_Read(addr, buff, length);
}
/*******************************************************************************
 Function:      //
 Description:   //写数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_WriteData(uint32_t addr, uint8_t *buff, uint16_t length)
{
  Flash_Write(addr, buff, length);
}
/*******************************************************************************
 Function:      //
 Description:   //清空EEPROM前64字节
                //前2字节不使用，若前2字节不全为0，则清空EEPROM前64字节
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataProcess_Clear64Bytes(void)
{
  uint8_t temp[64] = {0};

  DataProcess_ReadData(INTERNAL_EEPROM_START_ADDR,temp,2);
  if( (temp[0] != 0xAA)||(temp[1] != 0xBB) )
  {
    temp[0] = 0xAA;
    temp[1] = 0xBB;
    DataProcess_WriteData(INTERNAL_EEPROM_START_ADDR,temp,64);
  }
}
/*******************************************************************************
 Function:      //
 Description:   //写水量
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataProcess_WriteFlow(void)
{
  DataProcess_WriteData(FORWARD_FLOW_ADDR, DevicePara.ForwardFlow.flow8, 4);  
}
/*******************************************************************************
 Function:      //
 Description:   //写IMEI
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataProcess_WriteIMEI(void)
{
  uint8_t imei[15] = {0};
  
  DataProcess_ReadData(IMEI_ADDR,imei,15);  
  if( 0 != memcmp(BC95.IMEI, imei, 15) )
  {
    DataProcess_WriteData(IMEI_ADDR, BC95.IMEI, 15); 
  } 
}
/*********************************************************************************
 Function:      //
 Description:   //判断是否重新读参数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_CheckRereadParas(void)
{
  RTC_DateTypeDef date;
  
  RTC_GetDate(RTC_Format_BIN, &date);
  if(date.RTC_Year < 20)
  {
    DevicePara.IsRereadParas = TRUE;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //读设备参数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_ReadDevicePara(void)
{
  /*读水量*/
  DataProcess_ReadData(FORWARD_FLOW_ADDR,DevicePara.ForwardFlow.flow8,4);  
  
  /*读上报参数*/
  DataProcess_ReadReportParas();
  
  /*读采样参数*/
  DataProcess_ReadSampleParas();
}
/*********************************************************************************
 Function:      //
 Description:   //读上报参数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_ReadReportParas(void)
{
  uint8_t imei[15] = {0};
  uint8_t data[32] = {0};
  uint16_t offsetTime = 0;
  uint8_t offsetHour = 0;
  uint8_t offsetMinute = 0;
  uint16_t temp = 0;
  
  DataProcess_ReadData(IMEI_ADDR, imei, 15);
  offsetTime = GetOffsetTime(&imei[11]);
  
  DataProcess_ReadData(REPORT_FREQUENCY_ADDR,data,6);  

  temp = data[0]*0x100 + data[1];
  if( (temp > 0)&&(temp < 0xFFFF) )
  {
    DevicePara.ReportParas.Frequency = temp;
  }
  else
  {
    DevicePara.ReportParas.Frequency = 1440;
  }
  
  temp = data[4]*0x100 + data[5];
  if( (data[2] < 24)&&(data[3] < 60)
    &&(temp > 0)&&(temp <= 1440) )
  {
    DevicePara.ReportParas.StartTimeHour = data[2];
    DevicePara.ReportParas.StartTimeMinute = data[3];
    DevicePara.ReportParas.DRDuration = temp;
  }
  else
  {
    DevicePara.ReportParas.StartTimeHour = 0;
    DevicePara.ReportParas.StartTimeMinute = 0;
    DevicePara.ReportParas.DRDuration = 480;
  }
  
  offsetHour = offsetTime%DevicePara.ReportParas.DRDuration/60;
  offsetMinute = offsetTime%DevicePara.ReportParas.DRDuration%60;
  
  DevicePara.ReportParas.StartTimeHour = (DevicePara.ReportParas.StartTimeHour+offsetHour)%24;
  DevicePara.ReportParas.StartTimeMinute = (DevicePara.ReportParas.StartTimeMinute+offsetMinute)%60;
  DevicePara.ReportParas.StartTimeValid = TRUE;
  DevicePara.ReportParas.Timer = 0;
}
/*********************************************************************************
 Function:      //
 Description:   //读采样参数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataProcess_ReadSampleParas(void)
{
  uint8_t data[16] = {0};
  CircularQueue_TypeDef queue;
  
  DataProcess_ReadData(SAMPLE_FREQUENCY_ADDR,data,8); 
  memcpy(&queue.Total,&data[2],6);
  if( ((queue.Front+queue.Total)%SampleDataMax) ==  queue.Rear)
  {
    memcpy(&DevicePara.SampleParas.Queue.Total,&queue.Total,6);
  }
  else
  {
    memset(&DevicePara.SampleParas.Queue.Total,0,6);
  }
  DevicePara.SampleParas.Frequency = data[0]*0x100 + data[1];
  DevicePara.SampleParas.Timer = 0;
  DevicePara.SampleParas.Valid = FALSE;
}
/*******************************************************************************
 Function:      //
 Description:   //写采样数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataPocess_WriteSampleData(void)
{
  uint8_t data[16] = {0};
  uint32_t addr = 0;
  RTC_DateTypeDef Date;
  RTC_TimeTypeDef Time;
  
  addr = SAMPLE_DATA_START_ADDR + DevicePara.SampleParas.Queue.Rear*SampleDataEachSize;      //采样数据存储地址

  RTC_GetDate(RTC_Format_BIN, &Date);
  RTC_GetTime(RTC_Format_BIN, &Time);

  memcpy(data,DevicePara.ForwardFlow.flow8,4);
  data[4] = Date.RTC_Year;
  data[5] = Date.RTC_Month;
  data[6] = Date.RTC_Date;
  data[7] = Time.RTC_Hours;
  data[8] = Time.RTC_Minutes;

  DataProcess_WriteData(addr,data,9);
 
  DevicePara.SampleParas.Queue.Rear = (DevicePara.SampleParas.Queue.Rear+1)%SampleDataMax;
  if(DevicePara.SampleParas.Queue.Total < SampleDataMax)
  {
    DevicePara.SampleParas.Queue.Total++;
  }
  else
  {
    DevicePara.SampleParas.Queue.Front = DevicePara.SampleParas.Queue.Rear;
  }
  DataProcess_WriteData(SAMPLE_DATA_TOTAL_ADDR, (uint8_t *)&DevicePara.SampleParas.Queue.Total, 6);
}
/*******************************************************************************
 Function:      //
 Description:   //读采样数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataPocess_ReadSampleData(uint8_t *buff,uint8_t number)
{
  uint32_t addr = 0;

  addr = SAMPLE_DATA_START_ADDR + DevicePara.SampleParas.Queue.Front*SampleDataEachSize;      //采样数据读地址
  DataProcess_ReadData(addr, buff, number*SampleDataEachSize);
}
/*******************************************************************************
 Function:      //
 Description:   //清除采样数据包
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void DataPocess_ClearSampleData(uint8_t number)
{
  DevicePara.SampleParas.Queue.Total = DevicePara.SampleParas.Queue.Total - number;
  if(DevicePara.SampleParas.Queue.Total > 0)
  {
    DevicePara.SampleParas.Queue.Front = (DevicePara.SampleParas.Queue.Front+number)%SampleDataMax;
  }
  else
  {
    DevicePara.SampleParas.Queue.Front = DevicePara.SampleParas.Queue.Rear;
  }
  
  DataProcess_WriteData(SAMPLE_DATA_TOTAL_ADDR,(uint8_t *)&DevicePara.SampleParas.Queue.Total,6);
}
/*****************************************************************************************************/
/******************************************DEBUG相关读写**********************************************/
/*****************************************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //保存调试复位记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_WriteDebugResetRecord(void)
{
  uint8_t buff[10] = {0};
  uint16_t num = 0;
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;

  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  
  DataProcess_ReadData(DEBUG_RESET_RECORD_ADDR,buff,2);
  num = buff[0]*0x100 + buff[1];
  if(num < 0xFFFF)
  {
    num++;
  }
  buff[0] = num/0x100;
  buff[1] = num%0x100; 
  buff[2] = date.RTC_Year;
  buff[3] = date.RTC_Month;
  buff[4] = date.RTC_Date;
  buff[5] = time.RTC_Hours;
  buff[6] = time.RTC_Minutes; 
  buff[7] = time.RTC_Seconds; 
  
  DataProcess_WriteData(DEBUG_RESET_RECORD_ADDR,buff,8);
}
/*********************************************************************************
 Function:      //
 Description:   //读取调试复位记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_ReadDebugResetRecord(uint8_t *buff)
{
  DataProcess_ReadData(DEBUG_RESET_RECORD_ADDR,buff,8);
  DataProcess_ReadData(DEBUG_RESET_WAKE_TIMEOUT_ADDR,&buff[8],12);
}  
/*********************************************************************************
 Function:      //
 Description:   //保存上传统计
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_WriteDebugReportStatistics(uint8_t flag)
{
  uint8_t buff[2] = {0};
  uint16_t num = 0;
  uint16_t addr = 0;
  
  addr = DEBUG_REPORT_STATISTICS_ADDR + flag*2;
  
  DataProcess_ReadData(addr,buff,6);
  num = buff[0]*0x100 + buff[1];
  num++;
  buff[0] = num/0x100;
  buff[1] = num%0x100;
  DataProcess_WriteData(addr,buff,2);
}
/*********************************************************************************
 Function:      //
 Description:   //读取上传统计
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_ReadDebugReportStatistics(uint8_t *buff)
{
  DataProcess_ReadData(DEBUG_REPORT_STATISTICS_ADDR,buff,6);
}
/*********************************************************************************
 Function:      //
 Description:   //保存上传记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_WriteDebugReportRecord(uint8_t flag)
{
  uint8_t buff[10] = {0};
  uint16_t addr = 0;
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;
 
  if(flag == 0)         //保存启动时间
  { 
    addr = DEBUG_REPORT_RECORD_ADDR;
    RTC_GetDate(RTC_Format_BIN, &date);
    RTC_GetTime(RTC_Format_BIN, &time);
    buff[0] = date.RTC_Year;
    buff[1] = date.RTC_Month;
    buff[2] = date.RTC_Date;
    buff[3] = time.RTC_Hours;
    buff[4] = time.RTC_Minutes; 
    buff[5] = time.RTC_Seconds; 
    DataProcess_WriteData(addr,buff,10); 
  }
  else if(flag == 1)    //保存结果成功
  {
    addr = DEBUG_REPORT_RECORD_ADDR+6;
    buff[0] = 1;
    DataProcess_WriteData(addr,buff,1); 
  }
  else if(flag == 2)    //保存结果失败
  {
    addr = DEBUG_REPORT_RECORD_ADDR+6;
    buff[0] = 2;
    buff[1] = BC95.ErrorStep;
    buff[2] = BC95.ErrorCode/0x100;
    buff[3] = BC95.ErrorCode%0x100;
    DataProcess_WriteData(addr,buff,4); 
  }
}
/*********************************************************************************
 Function:      //
 Description:   //读取上传记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_ReadDebugReportRecord(uint8_t *buff)
{
  DataProcess_ReadData(DEBUG_REPORT_RECORD_ADDR,buff,10);
}
/*********************************************************************************
 Function:      //
 Description:   //保存唤醒超时复位记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_WriteWakeTimeoutResetRecord(void)
{
  uint8_t buff[10] = {0};
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;

  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  
  buff[0] = date.RTC_Year;
  buff[1] = date.RTC_Month;
  buff[2] = date.RTC_Date;
  buff[3] = time.RTC_Hours;
  buff[4] = time.RTC_Minutes; 
  buff[5] = time.RTC_Seconds; 
  
  DataProcess_WriteData(DEBUG_RESET_WAKE_TIMEOUT_ADDR,buff,6);
}
/*********************************************************************************
 Function:      //
 Description:   //保存上报超时复位记录
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*********************************************************************************/
void DataPocess_WriteReportTimeoutResetRecord(void)
{
  uint8_t buff[10] = {0};
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;

  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  
  buff[0] = date.RTC_Year;
  buff[1] = date.RTC_Month;
  buff[2] = date.RTC_Date;
  buff[3] = time.RTC_Hours;
  buff[4] = time.RTC_Minutes; 
  buff[5] = time.RTC_Seconds; 
  
  DataProcess_WriteData(DEBUG_RESET_REPORT_TIMEOUT_ADDR,buff,6);
}
/*************************************END**************************************/
