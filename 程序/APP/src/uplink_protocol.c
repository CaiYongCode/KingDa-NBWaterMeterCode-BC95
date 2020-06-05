/*******************************************************************************
Copyright: 
File name: uplink_protocol.c
Description: 上行通信协议相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "uplink_protocol.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
UplinkProtocol_Struct UP;
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
 Description:   //初始化
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_Init(void)
{
  SoftTimer_CreateTimer(ONCE,360000,
                        UplinkProtocol_TimeoutEnd);
  BC95_Init(); 
}
/*******************************************************************************
 Function:      //
 Description:   //取消初始化为默认复位状态
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_DeInit(void)
{
  SoftTimer_DeleteTimer(UplinkProtocol_TimeoutEnd);
  SoftTimer_DeleteTimer(UplinkProtocol_Timeout);
  SoftTimer_DeleteTimer(UplinkProtocol_DeInit);
  
  UP.MsgId = MessageId_Idle;
  UP.IncidentPend = FALSE;
  UP.TimeoutTimes = 0;
  memset(UP.TxBuffer,0,UPLINK_TX_MAX);
  
  SoftTimer_DeleteTimer(BC95_InquireMsgRecv); 
  BC95_ShutDown();
}
/*******************************************************************************
 Function:      //
 Description:   //超时结束
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_TimeoutEnd(void)
{
  UplinkProtocol_DeInit();
}
/*******************************************************************************
 Function:      //
 Description:   //开始上报,上报数据必须以设备状态为第一条
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_StartReport(void)
{
  UP.MsgId = MessageId_0001;
  UP.IncidentPend = TRUE;
}
/*******************************************************************************
 Function:      //
 Description:   //上行协议发送进程
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_TxProcess(void)
{ 
  if(UP.IncidentPend != FALSE)    //检测是否有事件挂起
  {
    UP.IncidentPend = FALSE;      //清除事件挂起
    switch(UP.MsgId)
    {
    case MessageId_0001:                    //上报状态数据
      {
        UplinkProtocol_ReportMessageId_0001();
        SoftTimer_CreateTimer(ONCE, UPLINK_TIMEROUT_TIME, 
                              UplinkProtocol_Timeout);
      }
      break;
    case MessageId_0002:                    //上报采样数据
      { 
        if(DevicePara.SampleParas.Queue.Total > 0)
        {
          UplinkProtocol_ReportMessageId_0002();
          SoftTimer_CreateTimer(ONCE, UPLINK_TIMEROUT_TIME, 
                                UplinkProtocol_Timeout);
        }
        else
        {
          UP.MsgId++;
          UP.IncidentPend = TRUE;
        }
      }                         
      break;
    default:
      {
        SoftTimer_CreateTimer(ONCE, 5000, 
                                UplinkProtocol_DeInit);
        BC95_InquireMsgRecv();
      }
      break;
    }
  } 
}
/*******************************************************************************
 Function:      //
 Description:   //上行协议发送成功
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_TxSuccess(void)
{
  switch(UP.MsgId)
  {
  case MessageId_0001:                    //上报状态数据
    {
      SoftTimer_DeleteTimer(UplinkProtocol_Timeout);
      UP.TimeoutTimes = 0;
      
      DevicePara.ReportParas.Timeout = 0;
      DataPocess_WriteDebugReportStatistics(1);      //成功次数+1
      DataPocess_WriteDebugReportRecord(1);          //保存成功记录
      
      UP.MsgId = MessageId_0002;
      UP.IncidentPend = TRUE;
    }
    break;
  case MessageId_0002:                    //上报采样数据
    { 
      DataPocess_ClearSampleData(1);
      SoftTimer_DeleteTimer(UplinkProtocol_Timeout);
      UP.TimeoutTimes = 0;
      UP.IncidentPend = TRUE;
    }
    break;
  default:
    {
      UP.MsgId = MessageId_Idle;
      UP.IncidentPend = TRUE;
    }
    break;
  }
}
/*******************************************************************************
 Function:      //
 Description:   //上报状态数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_ReportMessageId_0001(void)
{
  uint8_t i = 0;
  uint8_t valueH = 0;
  RTC_DateTypeDef date;
  RTC_TimeTypeDef time;                      
  FlowUnion flow;
  uint16_t year = 0;
   
  
  flow.flow32 = DevicePara.ForwardFlow.flow32;
  RTC_GetDate(RTC_Format_BIN, &date);
  RTC_GetTime(RTC_Format_BIN, &time);
  DevicePara.Voltage = Detect_Voltage();
  DevicePara.Temp = Detect_Temp(); 
  
  memcpy(UP.TxBuffer,"AT+NMGS=79,00",13);

  
  //当前累积流量
  UP.TxBuffer[13] = Int_to_ASCLL(flow.flow8[0]/0x10);
  UP.TxBuffer[14] = Int_to_ASCLL(flow.flow8[0]%0x10);
  UP.TxBuffer[15] = Int_to_ASCLL(flow.flow8[1]/0x10);
  UP.TxBuffer[16] = Int_to_ASCLL(flow.flow8[1]%0x10);
  UP.TxBuffer[17] = Int_to_ASCLL(flow.flow8[2]/0x10);
  UP.TxBuffer[18] = Int_to_ASCLL(flow.flow8[2]%0x10);
  UP.TxBuffer[19] = Int_to_ASCLL(flow.flow8[3]/0x10);
  UP.TxBuffer[20] = Int_to_ASCLL(flow.flow8[3]%0x10);

  //结算日累积流量
  memset(&UP.TxBuffer[21],0x30,8);
  
  //电池电压
  UP.TxBuffer[29] = Int_to_ASCLL(DevicePara.Voltage/0x1000);
  UP.TxBuffer[30] = Int_to_ASCLL(DevicePara.Voltage%0x1000/0x100);
  UP.TxBuffer[31] = Int_to_ASCLL(DevicePara.Voltage%0x100/0x10);
  UP.TxBuffer[32] = Int_to_ASCLL(DevicePara.Voltage%0x10);
  
  //信号强度
  UP.TxBuffer[33] = Int_to_ASCLL(BC95.CSQ/0x10);
  UP.TxBuffer[34] = Int_to_ASCLL(BC95.CSQ%0x10);
  //温度 
  UP.TxBuffer[35] = Int_to_ASCLL((uint8_t)DevicePara.Temp/0x10);
  UP.TxBuffer[36] = Int_to_ASCLL((uint8_t)DevicePara.Temp%0x10);
  
  //年
  year = 2000+date.RTC_Year;
  UP.TxBuffer[37] = Int_to_ASCLL(year/0x1000);;
  UP.TxBuffer[38] = Int_to_ASCLL(year%0x1000/0x100);;
  UP.TxBuffer[39] = Int_to_ASCLL(year%0x100/0x10);
  UP.TxBuffer[40] = Int_to_ASCLL(year%0x10); 
  //月
  UP.TxBuffer[41] = Int_to_ASCLL(date.RTC_Month/0x10);
  UP.TxBuffer[42] = Int_to_ASCLL(date.RTC_Month%0x10);
  //日
  UP.TxBuffer[43] = Int_to_ASCLL(date.RTC_Date/0x10);
  UP.TxBuffer[44] = Int_to_ASCLL(date.RTC_Date%0x10);
  //时
  UP.TxBuffer[45] = Int_to_ASCLL(time.RTC_Hours/0x10);
  UP.TxBuffer[46] = Int_to_ASCLL(time.RTC_Hours%0x10);
  //分
  UP.TxBuffer[47] = Int_to_ASCLL(time.RTC_Minutes/0x10);
  UP.TxBuffer[48] = Int_to_ASCLL(time.RTC_Minutes%0x10);
  //秒
  UP.TxBuffer[49] = Int_to_ASCLL(time.RTC_Seconds/0x10);
  UP.TxBuffer[50] = Int_to_ASCLL(time.RTC_Seconds%0x10);
  //表号
  for(i = 0;i < 14;i++)
  {
    UP.TxBuffer[51+i*2] = 0x33;
    UP.TxBuffer[51+i*2+1] = 0x30;
  }
   //结算日期
  UP.TxBuffer[79] = 0x30;
  UP.TxBuffer[80] = 0x30;
  //上报频率
  UP.TxBuffer[81] = Int_to_ASCLL(DevicePara.ReportParas.Frequency/0x1000);
  UP.TxBuffer[82] = Int_to_ASCLL(DevicePara.ReportParas.Frequency%0x1000/0x100);
  UP.TxBuffer[83] = Int_to_ASCLL(DevicePara.ReportParas.Frequency%0x100/0x10);
  UP.TxBuffer[84] = Int_to_ASCLL(DevicePara.ReportParas.Frequency%0x10);
  //告警电压
  UP.TxBuffer[85] = 0x30;
  UP.TxBuffer[86] = 0x30;
  UP.TxBuffer[87] = 0x30;
  UP.TxBuffer[88] = 0x30;
  //阀门状态
  UP.TxBuffer[89] = 0x30;
  UP.TxBuffer[90] = 0x30;
  //霍尔状态
  UP.TxBuffer[91] = Int_to_ASCLL(DevicePara.SensorError/0x10);
  UP.TxBuffer[92] = Int_to_ASCLL(DevicePara.SensorError%0x10);
  //IMEI
  UP.TxBuffer[93] = Int_to_ASCLL(BC95.IMEI[0]/0x10);
  UP.TxBuffer[94] = Int_to_ASCLL(BC95.IMEI[0]%0x10);
  UP.TxBuffer[95] = Int_to_ASCLL(BC95.IMEI[1]/0x10);
  UP.TxBuffer[96] = Int_to_ASCLL(BC95.IMEI[1]%0x10);
  UP.TxBuffer[97] = Int_to_ASCLL(BC95.IMEI[2]/0x10);
  UP.TxBuffer[98] = Int_to_ASCLL(BC95.IMEI[2]%0x10);
  UP.TxBuffer[99] = Int_to_ASCLL(BC95.IMEI[3]/0x10);
  UP.TxBuffer[100] = Int_to_ASCLL(BC95.IMEI[3]%0x10);
  UP.TxBuffer[101] = Int_to_ASCLL(BC95.IMEI[4]/0x10);
  UP.TxBuffer[102] = Int_to_ASCLL(BC95.IMEI[4]%0x10);
  UP.TxBuffer[103] = Int_to_ASCLL(BC95.IMEI[5]/0x10);
  UP.TxBuffer[104] = Int_to_ASCLL(BC95.IMEI[5]%0x10);
  UP.TxBuffer[105] = Int_to_ASCLL(BC95.IMEI[6]/0x10);
  UP.TxBuffer[106] = Int_to_ASCLL(BC95.IMEI[6]%0x10);
  UP.TxBuffer[107] = Int_to_ASCLL(BC95.IMEI[7]/0x10);
  UP.TxBuffer[108] = Int_to_ASCLL(BC95.IMEI[7]%0x10);
  UP.TxBuffer[109] = Int_to_ASCLL(BC95.IMEI[8]/0x10);
  UP.TxBuffer[110] = Int_to_ASCLL(BC95.IMEI[8]%0x10);
  UP.TxBuffer[111] = Int_to_ASCLL(BC95.IMEI[9]/0x10);
  UP.TxBuffer[112] = Int_to_ASCLL(BC95.IMEI[9]%0x10);
  UP.TxBuffer[113] = Int_to_ASCLL(BC95.IMEI[10]/0x10);
  UP.TxBuffer[114] = Int_to_ASCLL(BC95.IMEI[10]%0x10);
  UP.TxBuffer[115] = Int_to_ASCLL(BC95.IMEI[11]/0x10);
  UP.TxBuffer[116] = Int_to_ASCLL(BC95.IMEI[11]%0x10);
  UP.TxBuffer[117] = Int_to_ASCLL(BC95.IMEI[12]/0x10);
  UP.TxBuffer[118] = Int_to_ASCLL(BC95.IMEI[12]%0x10);
  UP.TxBuffer[119] = Int_to_ASCLL(BC95.IMEI[13]/0x10);
  UP.TxBuffer[120] = Int_to_ASCLL(BC95.IMEI[13]%0x10);
  UP.TxBuffer[121] = Int_to_ASCLL(BC95.IMEI[14]/0x10);
  UP.TxBuffer[122] = Int_to_ASCLL(BC95.IMEI[14]%0x10);
  //CCID
  UP.TxBuffer[123] = Int_to_ASCLL(BC95.CCID[0]/0x10);
  UP.TxBuffer[124] = Int_to_ASCLL(BC95.CCID[0]%0x10);
  UP.TxBuffer[125] = Int_to_ASCLL(BC95.CCID[1]/0x10);
  UP.TxBuffer[126] = Int_to_ASCLL(BC95.CCID[1]%0x10);
  UP.TxBuffer[127] = Int_to_ASCLL(BC95.CCID[2]/0x10);
  UP.TxBuffer[128] = Int_to_ASCLL(BC95.CCID[2]%0x10);
  UP.TxBuffer[129] = Int_to_ASCLL(BC95.CCID[3]/0x10);
  UP.TxBuffer[130] = Int_to_ASCLL(BC95.CCID[3]%0x10);
  UP.TxBuffer[131] = Int_to_ASCLL(BC95.CCID[4]/0x10);
  UP.TxBuffer[132] = Int_to_ASCLL(BC95.CCID[4]%0x10);
  UP.TxBuffer[133] = Int_to_ASCLL(BC95.CCID[5]/0x10);
  UP.TxBuffer[134] = Int_to_ASCLL(BC95.CCID[5]%0x10);
  UP.TxBuffer[135] = Int_to_ASCLL(BC95.CCID[6]/0x10);
  UP.TxBuffer[136] = Int_to_ASCLL(BC95.CCID[6]%0x10);
  UP.TxBuffer[137] = Int_to_ASCLL(BC95.CCID[7]/0x10);
  UP.TxBuffer[138] = Int_to_ASCLL(BC95.CCID[7]%0x10);
  UP.TxBuffer[139] = Int_to_ASCLL(BC95.CCID[8]/0x10);
  UP.TxBuffer[140] = Int_to_ASCLL(BC95.CCID[8]%0x10);
  UP.TxBuffer[141] = Int_to_ASCLL(BC95.CCID[9]/0x10);
  UP.TxBuffer[142] = Int_to_ASCLL(BC95.CCID[9]%0x10);
  UP.TxBuffer[143] = Int_to_ASCLL(BC95.CCID[10]/0x10);
  UP.TxBuffer[144] = Int_to_ASCLL(BC95.CCID[10]%0x10);
  UP.TxBuffer[145] = Int_to_ASCLL(BC95.CCID[11]/0x10);
  UP.TxBuffer[146] = Int_to_ASCLL(BC95.CCID[11]%0x10);
  UP.TxBuffer[147] = Int_to_ASCLL(BC95.CCID[12]/0x10);
  UP.TxBuffer[148] = Int_to_ASCLL(BC95.CCID[12]%0x10);
  UP.TxBuffer[149] = Int_to_ASCLL(BC95.CCID[13]/0x10);
  UP.TxBuffer[150] = Int_to_ASCLL(BC95.CCID[13]%0x10);
  UP.TxBuffer[151] = Int_to_ASCLL(BC95.CCID[14]/0x10);
  UP.TxBuffer[152] = Int_to_ASCLL(BC95.CCID[14]%0x10);
  UP.TxBuffer[153] = Int_to_ASCLL(BC95.CCID[15]/0x10);
  UP.TxBuffer[154] = Int_to_ASCLL(BC95.CCID[15]%0x10);
  UP.TxBuffer[155] = Int_to_ASCLL(BC95.CCID[16]/0x10);
  UP.TxBuffer[156] = Int_to_ASCLL(BC95.CCID[16]%0x10);
  UP.TxBuffer[157] = Int_to_ASCLL(BC95.CCID[17]/0x10);
  UP.TxBuffer[158] = Int_to_ASCLL(BC95.CCID[17]%0x10);
  UP.TxBuffer[159] = Int_to_ASCLL(BC95.CCID[18]/0x10);
  UP.TxBuffer[160] = Int_to_ASCLL(BC95.CCID[18]%0x10);
  UP.TxBuffer[161] = Int_to_ASCLL(BC95.CCID[19]/0x10);
  UP.TxBuffer[162] = Int_to_ASCLL(BC95.CCID[19]%0x10);
  
  //上次联网故障信息
  valueH = *((const unsigned char *)(BC95_ERROR_RECORD_ADD));
  UP.TxBuffer[163] = Int_to_ASCLL(valueH/0x10);
  UP.TxBuffer[164] = Int_to_ASCLL(valueH%0x10);
  //采样频率
  UP.TxBuffer[165] = Int_to_ASCLL(DevicePara.SampleParas.Frequency/0x1000);
  UP.TxBuffer[166] = Int_to_ASCLL(DevicePara.SampleParas.Frequency%0x1000/0x100);
  UP.TxBuffer[167] = Int_to_ASCLL(DevicePara.SampleParas.Frequency%0x100/0x10);
  UP.TxBuffer[168] = Int_to_ASCLL(DevicePara.SampleParas.Frequency%0x10);
  
  UP.TxBuffer[169] = '\r';
  UP.TxBuffer[170] = '\n';
  
  BC95_TxMessage_NMGS(UP.TxBuffer,171);
}
/*******************************************************************************
 Function:      //
 Description:   //上报采样数据
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_ReportMessageId_0002(void)
{
  uint8_t buff[16] = {0};
  uint16_t year = 0;
    
  DataPocess_ReadSampleData(buff,1);

  memcpy(UP.TxBuffer,"AT+NMGS=12,08",13);
  //累积流量
  UP.TxBuffer[13] = Int_to_ASCLL(buff[0]/0x10);
  UP.TxBuffer[14] = Int_to_ASCLL(buff[0]%0x10);
  UP.TxBuffer[15] = Int_to_ASCLL(buff[1]/0x10);
  UP.TxBuffer[16] = Int_to_ASCLL(buff[1]%0x10);
  UP.TxBuffer[17] = Int_to_ASCLL(buff[2]/0x10);
  UP.TxBuffer[18] = Int_to_ASCLL(buff[2]%0x10);
  UP.TxBuffer[19] = Int_to_ASCLL(buff[3]/0x10);
  UP.TxBuffer[20] = Int_to_ASCLL(buff[3]%0x10);
  //年
  year = 2000+buff[4];  
  UP.TxBuffer[21] = Int_to_ASCLL(year/0x1000);;
  UP.TxBuffer[22] = Int_to_ASCLL(year%0x1000/0x100);;
  UP.TxBuffer[23] = Int_to_ASCLL(year%0x100/0x10);
  UP.TxBuffer[24] = Int_to_ASCLL(year%0x10); 
  //月
  UP.TxBuffer[25] = Int_to_ASCLL(buff[5]/0x10);
  UP.TxBuffer[26] = Int_to_ASCLL(buff[5]%0x10);
  //日
  UP.TxBuffer[27] = Int_to_ASCLL(buff[6]/0x10);
  UP.TxBuffer[28] = Int_to_ASCLL(buff[6]%0x10);
  //时
  UP.TxBuffer[29] = Int_to_ASCLL(buff[7]/0x10);
  UP.TxBuffer[30] = Int_to_ASCLL(buff[7]%0x10);
  //分
  UP.TxBuffer[31] = Int_to_ASCLL(buff[8]/0x10);
  UP.TxBuffer[32] = Int_to_ASCLL(buff[8]%0x10);
  //秒
  UP.TxBuffer[33] = 0x30;
  UP.TxBuffer[34] = 0x30;
  
  UP.TxBuffer[35] = '\r';
  UP.TxBuffer[36] = '\n';
  
  BC95_TxMessage_NMGS(UP.TxBuffer,37);
}
/*******************************************************************************
 Function:      //
 Description:   //上行协议接收进程
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void UplinkProtocol_RxProcess(uint8_t *buff,uint16_t length)
{ 
  uint16_t temp = 0;
  RTC_DateTypeDef date;
  RTC_TimeTypeDef time; 
  
  switch(buff[0])
  {
    case 0x02:            //配置参数
      {//24,020004 3030303031383035303030303031 01 02D0 0140 001E
        //上报频率
        temp = buff[18]*0x100 + buff[19];
        if( (temp != DevicePara.ReportParas.Frequency)&&( temp > 0) )
        {
          DataProcess_WriteData(REPORT_FREQUENCY_ADDR,(uint8_t *)&temp,2);
          DataProcess_ReadReportParas();
        }
 
        //采样频率
        temp = buff[22]*0x100 + buff[23];
        if(temp != DevicePara.SampleParas.Frequency)
        {
          DataProcess_WriteData(SAMPLE_FREQUENCY_ADDR,(uint8_t *)&temp,2);
          DataProcess_ReadSampleParas();
        }
      }
      break;
    case 0x04:           //校准水量
      {//8,040003010000007B 
        memcpy(DevicePara.ForwardFlow.flow8,&buff[4],4);
        DataProcess_WriteFlow();                    //保存当前水量
      } 
      break;
    case 0x06:           //校准时间
      {//17,060001 3230313830313031303030303030
        //时间       
        date.RTC_Year = ASCLL_to_Int(buff[5])*10+ASCLL_to_Int(buff[6]);
        date.RTC_Month = (RTC_Month_TypeDef)(ASCLL_to_Int(buff[7])*10+ASCLL_to_Int(buff[8]));
        date.RTC_Date = ASCLL_to_Int(buff[9])*10+ASCLL_to_Int(buff[10]);
        
        time.RTC_Hours   = ASCLL_to_Int(buff[11])*10+ASCLL_to_Int(buff[12]);
        time.RTC_Minutes = ASCLL_to_Int(buff[13])*10+ASCLL_to_Int(buff[14]);
        time.RTC_Seconds = ASCLL_to_Int(buff[15])*10+ASCLL_to_Int(buff[16]);
        
        RTC_SetDate(RTC_Format_BIN, &date);
        RTC_SetTime(RTC_Format_BIN, &time);
      } 
      break;
    case 0x09:           //设置离散上报起始时间、离散上报时长
      {//17,090001 0600 0078 0000
        temp = buff[5]*0x100 + buff[6];
        if( (buff[3] < 24)&&(buff[4] < 60) 
           &&(temp > 0)&&(temp <= 1440) )
        {
          DataProcess_WriteData(FIRST_REPORT_ADDR,&buff[3],4);
          DataProcess_ReadReportParas();
        }
      } 
      break;
    default:
      break;
  }
  
  BC95_InquireMsgRecv();        //继续查询
}
/*******************************************************************************
 Function:      //
 Description:   //延时回调
 Input:         //
 Output:        //
 Return:        //
 Others:        //
*******************************************************************************/
void UplinkProtocol_Delay(void)
{
  UP.IncidentPend = TRUE;//标记挂起
}
/*******************************************************************************
 Function:      //
 Description:   //超时回调
 Input:         //
 Output:        //
 Return:        //
 Others:        //
*******************************************************************************/
void UplinkProtocol_Timeout(void)
{
  UP.TimeoutTimes++;
  if(UP.TimeoutTimes < 3)    //超时未超次数则重发
  {
    UP.IncidentPend = TRUE; 
  }
  else                                //否则关机
  {
    UP.TimeoutTimes = 0; 
    BC95_Reconnect();
  }
}  
/*******************************************************************************
 Function:      //
 Description:   //检查是否正在上报
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
bool UplinkProtocol_IsReporting(void)
{
  if( (DevicePara.Mode.PeriodicReport == SLEEP)
        &&(DevicePara.Mode.ManualReport == SLEEP)
          &&(DevicePara.Mode.AlarmReport == SLEEP) )
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}
/*************************************END**************************************/

