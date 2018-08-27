/*********************************************************************************
//概述：
//作者：大胡子书生     时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************/
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "CJT-188-2004.h"
#include "include.h"
//#include "..\inc\ValveControl.h"
/*********************************************************************************
常量定义区
*********************************************************************************/

/*********************************************************************************
公共变量定义区
*********************************************************************************/
const  unsigned char *CJT_188_MeterID = (unsigned char *)(CJT_188_ADD);
const  unsigned char Ctr_List[6] = {CTR_ReadData_ASK, CTR_ReadVerNo_ASK,CTR_ReadAddress_ASK, CTR_WriteData_ASK,
                                      CTR_WriteAddress_ASK, CTR_WriteOffset_ASK};
unsigned  char cjt_188_Valve_AckFlg = 0;

/*********************************************************************************
外部变量声明区
*********************************************************************************/
//extern const Valve_State *ValveState ;
extern NEAR Data_SourceType Pro_DataSource;
extern NEAR  struct Get_Cal_Str Cal;
/*********************************************************************************
私有变量定义区
*********************************************************************************/ 
typedef struct{
 unsigned char  flg;
 
 unsigned char  Preamble[CJT_188_PreambleLength];
 CJT_188_FrameHeadStruct  Head;
 union
{
   CJT_188_OkACK_Struct    OK;
   CJT8_188_ErrACK_Struct  ERR;
 }Data; 
 unsigned char sum;
 unsigned char Pause;
}CJT_188_SendBuff_Struct;
NEAR static CJT_188_SendBuff_Struct  cjt_188_sendbuff ;


static unsigned  char UpdataSER = 0;
/*********************************************************************************
测试变量定义区
*********************************************************************************/
/*********************************************************************************
内部函数定义区
*********************************************************************************/
ErrCodeType CJT_188_2004_frameVerify (void *pbuff, unsigned char length);
ErrCodeType CTR_ReadData_ACKFunc(CJT_188_AskFrameData_Struct* ask);
ErrCodeType CTR_ReadVerNo_ACKFunc(void *pbuff, CJT_188_SendBuff_Struct *outbuff);
ErrCodeType CTR_ReadAddress_ACKFunc(CJT_188_AskFrameData_Struct* ask);
ErrCodeType CTR_WriteData_ACKFunc(CJT_188_AskFrameData_Struct* input);
ErrCodeType CTR_WriteAddress_ACKFunc(CJT_188_AskFrameData_Struct* ask);

