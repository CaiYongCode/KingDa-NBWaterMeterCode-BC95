/*******************************************************************************
Copyright: 
File name: rtc.c
Description: rtc相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "rtc.h"
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
RTC_TimeUpdate_TypeDef TimeUpdate;
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
 Description:   //配置
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_Config(void)
{
  RTC_InitTypeDef   RTC_InitStr;        
  
  CLK_LSEConfig(CLK_LSE_ON);                                    //打开LSE时钟
  while(CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);          //等待LSE时钟就绪
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);    //LSE时钟1分频
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  
  RTC_WakeUpCmd(DISABLE);                                       //RTC唤醒关闭
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);          //唤醒设置为16分频 
  RTC_SetWakeUpCounter(2047);                                   //设置唤醒寄存器时间为 1s
  RTC_ITConfig(RTC_IT_WUT, ENABLE);                             //使能RTC唤醒中断使能
  RTC_ClearITPendingBit(RTC_IT_WUT);                            //清除RTC唤醒标志
  RTC_WakeUpCmd(ENABLE);                                        //自动唤醒使能
  
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;               //设置24小时制
  RTC_InitStr.RTC_AsynchPrediv = 127;                           //异步分频器 128分频
  RTC_InitStr.RTC_SynchPrediv = 255;                            //同步分频器 256分频
  RTC_Init(&RTC_InitStr);
  
  ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_3);//优先级 
}
/*******************************************************************************
 Function:      //
 Description:   //设置闹钟
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_AlarmConfig(void) 
{
  RTC_AlarmTypeDef  RTC_AlarmStr;       
  
  RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 1;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 0;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay|RTC_AlarmMask_Hours|RTC_AlarmMask_Minutes;
  RTC_AlarmCmd(DISABLE);  
  RTC_SetAlarm(RTC_Format_BIN,&RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);                            //启动闹钟中断
  RTC_ClearITPendingBit(RTC_IT_ALRA);                           //清除闹钟中断
  RTC_AlarmCmd(ENABLE);                                         //启动闹钟
  ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_2);//RTC闹钟优先级
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Close_Alarm(void)
{
  RTC_ITConfig(RTC_IT_ALRA, DISABLE);  //关闭闹钟中断
  RTC_AlarmCmd(DISABLE);    //关闭闹钟
}
/*******************************************************************************
 Function:      //
 Description:   //闹钟中断
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_AlarmInterrupt(void)                        
{
  if(RESET != RTC_GetITStatus(RTC_IT_ALRA))
  {   

      
    RTC_ClearITPendingBit(RTC_IT_ALRA);              //清除闹钟中断
  }
}
/*******************************************************************************
 Function:      //
 Description:   //唤醒中断
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_WakeInterrupt (void)                        
{ 
  RTC_DateTypeDef date;
  RTC_TimeTypeDef time; 
  
  if(RESET != RTC_GetITStatus(RTC_IT_WUT))
  { 
    RTC_Second_Event();
    
    TimeUpdate.Second_Update++;
    if(TimeUpdate.Second_Update >= 30)
    {
      TimeUpdate.Second_Update = 0;
      RTC_GetDate(RTC_Format_BIN, &date);
      RTC_GetTime(RTC_Format_BIN, &time);
      if(TimeUpdate.Minute_Update != time.RTC_Minutes)
      {
        TimeUpdate.Minute_Update = time.RTC_Minutes;
        RTC_MinuteEvent(date,time);
      }
    }
    
    RTC_ClearITPendingBit(RTC_IT_WUT);                        //清除RTC唤醒标志
  }
}
/*******************************************************************************
 Function:      //
 Description:   //RTC秒事件
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_Second_Event(void)
{
  uint32_t timeoutLimit = 0;
  
  /*唤醒超过10分钟，则复位*/
  if(DevicePara.Mode.All != 0)
  {
    DevicePara.WeekTime++;
    if(DevicePara.WeekTime > 600)       //10m
    {
      DevicePara.Mode.WakeTimeoutRst = WAKE;
      DevicePara.Event.WakeTimeoutRst = PEND;
      DevicePara.WeekTime = 0;
    }
  }
  else
  {
    DevicePara.WeekTime = 0;
  }
  
  /*超过2倍上报周期没上报成功，则复位*/
  timeoutLimit = (uint32_t)DevicePara.ReportParas.Frequency*60*2;
  if(timeoutLimit < 176400)     //最小49小时
  {
    timeoutLimit = 176400;
  }
  DevicePara.ReportParas.Timeout++;
  if(DevicePara.ReportParas.Timeout > timeoutLimit)
  {
    DevicePara.Mode.ReportTimeoutRst = WAKE;
    DevicePara.Event.ReportTimeoutRst = PEND; 
    DevicePara.ReportParas.Timeout = 0;
  }   
}
/*******************************************************************************
 Function:      //
 Description:   //RTC分钟事件
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_MinuteEvent(RTC_DateTypeDef date,RTC_TimeTypeDef time)
{
  /*上报*/
  RTC_CycleReport(time);
  
  if(date.RTC_Year >= 20)
  {
    /*采样*/
    RTC_CycleSample(time);
    
    /*0分*/
    if(time.RTC_Minutes == 0)
    {
      /*0时*/
      if(time.RTC_Hours == 0)
      {
        /*每天0点清除告警标记*/
        DevicePara.AlarmMark.All = 0;   
        
        /*重新读取参数*/
        if(DevicePara.IsRereadParas != FALSE)
        {
          DevicePara.Mode.RereadParas = WAKE;
          DevicePara.Event.RereadParas = PEND;
          DevicePara.IsRereadParas = FALSE;
        }
        
        /*1日*/
        if(date.RTC_Date == 1)
        {
          DevicePara.Mode.RereadParas = WAKE;
          DevicePara.Event.RereadParas = PEND;
        } 
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //周期上报
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_CycleReport(RTC_TimeTypeDef time)
{
  if(DevicePara.ReportParas.StartTimeValid != FALSE)
  {
    if( (time.RTC_Hours == DevicePara.ReportParas.StartTimeHour)
       &&(time.RTC_Minutes == DevicePara.ReportParas.StartTimeMinute) )
    {
      DevicePara.ReportParas.StartTimeValid = FALSE;
      DevicePara.ReportParas.Timer = 0;
      DevicePara.Mode.PeriodicReport = WAKE;
      DevicePara.Event.PeriodicReport = PEND;
    }
  }
  else if(DevicePara.ReportParas.Frequency > 0)
  {
    DevicePara.ReportParas.Timer++;
    if( DevicePara.ReportParas.Timer >= DevicePara.ReportParas.Frequency )
    {   
      DevicePara.ReportParas.Timer = 0;
      DevicePara.Mode.PeriodicReport = WAKE;
      DevicePara.Event.PeriodicReport = PEND;
    }  
  }
}
/*******************************************************************************
 Function:      //
 Description:   //周期采样
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void RTC_CycleSample(RTC_TimeTypeDef time)
{
  if(DevicePara.SampleParas.Valid == FALSE)
  {
    if( (time.RTC_Hours == 0)
        &&(time.RTC_Minutes == 0) )
    {
      DevicePara.SampleParas.Valid = TRUE;
      DevicePara.SampleParas.Timer = 0;
      DevicePara.Mode.PeriodicSample = WAKE;
      DevicePara.Event.PeriodicSample = PEND;
    }
  }
  else
  {  
    if(DevicePara.SampleParas.Frequency > 0)
    {
      DevicePara.SampleParas.Timer++;
      if(DevicePara.SampleParas.Timer >= DevicePara.SampleParas.Frequency)
      {
        DevicePara.SampleParas.Timer = 0;
        DevicePara.Mode.PeriodicSample = WAKE;
        DevicePara.Event.PeriodicSample = PEND;
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //格林威治时间转换成北京时间
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
ErrorStatus RTC_GMTtoBT(unsigned char *str)
{
  unsigned char year,month,day,hour,minute,second;
  unsigned char LeapYear = 0;
  RTC_DateTypeDef Date;
  RTC_TimeTypeDef Time;
  ErrorStatus status;
  
  year   = ASCLL_to_Int(str[6])*10 + ASCLL_to_Int(str[7]);
  if(year < 20)
  {
    return ERROR;
  }
  month  = ASCLL_to_Int(str[9])*10 + ASCLL_to_Int(str[10]);
  day    = ASCLL_to_Int(str[12])*10 + ASCLL_to_Int(str[13]);
  hour   = ASCLL_to_Int(str[15])*10 + ASCLL_to_Int(str[16]);
  minute = ASCLL_to_Int(str[18])*10 + ASCLL_to_Int(str[19]);
  second = ASCLL_to_Int(str[21])*10 + ASCLL_to_Int(str[22]);
  
  //闰年判断
  if( (((year+2000)%4 == 0) && ((year+2000)%100 != 0)) || ((year+2000)%400 == 0))
  {
    LeapYear = 1;
  }
  
  hour = hour+8;
  if(hour > 23)
  {
    hour = hour%24;
    day++;
    switch(month)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
        {
          if(day > 31)
          {
            day = 1;
            month++;
          }
        }
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        {
          if(day > 30)
          {
            day = 1;
            month++;
          }
        }
        break;
      case 2:
        {
          if( (LeapYear == 0)&&(day > 28) )
          {
            day = 1;
            month++;
          }
          else if( (LeapYear == 1)&&(day > 29) )
          {
            day = 1;
            month++;
          }
        }
        break;
      case 12:
        {
          if(day > 31)
          {
            day = 1;
            month = 1;
            year++;
          }
        }
        break;  
    }
  }
  
  Date.RTC_Year = year;
  Date.RTC_Month = (RTC_Month_TypeDef)month;
  Date.RTC_Date = day;
  Time.RTC_Hours   = hour;
  Time.RTC_Minutes = minute;
  Time.RTC_Seconds = second;
  
  status = RTC_SetDate(RTC_Format_BIN, &Date);
  status = RTC_SetTime(RTC_Format_BIN, &Time);
  
  return status;
}
/*************************************END**************************************/