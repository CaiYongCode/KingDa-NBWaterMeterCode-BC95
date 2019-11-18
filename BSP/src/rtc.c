/*********************************************************************************
//概述：
//作者：随风飘跃     时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************/
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
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Rtc_Config(void)
{
  RTC_InitTypeDef   RTC_InitStr;        //定义RTC初始化结构体
  
  CLK_LSEConfig(CLK_LSE_ON);//打开LSE时钟
  while(CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);//等待LSE时钟就绪
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  
  RTC_WakeUpCmd(DISABLE);                                   //RTC唤醒关闭
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);      //唤醒设置为16分频 也就是32.768k/16
  RTC_SetWakeUpCounter(2047);                               //设置唤醒寄存器时间为 1s

  RTC_ITConfig(RTC_IT_WUT, ENABLE);                         //使能RTC唤醒中断使能
  RTC_ClearITPendingBit(RTC_IT_WUT);                        //清除RTC唤醒标志
  RTC_WakeUpCmd(ENABLE);                                    //自动唤醒使能
  
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;  //设置24小时制
  RTC_InitStr.RTC_AsynchPrediv = 127;     //异步分频器 128分频
  RTC_InitStr.RTC_SynchPrediv = 255;      //同步分频器 256分频
  RTC_Init(&RTC_InitStr);
  
  ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_2);   //优先级
  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Set_Alarm(void) //设置闹钟
{
  RTC_AlarmTypeDef  RTC_AlarmStr;       //闹钟结构体
  
//  RTC_AlarmStructInit(RTC_Alarm);    //设置闹钟
  RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 1;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 0;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
 
  RTC_AlarmCmd(DISABLE);  
  
  RTC_SetAlarm(RTC_Format_BIN,&RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);                                            //启动闹钟中断
  RTC_ClearITPendingBit(RTC_IT_ALRA);                                           //清除闹钟中断
  RTC_AlarmCmd(ENABLE);                                                         //启动闹钟
  ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_2);                //优先级
}
/*********************************************************************************
 Function:      //
 Description:   //闹钟中断
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Alarm_Interrupt (void)                        
{
  if(RESET != RTC_GetITStatus(RTC_IT_ALRA))
  {   
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
    if(RTC_DateStr.RTC_Date == MeterParameter.SettleDate)       //结算日保存累积流量
    {
      Save_SDCF_Flow(&Cal.Water_Data);
    }
    RTC_ClearITPendingBit(RTC_IT_ALRA);              //清除闹钟中断
  }
}
/*********************************************************************************
 Function:      //
 Description:   //唤醒中断
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Wake_Interrupt (void)                        
{
  RTC_TimeTypeDef Time;
  uint16_t randnum = 0;
  
  if(RESET != RTC_GetITStatus(RTC_IT_WUT))
  {    
    /*周期采样数据*/
    if(MeterParameter.SampleFrequency > 0)
    {
      MeterParameter.SampleTiming++;
      if( (MeterParameter.SampleTiming/60) >= MeterParameter.SampleFrequency )
      {
        MeterParameter.SampleTiming = 0;
        MeterParameter.Mode.eeprom = WAKE;
        MeterParameter.Event.eeprom = PEND;
      }
    }
    /*离散上报时间无效，则按出厂时间上报，否则按照设定离散上报*/
    if(MeterParameter.DRValid == FALSE)
    {      
      if(MeterParameter.ReportFrequency > 0)
      {
        MeterParameter.ReportTiming++;
        if( (MeterParameter.ReportTiming/60) >= MeterParameter.ReportFrequency )
        {               
          MeterParameter.ReportTiming = 0;
          MeterParameter.Mode.bc95 = WAKE;
          MeterParameter.Event.bc95 = PEND;
        }  
      }
    }
    else
    {
      if(MeterParameter.ReportRandTime == 0)
      {
        RTC_GetTime(RTC_Format_BIN, &Time);
        if( (Time.RTC_Hours == MeterParameter.DRStartTimeHour)&&(Time.RTC_Minutes == MeterParameter.DRStartTimeMinute) )
        {
          randnum = BC95.IMEI[13]*0x100+BC95.IMEI[14];
          MeterParameter.ReportRandTime = randnum%(MeterParameter.DRDuration*60)+1; 
        }
      }
      else
      {
        MeterParameter.ReportRandTiming++;
        if(MeterParameter.ReportRandTiming >= MeterParameter.ReportRandTime)
        {
          MeterParameter.DRValid = FALSE;
          MeterParameter.ReportRandTime = 0;
          MeterParameter.ReportRandTiming = 0;
          MeterParameter.ReportTiming = 0;
          MeterParameter.Mode.bc95 = WAKE;
          MeterParameter.Event.bc95 = PEND;
        }
      }
    }
   
    RTC_ClearITPendingBit(RTC_IT_WUT);                        //清除RTC唤醒标志
  }
}

/*********************************************************************************
 Function:      //
 Description:   //格林威治时间转换成北京时间
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void GMT_to_BT(unsigned char *str)
{
  unsigned char year,month,day,hour,minute,second;
  unsigned char LeapYear = 0;
  
  year   = ASCLL_to_Int(str[6])*10 + ASCLL_to_Int(str[7]);
  if(year < 19)
  {
    return;
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
  
  RTC_DateStr.RTC_Year = year;
  RTC_DateStr.RTC_Month = (RTC_Month_TypeDef)month;
  RTC_DateStr.RTC_Date = day;
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Monday;
  
  RTC_TimeStr.RTC_Hours   = hour;
  RTC_TimeStr.RTC_Minutes = minute;
  RTC_TimeStr.RTC_Seconds = second;
  
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