ErrCodeType send_MeterData (unsigned char ser);
ErrCodeType CJT_188_WriteValveState_func (CJT_188_AskFrameData_Struct* ask);
void BinToBCD (unsigned long data, unsigned char *pbuff, unsigned char w);
void CJT_188_SendOK_CallBack (unsigned char port, void *pbuff);
ErrCodeType CJT_188_SendStart (CJT_188_SendBuff_Struct *Outbuff);
ErrCodeType send_TempData (unsigned char ser);
ErrCodeType CTR_WriteOffset_ACKFunc(CJT_188_AskFrameData_Struct* ask);
ErrCodeType send_HistoryData (unsigned char ser,unsigned char num);
ErrCodeType send_ReadSelDate(unsigned char ser);
ErrCodeType send_ReadRecordDate(unsigned char ser);
ErrCodeType send_ReadIP1Date(unsigned char ser);
ErrCodeType send_ReadIP2Date(unsigned char ser);
ErrCodeType send_ReadBattey(unsigned char ser);
ErrCodeType send_ReadBatteyAlarm(unsigned char ser);
ErrCodeType send_ReadUpdataTime(unsigned char ser);
ErrCodeType send_ReadRSSI(unsigned char ser);
ErrCodeType CJT_188_WriteSelDate_func (CJT_188_AskFrameData_Struct* ask);
ErrCodeType CJT_188_WriteRecordDate_func (CJT_188_AskFrameData_Struct* ask);
ErrCodeType CJT_188_WriteTime_func (CJT_188_AskFrameData_Struct* ask);
ErrCodeType CJT_188_WriteIP_func (CJT_188_AskFrameData_Struct* ask,unsigned char num);
ErrCodeType CJT_188_WriteBatteyAlarm_func (CJT_188_AskFrameData_Struct* ask);
ErrCodeType CJT_188_WriteUpdataTime_func (CJT_188_AskFrameData_Struct* ask);
ErrCodeType CTR_AotoUpData_ACKFunc(CJT_188_AskFrameData_Struct* ask);
/*********************************************************************************
功能代码定义区
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_2004_InPut (void *pbuff, unsigned length)
{
 ErrCodeType err = NoErr;
 unsigned char itemp;
 CJT_188_AskFrameData_Struct* AskFrame;
 err = CJT_188_2004_frameVerify(pbuff, length);
 if(NoErr != err) 
 {return err;}
 itemp = 0;
 while (CJT_188_StartCharacter !=((unsigned char *)pbuff)[itemp])
 {itemp ++;}
 AskFrame =(CJT_188_AskFrameData_Struct *)(&((unsigned char *)pbuff)[itemp]);
 
 switch (AskFrame->Head.CTR.Byte)
 {
  case CTR_ReadData_ASK: //读数据
    { 
      err = CTR_ReadData_ACKFunc(AskFrame);
      break;
     }
  case CTR_ReadVerNo_ASK: //读版本
    { 
      //CTR_ReadVerNo_ACKFunc(pbuff);
      break; 
    }
  case CTR_ReadAddress_ASK: //读地址
    {
     if(DI_ReadAddress == AskFrame->DataHead.DI)
     {err = CTR_ReadAddress_ACKFunc(AskFrame);}
      break; 
    }
  case CTR_WriteData_ASK: //写数据
    { 
      err = CTR_WriteData_ACKFunc(AskFrame);
      //CTR_ReadVerNo_ACKFunc(frame + 1,&cjt_188_sendbuff);
      break; 
    }
  case CTR_WriteAddress_ASK: //写地址
    { 
      if(DI_WriteAddress == AskFrame->DataHead.DI)
      {err = CTR_WriteAddress_ACKFunc(AskFrame);}
      break; 
    }
  case CTR_WriteOffset_ASK: //写机电同步
    {
      if(DI_WriteOffset == AskFrame->DataHead.DI)
      {err = CTR_WriteOffset_ACKFunc(AskFrame);}
      break; 
    }
 case CTR_WriteData_ACK: //服务器端的应答
    {
      if(DI_AotoUpData == AskFrame->DataHead.DI)  //主动上传的应答
      {err = CTR_AotoUpData_ACKFunc(AskFrame);}
      break; 
    }
 default:
   {err = OperateCmd_err;}
 }
 return err;
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_AotoUpData_ACKFunc(CJT_188_AskFrameData_Struct* ask)   //主动上传返回函数
{
 
  RTC_TimeTypeDef   RTC_TimeStr_BCD;        //RTC时间结构体
  RTC_DateTypeDef   RTC_DateStr_BCD;        //RTC日期结构体

  RTC_TimeStructInit(&RTC_TimeStr_BCD);
  RTC_TimeStr_BCD.RTC_Hours   = ask->Data.Time.Hour;
  RTC_TimeStr_BCD.RTC_Minutes = ask->Data.Time.Min;
  RTC_TimeStr_BCD.RTC_Seconds = ask->Data.Time.Sec;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStr_BCD);

  //RTC_DateStr_BCD.RTC_WeekDay = RTC_Weekday_Thursday; //不要周
  RTC_DateStr_BCD.RTC_Date = ask->Data.Time.Day;
  RTC_DateStr_BCD.RTC_Month = (RTC_Month_TypeDef)ask->Data.Time.Mon;
  RTC_DateStr_BCD.RTC_Year = ask->Data.Time.Year_L;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStr_BCD);

  return NoErr;
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_2004_frameVerify (void *pbuff, unsigned char length)
{
  unsigned char itemp ;
  unsigned char itemp2 ;
  unsigned char itemp3 ;
  CJT_188_FrameHeadStruct *frame;
  
  itemp = 0;
  while (CJT_188_Preamble ==((unsigned char *)pbuff)[itemp])
  {itemp ++;}
  
  frame =(CJT_188_FrameHeadStruct *)(&((unsigned char *)pbuff)[itemp]);
  if(CJT_188_StartCharacter != frame->StartCharacter)
  {return FrameSync_err;}
  
  itemp += frame->Length;
  itemp += sizeof(CJT_188_FrameHeadStruct) + 2;
 
  if(length < itemp)
  {return Length_err;} 
  
  if((Locall_MeterType != frame->Type)&&(UnknownMeterType != frame->Type))
  {return FrameInvalid;}
  
  if(frame->Addr.MeterID[0] != CJT_188_MeterID[0])//判断地址为广播 如果为广播接收为0xaa 不可能和地址相等
  {
    itemp = 0;
    while(itemp < 7)
    {
     if(((unsigned char *)&(frame->Addr))[itemp]!= 0xAA)
     {return FrameInvalid;}
     else
     {itemp ++;}
    }  
  }
  else
  {
    itemp = 0;
    while(itemp < 7)
    {
     if(frame->Addr.MeterID[itemp]!= CJT_188_MeterID[itemp])
     {return FrameInvalid;}
     else
     {itemp ++;}
    }
  }
  
  itemp = 0;
  itemp2 = frame->Length + sizeof(CJT_188_FrameHeadStruct);
  itemp3 = 0;
  while(itemp < itemp2)
  {
    itemp3 +=  ((unsigned char *)frame)[itemp];
    itemp ++;
  }
  if(itemp3 != ((unsigned char *)frame)[itemp])
  {return Verify_err;}
 return NoErr; 
}

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_ReadData_ACKFunc(CJT_188_AskFrameData_Struct* ask)
{
 ErrCodeType err = NoErr;
 switch (ask->DataHead.DI)
 {
   case DI_ReadData :      //计量数据
     {err = send_MeterData (ask->DataHead.SER);  
       break;
     }
   case DI_ReadHistData_1 :        //历史计量数据1
     {
       err = send_HistoryData (ask->DataHead.SER,0);
       break;
     }
   case DI_ReadHistData_2 :         //历史计量数据2
     {
       err = send_HistoryData (ask->DataHead.SER,1);
       break;
     }
   case DI_ReadHistData_3 :        //历史计量数据3
     {
       err = send_HistoryData (ask->DataHead.SER,2);
       break;
     }
   case DI_ReadHistData_4 :      //历史计量数据4
     {
       err = send_HistoryData (ask->DataHead.SER,3);
       break;
     }
   case DI_ReadHistData_5 :       //历史计量数据5
     {
       err = send_HistoryData (ask->DataHead.SER,4);
       break;
     }
   case DI_ReadHistData_6 :         //历史计量数据6
     {
       err = send_HistoryData (ask->DataHead.SER,5);
       break;
     }
   case DI_ReadHistData_7 :        //历史计量数据7
     {
       err = send_HistoryData (ask->DataHead.SER,6);
       break;
     }
   case DI_ReadHistData_8 :       //历史计量数据8
     {
       err = send_HistoryData (ask->DataHead.SER,7);
       break;
     }
   case DI_ReadHistData_9 :       //历史计量数据9
     {
       err = send_HistoryData (ask->DataHead.SER,8);
       break;
     }
   case DI_ReadHistData_10 :     //历史计量数据10
     {
       err = send_HistoryData (ask->DataHead.SER,9);
       break;
     }
   case DI_ReadHistData_11 :    //历史计量数据11
     {
       err = send_HistoryData (ask->DataHead.SER,10);
       break;
     }
   case DI_ReadHistData_12 :     //历史计量数据12
     {
       err = send_HistoryData (ask->DataHead.SER,11);
       break;
     }
   case DI_ReadPriceList :       //读价格表
     {break;}
   case DI_ReadSelDate :         //读结算日
     {
       send_ReadSelDate(ask->DataHead.SER);
       break;
     }
   case DI_ReadRecordDate :      //读抄表日
     {
       send_ReadRecordDate(ask->DataHead.SER);
       break;
     }
   case DI_ReadRMoney :          //读购入金额
     {break;}
   case DI_ReadVerNo :           //读秘钥版本号
     {break;}
   case DI_ReadTemp :            //读温度数据
     {
       send_TempData (ask->DataHead.SER);
       break;
     }
   case DI_ReadIP1 :            //读IP1的数据
     {
       send_ReadIP1Date (ask->DataHead.SER);
       break;
     }
   case DI_ReadIP2 :            //读IP2的数据
     {
       send_ReadIP2Date (ask->DataHead.SER);
       break;
     }
   case DI_ReadBattey :            //读电池电压
     {
       send_ReadBattey (ask->DataHead.SER);
       break;
     }
   case DI_ReadBatteyAlarm :            //读电池报警值
     {
       send_ReadBatteyAlarm (ask->DataHead.SER);
       break;
     }
   case DI_ReadUpdataTime:
    {
      send_ReadUpdataTime(ask->DataHead.SER);
      break;
    }
   case DI_ReadRSSI:
    {
      send_ReadRSSI(ask->DataHead.SER);
      break;
    }
   default :
     {err = OperateCmd_err;break;}
 }
 return err;  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_ReadVerNo_ACKFunc(void *pbuff, CJT_188_SendBuff_Struct *outbuff)
{
 ErrCodeType  err = NoErr;

 if(DI_WriteAddress == ((CJT_188_DataHeadStruct *)pbuff)->DI)
 {
  // WriteRom (CJT_188_ADD,((CJT_188_DataHeadStruct *)pbuff) + 1,7);
 }

  outbuff->Head.CTR.Byte = CTR_WriteAddress_ERR;
  outbuff->Head.Length = sizeof(CJT_188_ST_Stuct) + sizeof(CJT_188_SER_Type) ;
  outbuff->Data.ERR.SER = ((CJT_188_DataHeadStruct *)pbuff)->SER;
  outbuff->Data.ERR.ST.Word = 0;
  outbuff->Data.ERR.ST.Bit.Custom = err;
  return CJT_188_SendStart (pbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_ReadAddress_ACKFunc(CJT_188_AskFrameData_Struct* ask)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadAddress_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadAddress; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER; 
  return CJT_188_SendStart (&cjt_188_sendbuff);  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_WriteData_ACKFunc(CJT_188_AskFrameData_Struct* input)
{
  ErrCodeType err = NoErr;
  switch (input->DataHead.DI)
  {
  case DI_WritePriceList:     //0xA010      //写价格表
    {break;}
  case DI_WriteSelDate:       //0xA011      //写结算日期
    {err = CJT_188_WriteSelDate_func (input);break;}
  case DI_WriteRecordDate:    //0xA012      //写抄表日
    {err = CJT_188_WriteRecordDate_func (input);break;}
  case DI_WriteRMoney:        //0xA013      //读购入金额
    {break;}
  case DI_WriteSecretKey:     //0xA014      //写秘钥版本号
    {break;}
  case DI_WriteTime:          //0xA015       //写标准时间
    {err = CJT_188_WriteTime_func (input);break;}
  case DI_WriteValveState:    //0xA017      //写阀门控制
    {err = CJT_188_WriteValveState_func (input);break;}
  case DI_Lock:               //0xA019      //出厂启用
    {break;}
  case DI_WriteAddress:        //0xA018      //写地址
    {break;}
  case DI_WriteOffset:         //0xA016      //写地址
    {break;}
  case DI_WriteIP1:         //0xA201      //写IP1
    {err = CJT_188_WriteIP_func (input,1);break;}
  case DI_WriteIP2:         //0xA202      //写IP2
    {err = CJT_188_WriteIP_func (input,2);break;}
  case DI_WriteBatteyAlarm:   //0xA203      //写电池报警值
    {err = CJT_188_WriteBatteyAlarm_func (input);break;}
  case DI_WriteUpdataTime:   //0xA204      //写上传周期值
    {err = CJT_188_WriteUpdataTime_func (input);break;}
  default :
    {break;}
  }
  return err;  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_AotuUpMeterData (void)
{
   RTC_TimeTypeDef   RTC_TimeStr_BCD;        //RTC时间结构体
   RTC_DateTypeDef   RTC_DateStr_BCD;        //RTC日期结构体

    cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ASK;
    cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_AotuUpData_Struct);   
    cjt_188_sendbuff.Data.OK.DataHead.DI = DI_AotoUpData; 
    cjt_188_sendbuff.Data.OK.DataHead.SER = 0; 

    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV_Unit = m3;

    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[0] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/10%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[0] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[0] += (Cal.Water_Data.flow32*100/PULSE_RATIO)%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[1] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/1000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[1] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[1] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/100%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[2] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/100000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[2] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[2] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/10000%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[3] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/10000000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[3] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_PV[3] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/1000000%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[0] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10%10; //结算日流量
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[0] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[0] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[1] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/1000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[1] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[1] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/100%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[2] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/100000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[2] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[2] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10000%10;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[3] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10000000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[3] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts[3] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/1000000%10;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Flow_Accounts_Unit =  m3;
    
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStr_BCD);
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStr_BCD);
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Year_H = 0x20;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Year_L = RTC_DateStr_BCD.RTC_Year;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Mon = RTC_DateStr_BCD.RTC_Month;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Day = RTC_DateStr_BCD.RTC_Date;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Hour = RTC_TimeStr_BCD.RTC_Hours;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Min = RTC_TimeStr_BCD.RTC_Minutes;
    cjt_188_sendbuff.Data.OK.Data.Aotu.Time.Sec = RTC_TimeStr_BCD.RTC_Seconds;
    cjt_188_sendbuff.Data.OK.Data.Aotu.ST.Word= 0x0;
    cjt_188_sendbuff.Data.OK.Data.Aotu.ST.Bit.Custom = 0;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.BatteyData[0] = 0x30; //读取电池电压
    cjt_188_sendbuff.Data.OK.Data.Aotu.BatteyData[1] = 0x03;
    cjt_188_sendbuff.Data.OK.Data.Aotu.BatteyData_Unit = V;
    
    cjt_188_sendbuff.Data.OK.Data.Aotu.RSSI = 0;//读信号强度
    cjt_188_sendbuff.Data.OK.Data.Aotu.Temp = 20;//读温度
    
#if (HARDWARE == 20)
    cjt_188_sendbuff.Data.OK.Data.Aotu.ST.Bit.Magnetism = Read_Mag_Att();
#endif
  //}
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //设置上传周期
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteUpdataTime_func (CJT_188_AskFrameData_Struct* ask)
{
  struct Up_Date_Str i;
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteUpdataTime; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  i.Hour = (ask->Data.UpDate.Hour&0x0f)%10;
  i.Hour += ((ask->Data.UpDate.Hour>>4)&0x0f)%10*10;
  
  i.Day = (ask->Data.UpDate.Day&0x0f)%10;
  i.Day += ((ask->Data.UpDate.Day>>4)&0x0f)%10*10;
  
  
  WriteRom (UP_DATE_ADD,&i,2);
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //设置电池报警值
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteBatteyAlarm_func (CJT_188_AskFrameData_Struct* ask)
{
  unsigned short i = 0;
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteBatteyAlarm; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  i = (ask->Data.Battey.BatteyData[0]&0x0f)%10;
  i += ((ask->Data.Battey.BatteyData[0]>>4)&0x0f)%10*10;
  i += (ask->Data.Battey.BatteyData[1]&0x0f)%10*100;
  i += ((ask->Data.Battey.BatteyData[1]>>4)&0x0f)%10*1000;
  
  WriteRom (BAT_ALARM_ADD,&i,2);
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //写IP1
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteIP_func (CJT_188_AskFrameData_Struct* ask,unsigned char num)
{
  union Network_Par_Uni ip;
    
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteIP1-1+num; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  ip.Str.IP[0] = ask->Data.IP.IP_1;
  ip.Str.IP[1] = ask->Data.IP.IP_2;
  ip.Str.IP[2] = ask->Data.IP.IP_3;
  ip.Str.IP[3] = ask->Data.IP.IP_4;
  ip.Byte[4] = ask->Data.IP.PORT_H;
  ip.Byte[5] = ask->Data.IP.PORT_L;
  
  Save_IP(ip.Byte,num);
  
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //写抄标准时间
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteTime_func (CJT_188_AskFrameData_Struct* ask)
{

  RTC_TimeTypeDef   RTC_TimeStr_BCD;        //RTC时间结构体
  RTC_DateTypeDef   RTC_DateStr_BCD;        //RTC日期结构体
   
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteTime; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  RTC_TimeStructInit(&RTC_TimeStr_BCD);
  RTC_TimeStr_BCD.RTC_Hours   = ask->Data.Time.Hour;
  RTC_TimeStr_BCD.RTC_Minutes = ask->Data.Time.Min;
  RTC_TimeStr_BCD.RTC_Seconds = ask->Data.Time.Sec;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStr_BCD);

  //RTC_DateStr_BCD.RTC_WeekDay = RTC_Weekday_Thursday; //不要周
  RTC_DateStr_BCD.RTC_Date = ask->Data.Time.Day;
  RTC_DateStr_BCD.RTC_Month = (RTC_Month_TypeDef)ask->Data.Time.Mon;
  RTC_DateStr_BCD.RTC_Year = ask->Data.Time.Year_L;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStr_BCD);
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //写抄表日 日期
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteRecordDate_func (CJT_188_AskFrameData_Struct* ask)
{
  unsigned char i = 0;
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteRecordDate; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  i = (ask->Data.Read_Date&0x0f)%10;  //保存 结算日日期
  i += ((ask->Data.Read_Date>>4)&0x0f)%10*10;
  
 // WriteRom (READ_DATE_ADD,&i,1);
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //写结算日 日期
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteSelDate_func (CJT_188_AskFrameData_Struct* ask)
{
  unsigned char i = 0;
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteSelDate; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;
  UpdataSER = ask->DataHead.SER;
  
  
  
  
  
  i = (ask->Data.Set_Date&0x0f)%10;  //保存 结算日日期
  i += ((ask->Data.Set_Date>>4)&0x0f)%10*10;
  
 // WriteRom (SET_DATE_ADD,&i,1);
  
  CJT_188_SendStart (&cjt_188_sendbuff);
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_WriteOffset_ACKFunc(CJT_188_AskFrameData_Struct* ask)   //写表底数的函数
{
 CJT_188_WriteOffsetStruct* Offset;
 unsigned long Offset_Data = 0;
 unsigned long i;
 
 Offset = (CJT_188_WriteOffsetStruct*)&(ask->Data);
 
 i = Offset ->Flow_Offse[0]&0x0f;
 Offset_Data += i;
 i = (Offset ->Flow_Offse[0]&0xf0)>>4;
 Offset_Data += i*10;
 i = Offset ->Flow_Offse[1]&0x0f;
 Offset_Data += i*100;
 i = (Offset ->Flow_Offse[1]&0xf0)>>4;
 Offset_Data += i*1000;
 i = Offset ->Flow_Offse[2]&0x0f;
 Offset_Data += i*10000;
 i = (Offset ->Flow_Offse[2]&0xf0)>>4;
 Offset_Data += i*100000;
 i = Offset ->Flow_Offse[3]&0x0f;
 Offset_Data += i*1000000;
 i = (Offset ->Flow_Offse[3]&0xf0)>>4;
 Offset_Data += i*10000000;
 
  Cal.Water_Data.flow32 = Offset_Data*PULSE_RATIO/100;
   
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteOffset_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188_ST_Stuct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteOffset; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER; 
  cjt_188_sendbuff.Data.OK.Data.ST.Word = 0;

  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CTR_WriteAddress_ACKFunc(CJT_188_AskFrameData_Struct* ask)
{
 CJT_188_AddresStruct* Addres;
 Addres = (CJT_188_AddresStruct*)&(ask->Data);
 
 WriteRom (CJT_188_ADD,Addres->MeterID,7);
   
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteAddress_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteAddress; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER; 
// else
// {
//    cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteAddress_ERR;
//    cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct);   
//    cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteAddress; 
//    cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER; 
// }
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_TempData (unsigned char ser)
{
  if(0 != cjt_188_sendbuff.flg)
  {return Busy;}
  else
  {cjt_188_sendbuff.flg = 1;}
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_TempData_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadTemp; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  
  cjt_188_sendbuff.Data.OK.Data.Temp.ST.Word= 0x0;
  cjt_188_sendbuff.Data.OK.Data.Temp.ST.Bit.Custom = 0;
#if (HARDWARE == 20)
  cjt_188_sendbuff.Data.Temp.Data.MeterData.ST.Bit.Magnetism = Read_Mag_Att();
#endif
  cjt_188_sendbuff.Data.OK.Data.Temp.Temp = 20; //温度值 临时变量
 // cjt_188_sendbuff.Data.Temp.Data.MeterData.Temp = Read_Temp();   //增加读取温度值
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadSelDate(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+1;   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadSelDate; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
//  cjt_188_sendbuff.Data.OK.Data.Set_Date = *SET_DATE%10;  //将结算日转为BCD码
//  cjt_188_sendbuff.Data.OK.Data.Set_Date += (*SET_DATE/10%10)<<4;
  
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadRecordDate(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+1;   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadRecordDate; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
//  cjt_188_sendbuff.Data.OK.Data.Set_Date = *READ_DATA%10;  //将抄表日转为BCD码
//  cjt_188_sendbuff.Data.OK.Data.Set_Date += (*READ_DATA/10%10)<<4;
  
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadBattey(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188BatteyData_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadBattey; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData[0] = 0x30; //读取电池电压
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData[1] = 0x03;
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData_Unit = V;
  cjt_188_sendbuff.Data.OK.Data.Battey.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadBatteyAlarm(unsigned char ser)
{
  unsigned char i = 0;
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188BatteyData_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadBatteyAlarm; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  
  i = *BAT_ALARM%10;
  i <<= 4;
  i += *BAT_ALARM/10%10;
  
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData[0] = i;
 
  i = *BAT_ALARM/100%10;
  i <<= 4;
  i += *BAT_ALARM/1000%10;
 
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData[1] = i;
  cjt_188_sendbuff.Data.OK.Data.Battey.BatteyData_Unit = V;
  cjt_188_sendbuff.Data.OK.Data.Battey.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadUpdataTime(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188UpDate_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadUpdataTime; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  
  cjt_188_sendbuff.Data.OK.Data.UpDate.Day = UP_DATA->Day/10%10;
  cjt_188_sendbuff.Data.OK.Data.UpDate.Day <<= 4;
  cjt_188_sendbuff.Data.OK.Data.UpDate.Day += UP_DATA->Day%10;
  
  cjt_188_sendbuff.Data.OK.Data.UpDate.Hour = UP_DATA->Hour/10%10;
  cjt_188_sendbuff.Data.OK.Data.UpDate.Hour <<= 4;
  cjt_188_sendbuff.Data.OK.Data.UpDate.Hour += UP_DATA->Hour%10;
  
  cjt_188_sendbuff.Data.OK.Data.UpDate.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadRSSI(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188RSSI_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadRSSI; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  
  cjt_188_sendbuff.Data.OK.Data.RSSI.RSSI = 0;
  
  cjt_188_sendbuff.Data.OK.Data.RSSI.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadIP1Date(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188_IPData_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadIP1; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  cjt_188_sendbuff.Data.OK.Data.IP.IP_1 = IP1->Str.IP[0];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_2 = IP1->Str.IP[1];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_3 = IP1->Str.IP[2];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_4 = IP1->Str.IP[3];
  cjt_188_sendbuff.Data.OK.Data.IP.PORT_H = IP1->Byte[4];
  cjt_188_sendbuff.Data.OK.Data.IP.PORT_L = IP1->Byte[5];
  cjt_188_sendbuff.Data.OK.Data.IP.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_ReadIP2Date(unsigned char ser)
{
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+sizeof(CJT_188_IPData_Struct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadIP1; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
  cjt_188_sendbuff.Data.OK.Data.IP.IP_1 = IP2->Str.IP[0];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_2 = IP2->Str.IP[1];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_3 = IP2->Str.IP[2];
  cjt_188_sendbuff.Data.OK.Data.IP.IP_4 = IP2->Str.IP[3];
  cjt_188_sendbuff.Data.OK.Data.IP.PORT_H = IP2->Byte[4];
  cjt_188_sendbuff.Data.OK.Data.IP.PORT_L = IP2->Byte[5];
  cjt_188_sendbuff.Data.OK.Data.IP.ST.Word = 0;
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_HistoryData (unsigned char ser,unsigned char num)
{
    cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
    cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_HistoryData_Struct);   
    cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadHistData_1+num; 
    cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History_Unit = m3; 
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[0] = (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/10%10;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[0] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[0] += (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)%10;
    
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[1] = (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/1000%10;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[1] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[1] += (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/100%10;
    
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[2] = (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/100000%10;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[2] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[2] += (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/10000%10;
    
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[3] = (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/10000000%10;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[3] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.HistoryData.Flow_History[3] += (HISTORY_FLOW[num].flow32*100/PULSE_RATIO)/1000000%10;
  
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType send_MeterData (unsigned char ser)
{
   RTC_TimeTypeDef   RTC_TimeStr_BCD;        //RTC时间结构体
   RTC_DateTypeDef   RTC_DateStr_BCD;        //RTC日期结构体

    cjt_188_sendbuff.Head.CTR.Byte =  CTR_ReadData_ACK;
    cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_MeterData_Struct);   
    cjt_188_sendbuff.Data.OK.DataHead.DI = DI_ReadData; 
    cjt_188_sendbuff.Data.OK.DataHead.SER = ser; 

    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV_Unit = m3;

    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[0] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/10%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[0] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[0] += (Cal.Water_Data.flow32*100/PULSE_RATIO)%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[1] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/1000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[1] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[1] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/100%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[2] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/100000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[2] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[2] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/10000%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[3] = (Cal.Water_Data.flow32*100/PULSE_RATIO)/10000000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[3] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_PV[3] += (Cal.Water_Data.flow32*100/PULSE_RATIO)/1000000%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[0] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10%10; //结算日流量
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[0] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[0] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[1] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/1000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[1] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[1] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/100%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[2] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/100000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[2] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[2] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10000%10;
    
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[3] = (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/10000000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[3] <<= 4;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts[3] += (ACCOUNT_FLOW->flow32*100/PULSE_RATIO)/1000000%10;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Flow_Accounts_Unit =  m3;
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStr_BCD);
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStr_BCD);
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Year_H = 0x20;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Year_L = RTC_DateStr_BCD.RTC_Year;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Mon = RTC_DateStr_BCD.RTC_Month;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Day = RTC_DateStr_BCD.RTC_Date;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Hour = RTC_TimeStr_BCD.RTC_Hours;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Min = RTC_TimeStr_BCD.RTC_Minutes;
    cjt_188_sendbuff.Data.OK.Data.MeterData.Time.Sec = RTC_TimeStr_BCD.RTC_Seconds;
    cjt_188_sendbuff.Data.OK.Data.MeterData.ST.Word= 0x0;
    cjt_188_sendbuff.Data.OK.Data.MeterData.ST.Bit.Custom = 0;
#if (HARDWARE == 20)
    cjt_188_sendbuff.Data.OK.Data.MeterData.ST.Bit.Magnetism = Read_Mag_Att();
#endif
  //}
  return CJT_188_SendStart (&cjt_188_sendbuff);
}
/*********************************************************************************
 Function:      //
 Description:   //写阀门控制  操作执行
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_WriteValveState_func (CJT_188_AskFrameData_Struct* ask)
{
  if(0 != cjt_188_sendbuff.flg)
  {return Busy;}
  else
  {cjt_188_sendbuff.flg = 1;}
  
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_ST_Stuct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteValveState; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = ask->DataHead.SER;

  cjt_188_sendbuff.Data.OK.Data.ST.Word= 0;
  cjt_188_sendbuff.Data.OK.Data.ST.Bit.Custom = 0;
#if (HARDWARE == 20)
  cjt_188_sendbuff.Data.OK.Data.ST.Bit.Magnetism = Read_Mag_Att();
#endif
  CJT_188_SendStart (&cjt_188_sendbuff);
  enableInterrupts();
  
  return NoErr; 
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void CJT_188_ValveState_updata ( void )
{
  if(0 != cjt_188_sendbuff.flg)
  {return; }
  else
  {cjt_188_sendbuff.flg = 1;}
  
  cjt_188_sendbuff.Head.CTR.Byte =  CTR_WriteData_ACK;
  cjt_188_sendbuff.Head.Length = sizeof(CJT_188_DataHeadStruct)+ sizeof(CJT_188_ST_Stuct);   
  cjt_188_sendbuff.Data.OK.DataHead.DI = DI_WriteValveState; 
  cjt_188_sendbuff.Data.OK.DataHead.SER = UpdataSER;
  
  cjt_188_sendbuff.Data.OK.Data.ST.Word= 0;
  cjt_188_sendbuff.Data.OK.Data.ST.Bit.Custom = 0;
#if (HARDWARE == 20)
  cjt_188_sendbuff.Data.OK.Data.ST.Bit.Magnetism = Read_Mag_Att();
#endif
  if(NoErr == CJT_188_SendStart (&cjt_188_sendbuff))
  {cjt_188_Valve_AckFlg = 0;}
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_SendStart (CJT_188_SendBuff_Struct *Outbuff)
{
  unsigned char itemp  =0;
  unsigned char itemp1;
  unsigned char sum;
  unsigned char* p;
  
  while(itemp < CJT_188_PreambleLength)     //增加报头fe
  {Outbuff->Preamble[itemp++] = CJT_188_Preamble;}

  Outbuff->Head.StartCharacter = CJT_188_StartCharacter;  //增加起始68
  Outbuff->Head.Type = Locall_MeterType;  //增加表具类型
 // Outbuff->Head.Addr.FactoryID = Locall_FactoryID;
 
  Outbuff->Head.Addr.MeterID[0] = (CJT_188_MeterID)[0];
  Outbuff->Head.Addr.MeterID[1] = (CJT_188_MeterID)[1];
  Outbuff->Head.Addr.MeterID[2] = (CJT_188_MeterID)[2];
  Outbuff->Head.Addr.MeterID[3] = (CJT_188_MeterID)[3];
  Outbuff->Head.Addr.MeterID[4] = (CJT_188_MeterID)[4];
  Outbuff->Head.Addr.MeterID[5] = (CJT_188_MeterID)[5];//如果为固定厂商则删除
  Outbuff->Head.Addr.MeterID[6] = (CJT_188_MeterID)[6];//如果为固定厂商则删除
  
  itemp = 0;
  itemp1 = sizeof(CJT_188_FrameHeadStruct) + Outbuff->Head.Length;  //计算结构体长度
 // itemp1 -= 2;//减去校验和报尾所占的长度
  sum = 0;  
  p = (unsigned char *)&(Outbuff->Head);
  while (itemp < itemp1)
  {sum += p[itemp ++];}
  p[itemp ++] = sum;   //计算校验
  p[itemp ++] = CJT_188_Pause;//计算结束
  
  if(Pro_DataSource == FROM_UART3)//从串口3返回
  {
    Uart3_Send(Outbuff->Preamble,itemp + CJT_188_PreambleLength);
  }
//  if(Mbus_SEND_CallBack (Outbuff->Preamble, itemp + CJT_188_PreambleLength, CJT_188_SendOK_CallBack, Outbuff ))
  {return NoErr;}
//  else
//  {return SendErr;}
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
ErrCodeType CJT_188_Send (unsigned char port, CJT_188_SendBuff_Struct *pbuff)
{
  CJT_188_FrameHeadStruct *p;
  unsigned char itemp;
  unsigned char itemp1;
  unsigned char sum;
  
  p = &(pbuff->Head);
  p->StartCharacter = CJT_188_StartCharacter;
  p->Type = Locall_MeterType;
  //p->Addr.FactoryID = Locall_FactoryID;
  p->Addr.MeterID[0] = (CJT_188_MeterID)[0];
  p->Addr.MeterID[1] = (CJT_188_MeterID)[1];
  p->Addr.MeterID[2] = (CJT_188_MeterID)[2];
  p->Addr.MeterID[3] = (CJT_188_MeterID)[3];
  p->Addr.MeterID[4] = (CJT_188_MeterID)[4];
  p->Addr.MeterID[3] = (CJT_188_MeterID)[5];
  p->Addr.MeterID[4] = (CJT_188_MeterID)[6];
  itemp = 0;
  itemp1 = sizeof(CJT_188_FrameHeadStruct) +  p->Length;
  sum = 0;  
  while (itemp < itemp1)
  {
    sum += ((unsigned char *)p)[itemp];
    itemp ++;
  }
  ((unsigned char *)p)[itemp ++] = sum;
  ((unsigned char *)p)[itemp ++] = CJT_188_Pause;
  
//  pbuff->flg = Mbus_SEND_CallBack ( p, itemp, CJT_188_SendOK_CallBack, pbuff );
//  if(0 == pbuff->flg )
  {return Busy;}
//  else
//  {return Busy;}
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void CJT_188_SendOK_CallBack (unsigned char port, void *pbuff)
{
  if(PNULL != pbuff)
  {((CJT_188_SendBuff_Struct *) pbuff)->flg = 0;}
  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
//static void BinToBCD (unsigned long data, unsigned char *pbuff, unsigned char w)
//{
//  unsigned char itemp;
//  while (data > 0)
//  {
//    w --;
//    pbuff[w] =  data %10;
//    data /= 10;
//    
//    itemp = (data %10);
//    data /= 10;
//    itemp <<= 4;
//    pbuff[w] |= itemp;
//    if(w == 0){break;}
//  }
//  while ( w-- > 0)
//  {pbuff[w] = 0;}
//}
void BinToBCD (unsigned long data, unsigned char *pbuff, unsigned char w)
{
  unsigned char itemp;
  unsigned char itemp2;
  
  pbuff[0] = 0;
  itemp = 1;
  while (data > 0)
  {
    pbuff[itemp] =  data %10;
    data /= 10;
    
    itemp2 = (data %10);
    data /= 10;
    itemp2 <<= 4;
    pbuff[itemp] |= itemp2;
    
    itemp ++;
    if(itemp >= w){break;}
  }
  while (itemp < w)
  {
    pbuff[itemp] = 0;
    itemp ++;
  }
}
/******************************************END********************************************************/

