/*******************************************************************************
Copyright: 
File name: main.c
Description: 主函数
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
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
void Event_Process(void);
void SystemResetLed_ON(void);
void SystemResetLed_OFF(void);
/*******************************************************************************
功能代码定义区
*******************************************************************************/
/*******************************************************************************
 Function:      //
 Description:   //主函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void main(void)
{ 
  disableInterrupts();                                      //关总中断
  MCU_Config();
  RTC_Config();
  Pulse_Config();  
  enableInterrupts();                                       //开总中断
/////////////////////////////////////////////////////////   
  SystemResetLed_ON();
  Delay_ms(500);
  SystemResetLed_OFF();
  DataProcess_Clear64Bytes();
  DataProcess_ReadDevicePara();                  
  DataProcess_CheckRereadParas();
  DataPocess_WriteDebugResetRecord();
/********************************DEBUG*****************************************/
/********************************DEBUG*****************************************/  
  while(1)
  { 
    IWDG_ReloadCounter();          
    if(DevicePara.Mode.All == SLEEP)      //设备进入睡眠模式
    {  
      Sleep();
    }  
    else
    {
      SoftTimer_Process();
      UplinkProtocol_TxProcess();
      BC95_Process();
      Event_Process();
      Debug_Process();
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //事件进程
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Event_Process(void)
{
  //周期上报
  if(DevicePara.Event.PeriodicReport != FREE)
  {
    DevicePara.Event.PeriodicReport = FREE;
    DataProcess_WriteFlow();                    //保存当前水量
    DataPocess_WriteDebugReportStatistics(0);   //启动次数+1
    DataPocess_WriteDebugReportRecord(0);       //保存启动时间
    UplinkProtocol_Init();
  }
  
  //周期采样
  if(DevicePara.Event.PeriodicSample != FREE)
  {
    DevicePara.Event.PeriodicSample = FREE;
    DataPocess_WriteSampleData();       //保存采样数据
//    DataProcess_WriteFlow();            //保存当前水量
    DevicePara.Mode.PeriodicSample = SLEEP;
  }
  
  //手动上报
  if(DevicePara.Event.ManualReport != FREE)
  {
    DevicePara.Event.ManualReport = FREE;
    DataProcess_WriteFlow();                    //保存当前水量
    DataPocess_WriteDebugReportStatistics(0);   //启动次数+1
    DataPocess_WriteDebugReportRecord(0);       //保存启动时间
    UplinkProtocol_Init();  
  }

  //调试数据
  if(DevicePara.Event.ManualDebug != FREE)
  {
    DevicePara.Event.ManualDebug = FREE;
    DataProcess_WriteFlow();                    //保存当前水量
    Debug_Init();
  }

  //告警上报
  if(DevicePara.Event.AlarmReport != FREE)
  {
    DevicePara.Event.AlarmReport = FREE;
    DataPocess_WriteDebugReportStatistics(0);   //启动次数+1
    DataPocess_WriteDebugReportRecord(0);       //保存启动时间
    UplinkProtocol_Init();  
  }
  
  //唤醒超时复位
  if(DevicePara.Event.WakeTimeoutRst != FREE)
  {
    DevicePara.Event.WakeTimeoutRst = FREE;
    DevicePara.Mode.WakeTimeoutRst = SLEEP;
    DataProcess_WriteFlow();  //保存当前水量
    DataPocess_WriteWakeTimeoutResetRecord();
    SystemReset();            //系统复位
  }

  //上报超时复位
  if(DevicePara.Event.ReportTimeoutRst != FREE)
  {
    DevicePara.Event.ReportTimeoutRst = FREE;
    DevicePara.Mode.ReportTimeoutRst = SLEEP;
    DataProcess_WriteFlow();    //保存当前水量
    DataPocess_WriteReportTimeoutResetRecord();
    SystemReset();              //系统复位   
  }
  
    //手动复位
  if(DevicePara.Event.ManualRst != FREE)
  {
    DevicePara.Event.ManualRst = FREE;
    DevicePara.Mode.ManualRst = SLEEP;
    DataProcess_WriteFlow();    //保存当前水量
    SystemReset();              //系统复位   
  }
  
  //重新读取参数
  if(DevicePara.Event.RereadParas != FREE)
  {
    DevicePara.Event.RereadParas = FREE;
    /*读上报参数*/
    DataProcess_ReadReportParas();
    if( (0 == DevicePara.ReportParas.StartTimeHour)
       &&(0 == DevicePara.ReportParas.StartTimeMinute) )
    {
      DevicePara.ReportParas.StartTimeValid = FALSE;
      DevicePara.ReportParas.Timer = 0;
      DevicePara.Mode.PeriodicReport = WAKE;
      DevicePara.Event.PeriodicReport = PEND;
    }
    /*读采样参数*/
    DataProcess_ReadSampleParas();
    DevicePara.SampleParas.Valid = TRUE;
    
    DevicePara.Mode.RereadParas = SLEEP;
  }
}
/*******************************************************************************
 Function:      //
 Description:   //复位指示灯
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void SystemResetLed_ON(void)
{
  GPIO_SetBits(GPIOD, GPIO_Pin_6);
  GPIO_SetBits(GPIOD, GPIO_Pin_7);
}
void SystemResetLed_OFF(void)
{
  GPIO_ResetBits(GPIOD, GPIO_Pin_6);
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}
/*************************************END**************************************/