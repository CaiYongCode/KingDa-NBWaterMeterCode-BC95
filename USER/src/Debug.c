/*********************************************************************************
文件包含区
*********************************************************************************/
#include "Debug.h"
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
//struct Debug_EN Debug;
/*********************************************************************************
测试变量定义区
*********************************************************************************/
/*********************************************************************************
内部函数定义区
*********************************************************************************/
/*********************************************************************************
功能代码定义区
*********************************************************************************/
void Debug_Config(void)
{
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_In_PU_IT);
  
  EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Falling);
  EXTI_ClearITPendingBit (EXTI_IT_Pin7);                    //清中断标志位
  ITC_SetSoftwarePriority(EXTI7_IRQn , ITC_PriorityLevel_2);//中断优先级设定
}
/*********************************************************************************
 Function:      //
 Description:   //初始化
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Init(void)
{
  USART3_Configuration();  
  Create_Timer(ONCE,60000,
               Debug_DeInit,0,PROCESS); 
}
/*********************************************************************************
 Function:      //
 Description:   //取消初始化为默认状态
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_DeInit(void)
{
  Free_Uart3();
  USART_DeInit(USART3);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3,DISABLE);
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);
  
  Debug_Config();
  
  MeterParameter.Mode.debug = SLEEP;
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
void Debug_Process(void)
{
  uint8_t buff[64] = {0};
  bool valid = FALSE;
  
  if(Uart3.Receive_Pend != FALSE)//判断有数据
  { 
    Uart3_Receive(buff);
    
    if(strstr((const char *)buff,"读EEPROM状态") != NULL)   //读EEPROM状态
    {
      valid = TRUE;
      Debug_EepromStatus();
    }
    else if(strstr((const char *)buff,"读电压温度") != NULL)   //读电压温度
    {
      valid = TRUE;
      Debug_VolTemp();
    }
    else if(strstr((const char *)buff,"读时间") != NULL)   //读时间
    {
      valid = TRUE;
      Debug_Time();
    }
    else if(strstr((const char *)buff,"读模组卡号") != NULL)   //读模组卡号
    {
      valid = TRUE;
      Debug_IMEIandIMSI();
    }
    else if(strstr((const char *)buff,"读信号参数") != NULL)   //读信号参数
    {
      valid = TRUE;
      Debug_SignalParas();
    }
    else if(strstr((const char *)buff,"读采样参数") != NULL)   //读采样参数
    {
      valid = TRUE;
      Debug_SampleParas();
    }
    else if(strstr((const char *)buff,"读上传参数") != NULL)   //读上传参数
    {
      valid = TRUE;
      Debug_ReportParas();
    }
    else if(strstr((const char *)buff,"读复位记录") != NULL)   //读复位记录
    {
      valid = TRUE;
      Debug_ResetRecord();
    }
    else if(strstr((const char *)buff,"读采样记录") != NULL)   //读采样记录
    {
      valid = TRUE;
      Debug_SampleRecord();
    }
    else if(strstr((const char *)buff,"读上传统计") != NULL)   //读上传统计
    {
      valid = TRUE;
      Debug_ReportStatistics();
    }
    else if(strstr((const char *)buff,"读上传记录") != NULL)   //读上传记录
    {
      valid = TRUE;
      Debug_ReportRecord();
    }
    else if(strstr((const char *)buff,"清复位记录") != NULL)   //清复位记录
    {
      valid = TRUE;
      Debug_ClearResetRecord();
      
    }
    else if(strstr((const char *)buff,"清上传统计") != NULL)   //清上传统计
    {
      valid = TRUE;
      Debug_ClearReportStatistics();
    }
    else if(strstr((const char *)buff,"调试结束") != NULL)   //调试结束
    {
      valid = FALSE;
      Uart3_Send("已结束",8);
      Create_Timer(ONCE,1000,
                   Debug_DeInit,0,PROCESS); 
    }
    
    if(valid != FALSE)
    {
      Create_Timer(ONCE,60000,
                   Debug_DeInit,0,PROCESS); 
    }
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
void Debug_EepromStatus(void)
{
  uint8_t i = 0;
  uint16_t addr = 0x17F0;
  uint8_t wbuff[10] = {0};
  uint8_t rbuff[10] = {0};
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;
 
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  wbuff[0] = date.RTC_Year;
  wbuff[1] = date.RTC_Month;
  wbuff[2] = date.RTC_Date;
  wbuff[3] = time.RTC_Hours;
  wbuff[4] = time.RTC_Minutes; 
  wbuff[5] = time.RTC_Seconds; 
  
  WriteRom(addr,wbuff,6);
  for(i = 0;i < 6;i++)
  {    
    rbuff[i] = *((const unsigned char *)(addr+i));
  }
  
  if( 0 == strncmp((const char *)wbuff,(const char *)rbuff,6) )
  {
    Uart3_Send("读写成功",8);
  }
  else
  {
    Uart3_Send("读写失败",8);
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_VolTemp(void)
{
  uint8_t buff[32] = "电压:00.00V,温度:000度";
  signed char temp = 0;                   
  uint16_t voltage = 0; 
  
  Read_Temp();
  Read_Voltage();
  voltage = MeterParameter.Voltage;
  temp = MeterParameter.Temp;
  
  buff[5] = Int_to_ASCLL(voltage/1000);
  buff[6] = Int_to_ASCLL(voltage%1000/100);
  buff[8] = Int_to_ASCLL(voltage%100/10);
  buff[9] = Int_to_ASCLL(voltage%10);
  if(temp> 0)
  {
    buff[17] = '+';
  }
  else
  {
    buff[17] = '-';
  }
  buff[18] = Int_to_ASCLL( abs(temp/10) );
  buff[19] = Int_to_ASCLL( abs(temp%10) );
  
  Uart3_Send(buff,22);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Time(void)
{
  uint8_t buff[32] = "2019年01月01日 01时01分01秒";
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;

  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  
  buff[2] = Int_to_ASCLL(date.RTC_Year/10);
  buff[3] = Int_to_ASCLL(date.RTC_Year%10);
  buff[6] = Int_to_ASCLL(date.RTC_Month/10);
  buff[7] = Int_to_ASCLL(date.RTC_Month%10);
  buff[10] = Int_to_ASCLL(date.RTC_Date/10);
  buff[11] = Int_to_ASCLL(date.RTC_Date%10);
  buff[15] = Int_to_ASCLL(time.RTC_Hours/10);
  buff[16] = Int_to_ASCLL(time.RTC_Hours%10);
  buff[19] = Int_to_ASCLL(time.RTC_Minutes/10);
  buff[20] = Int_to_ASCLL(time.RTC_Minutes%10);
  buff[23] = Int_to_ASCLL(time.RTC_Seconds/10);
  buff[24] = Int_to_ASCLL(time.RTC_Seconds%10);

  Uart3_Send(buff,27);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_IMEIandIMSI(void)
{
  uint8_t buff[64] = "IMEI:123456789012345,ICCID:12345678901234567890";
  
  memcpy(&buff[5],BC95.IMEI,15);
  memcpy(&buff[26],BC95.ICCID,20);

  Uart3_Send(buff,46);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_SignalParas(void)
{
  uint8_t buff[32] = "CSQ:00,RSRP:-000,SNR:000,ECL:000";  
  buff[4] = Int_to_ASCLL(BC95.Rssi/10);
  buff[5] = Int_to_ASCLL(BC95.Rssi%10);
  buff[13] = Int_to_ASCLL(abs(BC95.RSRP)/100);
  buff[14] = Int_to_ASCLL(abs(BC95.RSRP)%100/10);
  buff[15] = Int_to_ASCLL(abs(BC95.RSRP)%10);
  if(BC95.SNR < 0)
  {
    buff[21] = '-';
  }
  buff[22] = Int_to_ASCLL(abs(BC95.SNR)/10);
  buff[23] = Int_to_ASCLL(abs(BC95.SNR)%10);
  buff[29] = Int_to_ASCLL(BC95.ECL/100);
  buff[30] = Int_to_ASCLL(BC95.ECL/100);
  buff[31] = Int_to_ASCLL(BC95.ECL%10);

  Uart3_Send(buff,32);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_SampleParas(void)
{
  uint8_t buff[32] = "频率:00000分,计时:0000000秒";
  uint16_t freq = 0;
  uint32_t timing = 0;
  
  freq = MeterParameter.SampleFrequency;
  timing = MeterParameter.SampleTiming;
  
  buff[5] = Int_to_ASCLL(freq/10000);
  buff[6] = Int_to_ASCLL(freq%10000/1000);
  buff[7] = Int_to_ASCLL(freq%1000/100);
  buff[8] = Int_to_ASCLL(freq%100/10);
  buff[9] = Int_to_ASCLL(freq%10);
  
  buff[18] = Int_to_ASCLL(timing/1000000);
  buff[19] = Int_to_ASCLL(timing%1000000/100000);
  buff[20] = Int_to_ASCLL(timing%100000/10000);
  buff[21] = Int_to_ASCLL(timing%10000/1000);
  buff[22] = Int_to_ASCLL(timing%1000/100);
  buff[23] = Int_to_ASCLL(timing%100/10);
  buff[24] = Int_to_ASCLL(timing%10);

  Uart3_Send(buff,27);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ReportParas(void)
{
  uint8_t buff1[40] = "模式:周期,频率:00000分,计时:0000000秒";
  uint8_t buff2[60] = "模式:定时,时间:08时08分,时长:00000分,计时:0000000秒";
  uint16_t freq = 0;
  uint32_t timing = 0;
  uint8_t hour = 0,minute = 0;
  uint16_t duration = 0;
  
  if(MeterParameter.DRValid == FALSE)
  {
    freq = MeterParameter.ReportFrequency;
    timing = MeterParameter.ReportTiming;
    
    buff1[15] = Int_to_ASCLL(freq/10000);
    buff1[16] = Int_to_ASCLL(freq%10000/1000);
    buff1[17] = Int_to_ASCLL(freq%1000/100);
    buff1[18] = Int_to_ASCLL(freq%100/10);
    buff1[19] = Int_to_ASCLL(freq%10);
    buff1[28] = Int_to_ASCLL(timing/1000000);
    buff1[29] = Int_to_ASCLL(timing%1000000/100000);
    buff1[30] = Int_to_ASCLL(timing%100000/10000);
    buff1[31] = Int_to_ASCLL(timing%10000/1000);
    buff1[32] = Int_to_ASCLL(timing%1000/100);
    buff1[33] = Int_to_ASCLL(timing%100/10);
    buff1[34] = Int_to_ASCLL(timing%10);

    Uart3_Send(buff1,37);
  }
  else
  {
    hour = MeterParameter.DRStartTimeHour;
    minute = MeterParameter.DRStartTimeMinute;
    duration = MeterParameter.DRDuration;
    timing = MeterParameter.ReportRandTiming;
    
    buff2[15] = Int_to_ASCLL(hour/10);
    buff2[16] = Int_to_ASCLL(hour%10);
    buff2[19] = Int_to_ASCLL(minute/10);
    buff2[20] = Int_to_ASCLL(minute%10);
    buff2[29] = Int_to_ASCLL(duration/10000);
    buff2[30] = Int_to_ASCLL(duration%10000/1000);
    buff2[31] = Int_to_ASCLL(duration%1000/100);
    buff2[32] = Int_to_ASCLL(duration%100/10);
    buff2[33] = Int_to_ASCLL(duration%10);
    buff2[42] = Int_to_ASCLL(timing/1000000);
    buff2[43] = Int_to_ASCLL(timing%1000000/100000);
    buff2[44] = Int_to_ASCLL(timing%100000/10000);
    buff2[45] = Int_to_ASCLL(timing%10000/1000);
    buff2[46] = Int_to_ASCLL(timing%1000/100);
    buff2[47] = Int_to_ASCLL(timing%100/10);
    buff2[48] = Int_to_ASCLL(timing%10);

    Uart3_Send(buff2,51);
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ResetRecord(void)
{
  uint8_t buff[50] = "总数:00000次,最新时间:2019年01月01日 01时01分01秒";
  uint8_t temp[10] = {0};
  uint16_t times = 0;    

  Read_DebugResetRecord(temp);
  times = temp[0]*0x100 + temp[1];
  
  buff[5] = Int_to_ASCLL(times/10000);
  buff[6] = Int_to_ASCLL(times%10000/1000);
  buff[7] = Int_to_ASCLL(times%1000/100);
  buff[8] = Int_to_ASCLL(times%100/10);
  buff[9] = Int_to_ASCLL(times%10);

  buff[24] = Int_to_ASCLL(temp[2]/10);
  buff[25] = Int_to_ASCLL(temp[2]%10);
  buff[28] = Int_to_ASCLL(temp[3]/10);
  buff[29] = Int_to_ASCLL(temp[3]%10);
  buff[32] = Int_to_ASCLL(temp[4]/10);
  buff[33] = Int_to_ASCLL(temp[4]%10);
  buff[37] = Int_to_ASCLL(temp[5]/10);
  buff[38] = Int_to_ASCLL(temp[5]%10);
  buff[41] = Int_to_ASCLL(temp[6]/10);
  buff[42] = Int_to_ASCLL(temp[6]%10);
  buff[45] = Int_to_ASCLL(temp[7]/10);
  buff[46] = Int_to_ASCLL(temp[7]%10);
  
  Uart3_Send(buff,49);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_SampleRecord(void)
{
  uint8_t buff[50] = "包数:000,首包地址:0000,下包地址:0000";
  uint8_t num = 0;
  uint16_t addr1 = 0,addr2 = 0;    

  num = HistoryData.Total;
  addr1 = HISTORY_DATA_START_ADDR + HistoryData.Front*HistoryDataSize;
  addr2 = HISTORY_DATA_START_ADDR + HistoryData.Rear*HistoryDataSize; 
  
  buff[5] = Int_to_ASCLL(num/100);
  buff[6] = Int_to_ASCLL(num%100/10);
  buff[7] = Int_to_ASCLL(num%10);

  buff[18] = Int_to_ASCLL(addr1/0x1000);
  buff[19] = Int_to_ASCLL(addr1%0x1000/0x100);
  buff[20] = Int_to_ASCLL(addr1%0x100/0x10);
  buff[21] = Int_to_ASCLL(addr1%0x10);
  buff[32] = Int_to_ASCLL(addr2/0x1000);
  buff[33] = Int_to_ASCLL(addr2%0x1000/0x100);
  buff[34] = Int_to_ASCLL(addr2%0x100/0x10);
  buff[35] = Int_to_ASCLL(addr2%0x10);
  
  Uart3_Send(buff,36);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ReportStatistics(void)
{
  uint8_t buff[64] = "启动:00000次,成功:00000次,失败:00000次";
  uint8_t temp[6] = {0};
  uint16_t times1 = 0,times2 = 0,times3 = 0;    

  Read_DebugReportStatistics(temp);
  times1 = temp[0]*0x100 + temp[1];
  times2 = temp[2]*0x100 + temp[3];
  times3 = temp[4]*0x100 + temp[5];
  
  buff[5] = Int_to_ASCLL(times1/10000);
  buff[6] = Int_to_ASCLL(times1%10000/1000);
  buff[7] = Int_to_ASCLL(times1%1000/100);
  buff[8] = Int_to_ASCLL(times1%100/10);
  buff[9] = Int_to_ASCLL(times1%10);
  
  buff[18] = Int_to_ASCLL(times2/10000);
  buff[19] = Int_to_ASCLL(times2%10000/1000);
  buff[20] = Int_to_ASCLL(times2%1000/100);
  buff[21] = Int_to_ASCLL(times2%100/10);
  buff[22] = Int_to_ASCLL(times2%10);
  
  buff[31] = Int_to_ASCLL(times3/10000);
  buff[32] = Int_to_ASCLL(times3%10000/1000);
  buff[33] = Int_to_ASCLL(times3%1000/100);
  buff[34] = Int_to_ASCLL(times3%100/10);
  buff[35] = Int_to_ASCLL(times3%10);
  
  Uart3_Send(buff,38);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ReportRecord(void)
{
  uint8_t buff[70] = "最新时间:2019年09月04日 08时38分00秒,结果:成功,故障步骤:00,故障码:000";
  uint8_t temp[10] = {0};
  uint16_t code = 0;

  Read_DebugReportRecord(temp);
  
  buff[11] = Int_to_ASCLL(temp[0]/10);
  buff[12] = Int_to_ASCLL(temp[0]%10);
  buff[15] = Int_to_ASCLL(temp[1]/10);
  buff[16] = Int_to_ASCLL(temp[1]%10);
  buff[19] = Int_to_ASCLL(temp[2]/10);
  buff[20] = Int_to_ASCLL(temp[2]%10);
  buff[24] = Int_to_ASCLL(temp[3]/10);
  buff[25] = Int_to_ASCLL(temp[3]%10);
  buff[28] = Int_to_ASCLL(temp[4]/10);
  buff[29] = Int_to_ASCLL(temp[4]%10);
  buff[32] = Int_to_ASCLL(temp[5]/10);
  buff[33] = Int_to_ASCLL(temp[5]%10);
  
  if(temp[6] == 1)
  {
    Uart3_Send(buff,46);
  }
  else if(temp[6] == 2)
  {
    memcpy(&buff[42],"失败",4);
    buff[56] = Int_to_ASCLL(temp[7]/10);
    buff[57] = Int_to_ASCLL(temp[7]%10);
    code = temp[8]*0x100 + temp[9];
    buff[66] = Int_to_ASCLL(code/100);
    buff[67] = Int_to_ASCLL(code%100/10);
    buff[68] = Int_to_ASCLL(code%10);
    Uart3_Send(buff,69);
  } 
  else
  {
    Uart3_Send("未知",4);
  }
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_ClearResetRecord(void)
{
  uint8_t buff[10] = {0};
  WriteRom(DEBUG_RESET_RECORD_ADDR,buff,8);
  Uart3_Send("清除成功",8);
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
void Debug_ClearReportStatistics(void)
{
  uint8_t buff[10] = {0};
  WriteRom(DEBUG_REPORT_STATISTICS_ADDR,buff,6);
  Uart3_Send("清除成功",8);
}
