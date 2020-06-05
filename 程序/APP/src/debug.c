/*********************************************************************************
文件包含区
*********************************************************************************/
#include "debug.h"
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
//Debug状态指示灯
void Debug_LED_OFF(void)       
{
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}
void Debug_LedRun(void)        
{
  GPIO_ToggleBits(GPIOD, GPIO_Pin_7);
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
  USART3_Config(9600);  
  SoftTimer_CreateTimer(ONCE,30000,
                        Debug_DeInit); 
  SoftTimer_CreateTimer(CONTINUOUS, 1000, Debug_LedRun); 
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
  SoftTimer_DeleteTimer(Debug_DeInit);
  SoftTimer_DeleteTimer(Debug_LedRun);
  Debug_LED_OFF();
  
  USART3_Free();
  USART_DeInit(USART3);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3,DISABLE);
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_Out_PP_Low_Slow);
  
  DevicePara.Mode.ManualDebug = SLEEP;
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
  uint8_t length = 0;
  bool valid = FALSE;
  
  if(Usart3.RxPend != FALSE)//判断有数据
  { 
    length = USART3_RX(buff);
    
    if(strstr((const char *)buff,"读固件版本") != NULL)       //读EEPROM状态
    {
      valid = TRUE;
      Debug_FirmwareVersion();
    }
    else if(strstr((const char *)buff,"读EEPROM状态") != NULL)       //读EEPROM状态
    {
      valid = TRUE;
      Debug_EepromStatus();
    }
    else if(strstr((const char *)buff,"读电压温度") != NULL)   //读电压温度
    {
      valid = TRUE;
      Debug_VolTemp();
    }
    else if(strstr((const char *)buff,"读时间") != NULL)       //读时间
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
      USART3_TX("已结束",8);
      SoftTimer_CreateTimer(ONCE,1000,
                            Debug_DeInit);
    }
    
    if(valid != FALSE)
    {
      SoftTimer_CreateTimer(ONCE,30000,
                            Debug_DeInit); 
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
void Debug_FirmwareVersion(void)
{
  USART3_TX("V1.2.0",6);
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
  uint16_t addr = 0x17F0;
  uint8_t wbuff[10] = {0};
  uint8_t rbuff[10] = {0};
  
  RTC_DateTypeDef date;    
  RTC_TimeTypeDef time;

  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  
  wbuff[0] = date.RTC_Year;
  wbuff[1] = date.RTC_Month;
  wbuff[2] = date.RTC_Date;
  wbuff[3] = time.RTC_Hours;
  wbuff[4] = time.RTC_Minutes; 
  wbuff[5] = time.RTC_Seconds; 
    
  DataProcess_WriteData(addr,wbuff,6);
  DataProcess_ReadData(addr,rbuff,6);
  if( 0 == strncmp((const char *)wbuff,(const char *)rbuff,6) )
  {
    USART3_TX("读写成功",8);
  }
  else
  {
    USART3_TX("读写失败",8);
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
void Debug_ReadFlow(void)
{
//  uint8_t buff[32] = "正向水量:000000.000m3,反向水量:000000.000m3";                 
//  uint32_t ForwardInteger = 0; 
//  uint16_t ForwarDecimal = 0; 
//  uint32_t ReverseInteger = 0; 
//  uint16_t ReverseDecimal = 0; 
//
//  switch(DevicePara.Sensor.Ratio)
//  {
//  case RATIO_0:                    
//    {
//      ForwardInteger = DevicePara.ForwardFlow.flow32;
//      ForwarDecimal = 0;
//      ReverseInteger = DevicePara.ReverseFlow.flow32;
//      ReverseDecimal = 0;
//    }
//    break;
//  case RATIO_1:                    
//    { 
//      ForwardInteger = DevicePara.ForwardFlow.flow32/10;
//      ForwarDecimal = DevicePara.ForwardFlow.flow32%10;
//      ReverseInteger = DevicePara.ReverseFlow.flow32/10;
//      ReverseDecimal = DevicePara.ReverseFlow.flow32%10;
//    }
//    break;
//  case RATIO_2:                         
//    {  
//      ForwardInteger = DevicePara.ForwardFlow.flow32/100;
//      ForwarDecimal = DevicePara.ForwardFlow.flow32%100;
//      ReverseInteger = DevicePara.ReverseFlow.flow32/100;
//      ReverseDecimal = DevicePara.ReverseFlow.flow32%100;
//    }
//    break;
//  case RATIO_3:                   
//    {  
//      ForwardInteger = DevicePara.ForwardFlow.flow32/1000;
//      ForwarDecimal = DevicePara.ForwardFlow.flow32%1000;
//      ReverseInteger = DevicePara.ReverseFlow.flow32/1000;
//      ReverseDecimal = DevicePara.ReverseFlow.flow32%1000;
//    }
//    break;
//  default:
//    {
//    }
//    break;
//  }
//  
//  buff[9] = Int_to_ASCLL(ForwardInteger%1000000/100000);
//  buff[10] = Int_to_ASCLL(ForwardInteger%100000/10000);
//  buff[11] = Int_to_ASCLL(ForwardInteger%10000/1000);
//  buff[12] = Int_to_ASCLL(ForwardInteger%1000/100);
//  buff[13] = Int_to_ASCLL(ForwardInteger%100/10);
//  buff[14] = Int_to_ASCLL(ForwardInteger%10);
//  
//  buff[16] = Int_to_ASCLL(ForwarDecimal/100);
//  buff[17] = Int_to_ASCLL(ForwarDecimal%100/10);
//  buff[18] = Int_to_ASCLL(ForwarDecimal%10);
//  
//  buff[31] = Int_to_ASCLL(ForwardInteger%1000000/100000);
//  buff[32] = Int_to_ASCLL(ForwardInteger%100000/10000);
//  buff[33] = Int_to_ASCLL(ForwardInteger%10000/1000);
//  buff[34] = Int_to_ASCLL(ForwardInteger%1000/100);
//  buff[35] = Int_to_ASCLL(ForwardInteger%100/10);
//  buff[36] = Int_to_ASCLL(ForwardInteger%10);
//  
//  buff[38] = Int_to_ASCLL(ForwarDecimal/100);
//  buff[39] = Int_to_ASCLL(ForwarDecimal%100/10);
//  buff[40] = Int_to_ASCLL(ForwarDecimal%10);
//  
//  USART3_TX(buff,43);
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

  voltage = DevicePara.Voltage;
  temp = DevicePara.Temp; 
  
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
  
  USART3_TX(buff,22);
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

  USART3_TX(buff,27);
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
  uint8_t buff[70] = "IMEI:123456789012345,IMSI:123456789012345,CCID:00000000000000000000";
  
  memcpy(&buff[5],BC95.IMEI,15);
  memcpy(&buff[26],BC95.IMSI,15);
  memcpy(&buff[47],BC95.CCID,20);

  USART3_TX(buff,67);
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
  uint8_t buff[80] = "CSQ:00,RSRP:-000,SNR:000,ECL:000,CELLID:0000000000;EARFCN:00000,PCI:00000";  
  buff[4] = Int_to_ASCLL(BC95.CSQ/10);
  buff[5] = Int_to_ASCLL(BC95.CSQ%10);
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
  buff[40] = Int_to_ASCLL(BC95.CELLID/1000000000);
  buff[41] = Int_to_ASCLL(BC95.CELLID%1000000000/100000000);
  buff[42] = Int_to_ASCLL(BC95.CELLID%100000000/10000000);
  buff[43] = Int_to_ASCLL(BC95.CELLID%10000000/1000000);
  buff[44] = Int_to_ASCLL(BC95.CELLID%1000000/100000);
  buff[45] = Int_to_ASCLL(BC95.CELLID%100000/10000);
  buff[46] = Int_to_ASCLL(BC95.CELLID%10000/1000);
  buff[47] = Int_to_ASCLL(BC95.CELLID%1000/100);
  buff[48] = Int_to_ASCLL(BC95.CELLID%100/10);
  buff[49] = Int_to_ASCLL(BC95.CELLID%10);
  
  buff[58] = Int_to_ASCLL(BC95.EARFCN%100000/10000);
  buff[59] = Int_to_ASCLL(BC95.EARFCN%10000/1000);
  buff[60] = Int_to_ASCLL(BC95.EARFCN%1000/100);
  buff[61] = Int_to_ASCLL(BC95.EARFCN%100/10);
  buff[62] = Int_to_ASCLL(BC95.EARFCN%10);
  
  buff[68] = Int_to_ASCLL(BC95.PCI%100000/10000);
  buff[69] = Int_to_ASCLL(BC95.PCI%10000/1000);
  buff[70] = Int_to_ASCLL(BC95.PCI%1000/100);
  buff[71] = Int_to_ASCLL(BC95.PCI%100/10);
  buff[72] = Int_to_ASCLL(BC95.PCI%10);

  USART3_TX(buff,73);
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
  uint8_t buff[32] = "频率:00000分,计时:00000分";
  uint16_t freq = 0;
  uint32_t timer = 0;
  
  freq = DevicePara.SampleParas.Frequency;
  timer = DevicePara.SampleParas.Timer;
  
  buff[5] = Int_to_ASCLL(freq/10000);
  buff[6] = Int_to_ASCLL(freq%10000/1000);
  buff[7] = Int_to_ASCLL(freq%1000/100);
  buff[8] = Int_to_ASCLL(freq%100/10);
  buff[9] = Int_to_ASCLL(freq%10);
  
  buff[18] = Int_to_ASCLL(timer/10000);
  buff[19] = Int_to_ASCLL(timer%10000/1000);
  buff[20] = Int_to_ASCLL(timer%1000/100);
  buff[21] = Int_to_ASCLL(timer%100/10);
  buff[22] = Int_to_ASCLL(timer%10);

  USART3_TX(buff,25);
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
  uint8_t buff1[40] = "模式:周期,频率:00000分,计时:00000分";
  uint8_t buff2[60] = "模式:定时,时间:08时08分";
  uint16_t freq = 0;
  uint32_t timer = 0;
  uint8_t hour = 0,minute = 0;
  
  if(DevicePara.ReportParas.StartTimeValid == FALSE)
  {
    freq = DevicePara.ReportParas.Frequency;
    timer = DevicePara.ReportParas.Timer;
    
    buff1[15] = Int_to_ASCLL(freq/10000);
    buff1[16] = Int_to_ASCLL(freq%10000/1000);
    buff1[17] = Int_to_ASCLL(freq%1000/100);
    buff1[18] = Int_to_ASCLL(freq%100/10);
    buff1[19] = Int_to_ASCLL(freq%10);
    buff1[28] = Int_to_ASCLL(timer/10000);
    buff1[29] = Int_to_ASCLL(timer%10000/1000);
    buff1[30] = Int_to_ASCLL(timer%1000/100);
    buff1[31] = Int_to_ASCLL(timer%100/10);
    buff1[32] = Int_to_ASCLL(timer%10);

    USART3_TX(buff1,35);
  }
  else
  {
    hour = DevicePara.ReportParas.StartTimeHour;
    minute = DevicePara.ReportParas.StartTimeMinute;
    
    buff2[15] = Int_to_ASCLL(hour/10);
    buff2[16] = Int_to_ASCLL(hour%10);
    buff2[19] = Int_to_ASCLL(minute/10);
    buff2[20] = Int_to_ASCLL(minute%10);
	
    USART3_TX(buff2,23);
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
  uint8_t buff[70] = "00000,2019.01.01 01:01:01//2020.01.01 00:00:00//2020.01.01 00:00:00";
  uint8_t temp[24] = {0};
  uint16_t times = 0;    

  DataPocess_ReadDebugResetRecord(temp);
  times = temp[0]*0x100 + temp[1];
  
  buff[0] = Int_to_ASCLL(times/10000);
  buff[1] = Int_to_ASCLL(times%10000/1000);
  buff[2] = Int_to_ASCLL(times%1000/100);
  buff[3] = Int_to_ASCLL(times%100/10);
  buff[4] = Int_to_ASCLL(times%10);

  buff[8] = Int_to_ASCLL(temp[2]/10);
  buff[9] = Int_to_ASCLL(temp[2]%10);
  buff[11] = Int_to_ASCLL(temp[3]/10);
  buff[12] = Int_to_ASCLL(temp[3]%10);
  buff[14] = Int_to_ASCLL(temp[4]/10);
  buff[15] = Int_to_ASCLL(temp[4]%10);
  buff[17] = Int_to_ASCLL(temp[5]/10);
  buff[18] = Int_to_ASCLL(temp[5]%10);
  buff[20] = Int_to_ASCLL(temp[6]/10);
  buff[21] = Int_to_ASCLL(temp[6]%10);
  buff[23] = Int_to_ASCLL(temp[7]/10);
  buff[24] = Int_to_ASCLL(temp[7]%10);
  
  buff[29] = Int_to_ASCLL(temp[8]/10);
  buff[30] = Int_to_ASCLL(temp[8]%10);
  buff[32] = Int_to_ASCLL(temp[9]/10);
  buff[33] = Int_to_ASCLL(temp[9]%10);
  buff[35] = Int_to_ASCLL(temp[10]/10);
  buff[36] = Int_to_ASCLL(temp[10]%10);
  buff[38] = Int_to_ASCLL(temp[11]/10);
  buff[39] = Int_to_ASCLL(temp[11]%10);
  buff[41] = Int_to_ASCLL(temp[12]/10);
  buff[42] = Int_to_ASCLL(temp[12]%10);
  buff[44] = Int_to_ASCLL(temp[13]/10);
  buff[45] = Int_to_ASCLL(temp[13]%10);
  
  buff[50] = Int_to_ASCLL(temp[14]/10);
  buff[51] = Int_to_ASCLL(temp[14]%10);
  buff[53] = Int_to_ASCLL(temp[15]/10);
  buff[54] = Int_to_ASCLL(temp[15]%10);
  buff[56] = Int_to_ASCLL(temp[16]/10);
  buff[57] = Int_to_ASCLL(temp[16]%10);
  buff[59] = Int_to_ASCLL(temp[17]/10);
  buff[60] = Int_to_ASCLL(temp[17]%10);
  buff[62] = Int_to_ASCLL(temp[18]/10);
  buff[63] = Int_to_ASCLL(temp[18]%10);
  buff[65] = Int_to_ASCLL(temp[19]/10);
  buff[66] = Int_to_ASCLL(temp[19]%10);
  
  USART3_TX(buff,67);
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
  uint8_t buff[40] = "总数:0000,首条地址:0000,下条地址:0000";
  uint16_t total = 0;               //条数
  uint16_t addr1 = 0,addr2 = 0;           
  
  total = DevicePara.SampleParas.Queue.Total;
  addr1 = SAMPLE_DATA_START_ADDR + DevicePara.SampleParas.Queue.Front*SampleDataEachSize;      //首条地址
  addr2 = SAMPLE_DATA_START_ADDR + DevicePara.SampleParas.Queue.Rear*SampleDataEachSize;       //下条地址                   
    
  buff[5] = Int_to_ASCLL(total/1000);
  buff[6] = Int_to_ASCLL(total%1000/100);
  buff[7] = Int_to_ASCLL(total%100/10);
  buff[8] = Int_to_ASCLL(total%10);
  buff[19] = Int_to_ASCLL(addr1/0x1000);
  buff[20] = Int_to_ASCLL(addr1%0x1000/0x100);
  buff[21] = Int_to_ASCLL(addr1%0x100/0x10);
  buff[22] = Int_to_ASCLL(addr1%0x10);
  buff[33] = Int_to_ASCLL(addr2/0x1000);
  buff[34] = Int_to_ASCLL(addr2%0x1000/0x100);
  buff[35] = Int_to_ASCLL(addr2%0x100/0x10);
  buff[36] = Int_to_ASCLL(addr2%0x10);
  
  USART3_TX(buff,37);
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

  DataPocess_ReadDebugReportStatistics(temp);
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
  
  USART3_TX(buff,38);
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

  DataPocess_ReadDebugReportRecord(temp);
  
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
    USART3_TX(buff,46);
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
    USART3_TX(buff,69);
  } 
  else
  {
    memcpy(&buff[42],"未知",4);
    USART3_TX(buff,46);
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
  uint8_t buff[16] = {0};
  DataProcess_WriteData(DEBUG_RESET_RECORD_ADDR,buff,8);
  DataProcess_WriteData(DEBUG_RESET_WAKE_TIMEOUT_ADDR,buff,12);
  USART3_TX("清除成功",8);
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
  DataProcess_WriteData(DEBUG_REPORT_STATISTICS_ADDR,buff,6);
  USART3_TX("清除成功",8);
}
