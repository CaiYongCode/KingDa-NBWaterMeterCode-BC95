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
TimerData_Struct  Time;
RTC_TimeTypeDef   RTC_TimeStr;        //RTC时间结构体
RTC_DateTypeDef   RTC_DateStr;        //RTC日期结构体
RTC_AlarmTypeDef  RTC_AlarmStr;       //闹钟结构体


/*********************************************************************************
外部变量声明区
*********************************************************************************/
/*********************************************************************************
私有变量定义区
*********************************************************************************/ 
unsigned short Last_Vol;
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
void Set_RTC(void)
{
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
void Close_Alarm(void)
{
  RTC_ITConfig(RTC_IT_ALRA, DISABLE);  //关闭闹钟中断
  RTC_AlarmCmd(DISABLE);    //关闭闹钟
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
void Alarm_Interrupt (void)                        //闹钟中断
{
  if(RESET != RTC_GetITStatus(RTC_IT_ALRA))
  {   
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStr);
    if(RTC_DateStr.RTC_Date == Settle_Date)       //结算日保存累积流量
    {
      Save_SDCF_Flow(&Cal.Water_Data);
    }
    RTC_ClearITPendingBit(RTC_IT_ALRA);              //清除闹钟中断
  }
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
void Wake_Interrupt (void)                        //唤醒中断
{
  if(RESET != RTC_GetITStatus(RTC_IT_WUT))
  {
    Device_Status = RUN_MODE;
    RCC_Configuration();
    
    //每5秒执行一次电压采集   
    Gather_Cycle_counter++;
    if(Gather_Cycle_counter >= 5)
    {
      rtc_interrupt();
      Gather_Cycle_counter = 0;
    }

    //周期上报设备参数
    Report_Cycle_counter++;
    if( (Report_Cycle_counter/60) >= Report_Cycle )
    {
    
      BC95.Report_Bit = 1;
      if(BC95.Start_Process == BC95_POWER_DOWN)
      {
        BC95.Start_Process = BC95_RECONNECT;
      }     
      Report_Cycle_counter = 0;
    }
    else
    {   
      if(BC95.Start_Process == BC95_POWER_DOWN)
      {
        Device_Status = SLEEP_MODE;
      }
    }
    
    //BC95运行超时判定
    if(BC95.Start_Process != BC95_POWER_DOWN)
    {
      BC95.Run_Time++;
      if(BC95.Run_Time > 300)
      {
        Device_Status = SLEEP_MODE;
      }
    }
    RTC_ClearITPendingBit(RTC_IT_WUT);                        //清除RTC唤醒标志
  }
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
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=16000;  //自己定义
      while(i--) ;    
   }
}
void rtc_interrupt (void)  //RTC中断处理函数 5s一次
{
    //采集电压
    delay_ms(3);
    Read_Voltage();
    
    if(BAT_Vol < BAT_Alarm_Vol)                                         //检测电池是否欠压
    {
      if(Last_Vol >= BAT_Alarm_Vol)                                   //判断是否为第一次欠压
      {
        Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);                                  //保存当前水量
        //报警
      }
    }
    Last_Vol = BAT_Vol;
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

