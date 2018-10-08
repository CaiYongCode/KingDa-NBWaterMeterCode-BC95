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
  RTC_InitStr.RTC_AsynchPrediv = 127;     //127*256 = 32768 周期1Hz
  RTC_InitStr.RTC_SynchPrediv = 255;
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
//void Set_RTC(void)
//{
//  RTC_TimeTypeDef  RTC_Time;
//  RTC_DateTypeDef  RTC_Date;
//  
//  RTC_Date.RTC_Year = BC95.R_Buffer[22]*10+BC95.R_Buffer[24];
//  RTC_Date.RTC_Month = BC95.R_Buffer[26]*10+BC95.R_Buffer[28];
//  RTC_Date.RTC_Date = BC95.R_Buffer[30]*10+BC95.R_Buffer[32];
//  RTC_Date.RTC_WeekDay = RTC_Weekday_Monday;
//  
//  RTC_Time.RTC_Hours   = BC95.R_Buffer[34]*10+BC95.R_Buffer[36];
//  RTC_Time.RTC_Minutes = BC95.R_Buffer[38]*10+BC95.R_Buffer[40];
//  RTC_Time.RTC_Seconds = BC95.R_Buffer[42]*10+BC95.R_Buffer[44];
//  
//  RTC_SetDate(RTC_Format_BIN, &RTC_Date);
//  RTC_SetTime(RTC_Format_BIN, &RTC_Time);
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void Set_Time(RTC_TimeTypeDef  *RTC_Time) //设置时间
//{
//  RTC_TimeStructInit(RTC_Time);   //校时 时间
//  RTC_TimeStr.RTC_Hours   = RTC_Time->RTC_Hours;
//  RTC_TimeStr.RTC_Minutes = RTC_Time->RTC_Minutes;
//  RTC_TimeStr.RTC_Seconds = RTC_Time->RTC_Seconds;
//  RTC_SetTime(RTC_Format_BIN, RTC_Time);
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void Set_Date(RTC_DateTypeDef  *RTC_Date) //设置日期
//{
//  RTC_DateStructInit(RTC_Date);  //校时 日历
//  RTC_DateStr.RTC_WeekDay = RTC_Date->RTC_WeekDay;
//  RTC_DateStr.RTC_Date = RTC_Date->RTC_Date;
//  RTC_DateStr.RTC_Month = RTC_Date->RTC_Month;
//  RTC_DateStr.RTC_Year = RTC_Date->RTC_Year;
//  
//  RTC_SetDate(RTC_Format_BIN, RTC_Date);
//}
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
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void Close_Alarm(void)
//{
//  RTC_ITConfig(RTC_IT_ALRA, DISABLE);  //关闭闹钟中断
//  RTC_AlarmCmd(DISABLE);    //关闭闹钟
//}
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
  union flow_union Flow;
  
  if(RESET != RTC_GetITStatus(RTC_IT_WUT))
  { 
    if(MeterParameter.DeviceStatus != SLEEP)
    {
      SysTick_Handler();
    }
    
    //每1小时存储一次水量  
    MeterParameter.SaveFlowTiming++;
    if( (MeterParameter.SaveFlowTiming/60) >= 60)
    {
      Read_ACUM_Flow(ADD_FLOW_ADD,&Flow);                  //读取累积流量
      if(Cal.Water_Data.flow32 != Flow.flow32)
      {
        Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);       //保存当前水量
      }
      MeterParameter.SaveFlowTiming = 0;
    }
    
    //周期采样数据
    if(MeterParameter.SampleFrequency > 0)
    {
      MeterParameter.SampleTiming++;
      if( (MeterParameter.SampleTiming/60) >= MeterParameter.SampleFrequency )
      {
        Save_History_Data();    //保存本次数据
        MeterParameter.SampleTiming = 0;
      }
    }
    
    //周期上报设备参数
    if(MeterParameter.ReportFrequency > 0)
    {
      MeterParameter.ReportTiming++;
      if( (MeterParameter.ReportTiming/60) >= MeterParameter.ReportFrequency )
      {   
        if(BC95.Start_Process == BC95_POWER_DOWN)
        {
          MeterParameter.DeviceStatus = RUN;
          BC95_Power_On();
        }     
        MeterParameter.ReportTiming = 0;
      }  
    }
   
    //设备运行超时，强制睡眠
    if(MeterParameter.DeviceStatus == RUN)
    {
      MeterParameter.DeviceRunTiming++;    
      if( (MeterParameter.DeviceRunTiming/60) >= 10)
      {
         MCU_DeInit();
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

