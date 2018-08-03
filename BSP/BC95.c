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
struct BC95_Str BC95;            //BC95 用的寄存器
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
 Function:      //void BC95_Power_On(void)
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void BC95_Power_On(void)        //BC95上电
{
  RCC_Configuration();
  USART2_Configuration();       //初始化串口2
  
  Uart2.Sent_Length = 0;                                //清空串口2发送长度
  Uart2.Receive_Length = 0;                             //清空串口2接收长度
  Uart2.Send_Busy = FALSE;                              //清空串口2发送忙标志  
  Uart2.Receive_Busy = FALSE;                           //清空串口2接收忙
  Uart2.Receive_Pend = FALSE;                           //清空串口2挂起
  
  
  GPIO_SetBits(GPIOE,GPIO_Pin_2);       //VBAT拉高        3.1-4.2V，典型值3.6V
  GPIO_SetBits(GPIOE,GPIO_Pin_1);      //复位脚拉低
  
  BC95.Start_Process = BC95_POWER_UP; 
  
  Create_Timer(ONCE,1,
                     BC95_Reset,0,PROCESS);//建议定时器延时回调
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
void BC95_Power_Off(void)        //BC95断电
{
  GPIO_ResetBits(GPIOE,GPIO_Pin_2); 
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
void BC95_Reset(void)
{
  GPIO_ResetBits(GPIOE,GPIO_Pin_1);     //复位脚拉高
  
  Create_Timer(ONCE,40,
                     BC95_Start,0,PROCESS);//建议定时器延时回调
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
void BC95_Start(void)        //BC95复位
{
  BC95.Start_Process = AT; //指向下一个流程
  BC95.Incident_Pend = TRUE; //事件标志挂起
  BC95.Err_Conner.Connect = SEND_ERROR_NUM;     //连接超时次数
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
void BC95_Process(void)                         //BC95主进程
{
  char *str = NULL;
  //如果需要上报消息，启动BC95
  if(BC95.Report_Bit != 0)
  {
    if(BC95.Start_Process == BC95_RECONNECT)
    {
      if(BC95.Reconnect_Times >= 3)  //重连超次数则睡眠
      {
        BC95.Reconnect_Times = 0;
        
        BC95.Start_Process = BC95_POWER_DOWN;
        BC95_Power_Off();
        Device_Status = SLEEP_MODE;
      }
      else     //否则重连
      {
        Device_Status = RUN_MODE;
        BC95_Power_On();
      }
    }
  }
  
  if(BC95.Incident_Pend != FALSE) //检测是否有事件挂起
  {
    BC95.Incident_Pend = FALSE; //清除事件挂起
    switch(BC95.Start_Process)
    {
    case AT:                  //同步波特率
      {
        BC95_Data_Send("AT\r\n",4);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETNBAND:               //查询频段
      {
        
        BC95_Data_Send("AT+NBAND?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETCFUN:                //查询电话功能
      {
        BC95_Data_Send("AT+CFUN?\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      } 
      break;
    case CGSN:                 //查询IMEI      
      {
        BC95_Data_Send("AT+CGSN=1\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;  
     case CCID:                 //查询CCID
      {
//        BC95_Data_Send("AT+CIMI\r\n",9); 
        BC95_Data_Send("AT+NCCID\r\n",10); 
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;  
    case CSQ:                //查询信号强度
      {
        BC95_Data_Send("AT+CSQ\r\n",8);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      } 
      break;
    case GETCGATT:                //查询网络激活状态    
      {
        BC95_Data_Send("AT+CGATT?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;    
    case CEREG:                //查询网络注册状态     
      {
        BC95_Data_Send("AT+CEREG?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case CCLK:                //查询实时时间 
      {
        BC95_Data_Send("AT+CCLK?\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETNCDP:                 //查询CDP服务器
      {
        BC95_Data_Send("AT+NCDP?\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case SETNCDP:                 //设置CDP服务器 
      {
        BC95_Data_Send("AT+NCDP=180.101.147.115,5683\r\n",30);   
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break; 
    case NSMI:                 //设置发送消息指示
      {
        BC95_Data_Send("AT+NSMI=1\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
//    case NNMI:                 //设置接收消息指示
//      {
//        BC95_Data_Send("AT+NNMI=1\r\n",11);
//        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
//                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
//      }
//      break;
    case NMGS:                 //发送消息     
      {     
        Send_Data_Process();
        if(BC95.Report_Bit != 0)   //有消息发送
        {   
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
          Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
        }
      }
      break;
    case NQMGR:                 //查询消息接收缓存
      {
        BC95_Data_Send("AT+NQMGR\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case NMGR:                 //接收消息
      {
        BC95_Data_Send("AT+NMGR\r\n",9);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBack,0,PROCESS);//建议定时器延时回调
      }
      break;
    case BC95_CONNECT_ERROR:      //连接失败
      BC95_Power_Off();
      BC95.Start_Process = BC95_RECONNECT;
      BC95.Reconnect_Times++;
      break;
    case BC95_POWER_DOWN:       //发送接收完成则直接关电
      BC95_Power_Off();
      Device_Status = SLEEP_MODE;       //睡眠
      break;
    default:
      break;
    }
  }
  if(Uart2.Receive_Pend != FALSE)//判断有数据
  {
    memset(BC95.R_Buffer,'\0',RECV_BUFF_SIZE);//清缓存
    BC95.Recv_Length = Uart2_Receive((unsigned char *)BC95.R_Buffer);//接收数据

    switch(BC95.Start_Process)
    {
    case AT:            //同步波特率
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = GETNBAND;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case GETNBAND:               //查询频段
      {       
        if(strstr(BC95.R_Buffer,"+NBAND:5") != NULL)    //支持频段5
        {
          BC95.Start_Process = GETCFUN;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case GETCFUN:                //查询电话功能
      {
        if(strstr(BC95.R_Buffer,"+CFUN:1") != NULL)     //全功能
        {         
          BC95.Start_Process = CGSN;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      } 
      break;
    case CGSN:         // 查询IMEI
      {
        str = strstr(BC95.R_Buffer,"+CGSN");
        if( str != NULL)//获取到IMEI
        {
          memcpy(BC95.IMEI,&str[6],15);
          BC95.Start_Process = CCID;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
     case CCID:          //查询CCID
      {
        str = strstr(BC95.R_Buffer,"+NCCID");
        if( str != NULL)
        {
          memcpy(BC95.ICCID,&str[7],20);
          BC95.Start_Process = CSQ;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case CSQ:           //查询信号强度
      {
        str = strstr(BC95.R_Buffer,"+CSQ");
        if( str != NULL)
        {
          BC95.Rssi =0;//保存信号强度
          if( (str[5] >= '0') && (str[5] <= '9') )
          {
            BC95.Rssi += str[5]-0x30;
          }
          if( (str[6] >= '0') && (str[6] <= '9') )
          {
            BC95.Rssi *=10;
            BC95.Rssi += str[6]-0x30;
          }
          
          BC95.Rssi %= 100;
          if(BC95.Rssi < 99)
          {
            BC95.Start_Process = GETCGATT;
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
          }
        }
      }
      break;
    case GETCGATT:       //查询网络激活状态
      {
        if( strstr(BC95.R_Buffer,"+CGATT:1") != NULL)//网络激活
        {        
          BC95.Start_Process = CEREG;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }       
      }
      break;
    case CEREG:       //查询网络注册状态
      {
        if( strstr(BC95.R_Buffer,"+CEREG:0,1") != NULL)//网络注册
        {        
          BC95.Start_Process = CCLK;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;   
    case CCLK:       //查询实时时间
      {
        str = strstr(BC95.R_Buffer,"+CCLK:");
        if( str != NULL)//网络注册
        {  
          GMT_to_BT((unsigned char*)str);
          BC95.Start_Process = GETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;   
    case  GETNCDP:                 //查询CDP服务器
      {
        if( strstr(BC95.R_Buffer,"+NCDP:180.101.147.115,5683") != NULL)//获取到NCDP
        {        
          BC95.Start_Process = NSMI;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
        else
        {        
          BC95.Start_Process = SETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case  SETNCDP:                 //设置CDP服务器 
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = GETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }  
      }
      break;
    case NSMI:                 //设置发送消息指示
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = NMGS;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }  
      }
      break;
//    case  NNMI:                 //设置接收消息指示 
//      {
//        if(strstr(BC95.R_Buffer,"OK") != NULL)
//        {         
//          BC95.Start_Process = NMGS;
//          BC95.Incident_Pend = TRUE;//标记挂起
//          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
//        }  
//      }
//      break;
    case NMGS:        //发送消息
      {      
        if( strstr(BC95.R_Buffer,"+NSMI:SENT") != NULL)//已发送
        { 
          BC95.Start_Process = NQMGR;
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
          Create_Timer(ONCE,5,
                     BC95_Delay_CallBalk,0,PROCESS);//建议定时器延时回调,发送消息后等待5s查询消息接收缓存
        }
      }
      break;
    case NQMGR:        //查询消息接收缓存
      {
        if(strstr(BC95.R_Buffer,"ERROR") != NULL)       //返回错误
        {
          
        }
        else if(strstr(BC95.R_Buffer,"BUFFERED=0") != NULL)  //待读消息数量为零
        { 
          BC95.Start_Process = NMGS;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
        else                                            //否则读取消息
        {
          BC95.Start_Process = NMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case NMGR:        //接收消息
      {
        if(strstr(BC95.R_Buffer,"ERROR") != NULL)       //返回错误
        {
          
        }
        else if(strstr(BC95.R_Buffer,",AAAA0000") != NULL)  //上报全部参数的响应
        {   
          if(BC95.Report_Bit == 1)
          {
            BC95.Report_Bit = 2;
            HistoryReadIndex =  HistorySaveIndex+1;
          }
          else if(BC95.Report_Bit == 2)
          {  
            Clear_History_Data();
          }
          BC95.Start_Process = NQMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
        else if(strstr(BC95.R_Buffer,",AAAA0001") != NULL)     //上报历史流量的响应
        {
          BC95.Report_Bit = 0;
          BC95.Start_Process = NQMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
        else   //平台消息
        {
          Recv_Data_Process();   
          BC95.Start_Process = NQMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case BC95_CONNECT_ERROR:
      //添加异常处理
      break;
    default:
      break;
    }
  }
  
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
void BC95_Data_Send(unsigned char *Data,unsigned short Len)
{    
  memset(BC95.R_Buffer,'\0',RECV_BUFF_SIZE);//清接收缓冲区
  Uart2_Send((unsigned char*)Data,Len);
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
void BC95_Start_Timeout_CallBack(void)//启动超时重发
{
  if(BC95.Err_Conner.Connect != 0)//判断次数是否超时
  {
    BC95.Incident_Pend = TRUE;
    BC95.Err_Conner.Connect--;
  }
  else
  {
    BC95.ErrorRecord = BC95.Start_Process;
    Save_BC95_ErrorRecord();
    
    BC95.Incident_Pend = TRUE;
    BC95.Start_Process = BC95_CONNECT_ERROR;//启动错误
  }
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
void BC95_Delay_CallBalk(void)
{
  BC95.Incident_Pend = TRUE;//标记挂起
}
/*********************************************************************************
 Function:      //
 Description:   //接收消息进程
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void Recv_Data_Process(void)
{
  u16 i = 0;
  u8 month = 0;
  u8 MessageID = 0;
  u16 DataLength = 0;
  u8 mid[4] = {0};           //命令序列号
  u8 valueH = 0,valueL = 0;
  RTC_TimeTypeDef  RTC_Time;
  RTC_DateTypeDef  RTC_Date;
  union flow_union Flow;
  unsigned char* str = NULL;
  
  while(BC95.R_Buffer[i] != ',')
  {
    if( (BC95.R_Buffer[i]>= '0')&&(BC95.R_Buffer[i]<= '9') )
    {
      DataLength = DataLength*10+ASCLL_to_Int(BC95.R_Buffer[i]);
    }  
    i++;
  }
  
  str = (unsigned char*)&BC95.R_Buffer[i];
  for(i = 0;i < (DataLength*2);i++)
  {
    str[i+1] = ASCLL_to_Int(str[i+1]);
  }
  
  
  MessageID = str[1]*16+str[2];
  mid[0] = str[3];
  mid[1] = str[4];
  mid[2] = str[5];
  mid[3] = str[6];
  
  switch(MessageID)
  {
    case 0x02:            //配置参数
      {//31,020004 3030303031383035303030303031 01 02D0 0140 000000000000000030
        //表号
        valueH = str[7]*0x10+str[8];
        valueL = str[9]*0x10+str[10];
        Meter_Number[0] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[11]*0x10+str[12];
        valueL = str[13]*0x10+str[14];
        Meter_Number[1] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[15]*0x10+str[16];
        valueL = str[17]*0x10+str[18];
        Meter_Number[2] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[19]*0x10+str[20];
        valueL = str[21]*0x10+str[22];
        Meter_Number[3] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[23]*0x10+str[24];
        valueL = str[25]*0x10+str[26];
        Meter_Number[4] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[27]*0x10+str[28];
        valueL = str[29]*0x10+str[30];
        Meter_Number[5] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[31]*0x10+str[32];
        valueL = str[33]*0x10+str[34];
        Meter_Number[6] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        Save_Meter_Number();
        //结算日期
        Settle_Date = str[35]*0x10+str[36];   //设置结算日期
        Save_Settle_Date();       
        //上报周期
         Report_Cycle = str[37]*0x1000+str[38]*0x100+str[39]*0x10+str[40]; //设置上报周期
        Save_Report_Cycle();
        //告警电压
        BAT_Alarm_Vol = str[41]*0x1000+str[42]*0x100+str[43]*0x10+str[44];
        Save_BAT_Alarm_Value();
        
        //0x03响应
        ACK(0x03,0x00,mid);
      }
      break;
    case 0x04:           //校准水量
      {//8,040003010000007B 
        month = str[7]*0x10+str[8];
        if(month == 0)  //校准当前累积水量
        {
          Cal.Water_Data.flow8[0] = str[9]*0x10+str[10];
          Cal.Water_Data.flow8[1] = str[11]*0x10+str[12];
          Cal.Water_Data.flow8[2] = str[13]*0x10+str[14];
          Cal.Water_Data.flow8[3] = str[15]*0x10+str[16];
          Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);
        }
        else if(month <= 13)  //校准结算日累积水量
        {
          Flow.flow8[0] = str[9]*0x10+str[10];
          Flow.flow8[1] = str[11]*0x10+str[12];
          Flow.flow8[2] = str[13]*0x10+str[14];
          Flow.flow8[3] = str[15]*0x10+str[16];
          Save_Add_Flow(SDCF1_ADDR+4*(month-1),&Flow);
        }
        //0x05响应
        ACK(0x05,0x00,mid);
      } 
      break;
    case 0x06:           //校准时间
      {//
        //时间       
        RTC_Date.RTC_Year = str[12]*10+str[14];
        RTC_Date.RTC_Month = str[2+i+16]*10+str[18];
        RTC_Date.RTC_Date = str[20]*10+str[22];
        RTC_Date.RTC_WeekDay = RTC_Weekday_Monday;
        
        RTC_Time.RTC_Hours   = str[24]*10+str[26];
        RTC_Time.RTC_Minutes = str[28]*10+str[30];
        RTC_Time.RTC_Seconds = str[32]*10+str[34];
        
        RTC_SetDate(RTC_Format_BIN, &RTC_Date);
        RTC_SetTime(RTC_Format_BIN, &RTC_Time);
        //0x05响应
        ACK(0x07,0x00,mid);
      } 
      break;
    default:
      break;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //发送消息进程
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void Send_Data_Process(void)
{ 
   switch(BC95.Report_Bit)
  {
    case 0:             //没有消息上报,则关机
      {
        BC95.Start_Process = BC95_POWER_DOWN;
      }
      break;
    case 1:            //发送全部参数
      {
        Report_All_Parameters();
      }
      break;
    case 2:            //发送历史数据
      {
        Report_All_Parameters();
      }
      break;
    case 3:            //发送历史累积流量
      {
        Report_HC_Flow();
      }
      break;
    default:
      break;
  }
}
/*********************************************************************************
 Function:      //
 Description:   //命令响应
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void ACK(u8 messageId,u8 errcode,u8 mid[4])
{
  uint8_t data[64] = "AT+NMGS=4,00000000\r\n";
  
  data[10] = Int_to_ASCLL(messageId/0x10);
  data[11] = Int_to_ASCLL(messageId%0x10);
  data[12] = Int_to_ASCLL(errcode/0x10);
  data[13] = Int_to_ASCLL(errcode%0x10);
  data[14] = Int_to_ASCLL(mid[0]);
  data[15] = Int_to_ASCLL(mid[1]);
  data[16] = Int_to_ASCLL(mid[2]);
  data[17] = Int_to_ASCLL(mid[3]);
  
  BC95_Data_Send(data,20);
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
//uint8_t data[320] = "AT+NMGS=147,00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
//0000000000000030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030\r\n";
void Report_All_Parameters(void)
{
  uint8_t data[200] = "AT+NMGS=77,0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\r\n";
  union flow_union LastMonthFlow;     //上一月结算日累积流量
  union flow_union CurrentFlow;     //当前累积流量
  uint8_t month,date,hour,minute,second;
  unsigned short year = 0;
  uint8_t valueH = 0,valueL = 0;
  unsigned char buff[14] = {0};
   
  //获取上一月累计流量
  Read_ACUM_Flow(SDCF1_ADDR,&LastMonthFlow);
  //采集温度
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_High_Fast);         // 热敏电阻
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_In_FL_No_IT);      // 热敏电阻ADC检测端
  Read_Temp();
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow); 
  //获取上次联网错误信息
  Read_BC95_ErrorRecord();
  
  if(BC95.Report_Bit == 1)      //上传当前数据
  {
    CurrentFlow.flow32 = Cal.Water_Data.flow32;
    //获取时间   
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStr);
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStr);
    year = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Year)+2000;
    month = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Month);
    date = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Date);
    hour = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Hours);
    minute = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Minutes);
    second = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Seconds);
  }
  else if(BC95.Report_Bit == 2) //上传历史数据
  {
    
    if(1 == Read_History_Data(buff))
    {
      CurrentFlow.flow8[0] = buff[0];
      CurrentFlow.flow8[1] = buff[1];
      CurrentFlow.flow8[2] = buff[2];
      CurrentFlow.flow8[3] = buff[3];
      year = BCD_to_Int((unsigned char)buff[4])+2000;
      month = BCD_to_Int((unsigned char)buff[5]);
      date = BCD_to_Int((unsigned char)buff[6]);
      hour = BCD_to_Int((unsigned char)buff[7]);
      minute = BCD_to_Int((unsigned char)buff[8]);
      second = 0;
    }
    else
    {
      BC95.Report_Bit = 3;
      BC95.Incident_Pend = TRUE;//标记挂起
      return;
    }
  }
  
  
  //当前累积流量
  data[13] = Int_to_ASCLL(CurrentFlow.flow8[0]/0x10);
  data[14] = Int_to_ASCLL(CurrentFlow.flow8[0]%0x10);
  data[15] = Int_to_ASCLL(CurrentFlow.flow8[1]/0x10);
  data[16] = Int_to_ASCLL(CurrentFlow.flow8[1]%0x10);
  data[17] = Int_to_ASCLL(CurrentFlow.flow8[2]/0x10);
  data[18] = Int_to_ASCLL(CurrentFlow.flow8[2]%0x10);
  data[19] = Int_to_ASCLL(CurrentFlow.flow8[3]/0x10);
  data[20] = Int_to_ASCLL(CurrentFlow.flow8[3]%0x10);

  //结算日累积流量
  data[21] = Int_to_ASCLL(LastMonthFlow.flow8[0]/0x10);
  data[22] = Int_to_ASCLL(LastMonthFlow.flow8[0]%0x10);
  data[23] = Int_to_ASCLL(LastMonthFlow.flow8[1]/0x10);
  data[24] = Int_to_ASCLL(LastMonthFlow.flow8[1]%0x10);
  data[25] = Int_to_ASCLL(LastMonthFlow.flow8[2]/0x10);
  data[26] = Int_to_ASCLL(LastMonthFlow.flow8[2]%0x10);
  data[27] = Int_to_ASCLL(LastMonthFlow.flow8[3]/0x10);
  data[28] = Int_to_ASCLL(LastMonthFlow.flow8[3]%0x10);
  
  //电池电压
  data[29] = Int_to_ASCLL(BAT_Vol/0x1000);
  data[30] = Int_to_ASCLL(BAT_Vol%0x1000/0x100);
  data[31] = Int_to_ASCLL(BAT_Vol%0x100/0x10);
  data[32] = Int_to_ASCLL(BAT_Vol%0x10);
  
  //信号强度
  data[33] = Int_to_ASCLL(BC95.Rssi/0x10);
  data[34] = Int_to_ASCLL(BC95.Rssi%0x10);
  //温度 
  data[35] = Int_to_ASCLL((u8)Temp/0x10);
  data[36] = Int_to_ASCLL((u8)Temp%0x10);
  
  //年
  data[37] = Int_to_ASCLL(year/0x1000);
  data[38] = Int_to_ASCLL(year%0x1000/0x100);
  data[39] = Int_to_ASCLL(year%0x100/0x10);
  data[40] = Int_to_ASCLL(year%0x10); 
  //月
  data[41] = Int_to_ASCLL(month/0x10);
  data[42] = Int_to_ASCLL(month%0x10);
  //日
  data[43] = Int_to_ASCLL(date/0x10);
  data[44] = Int_to_ASCLL(date%0x10);
  //时
  data[45] = Int_to_ASCLL(hour/0x10);
  data[46] = Int_to_ASCLL(hour%0x10);
  //分
  data[47] = Int_to_ASCLL(minute/0x10);
  data[48] = Int_to_ASCLL(minute%0x10);
  //秒
  data[49] = Int_to_ASCLL(second/0x10);
  data[50] = Int_to_ASCLL(second%0x10);
  //表号
  valueH = Int_to_ASCLL(Meter_Number[0]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[0]%0x10);
  data[51] = Int_to_ASCLL(valueH/0x10);
  data[52] = Int_to_ASCLL(valueH%0x10);
  data[53] = Int_to_ASCLL(valueL/0x10);
  data[54] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[1]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[1]%0x10);
  data[55] = Int_to_ASCLL(valueH/0x10);
  data[56] = Int_to_ASCLL(valueH%0x10);
  data[57] = Int_to_ASCLL(valueL/0x10);
  data[58] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[2]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[2]%0x10);
  data[59] = Int_to_ASCLL(valueH/0x10);
  data[60] = Int_to_ASCLL(valueH%0x10);
  data[61] = Int_to_ASCLL(valueL/0x10);
  data[62] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[3]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[3]%0x10);
  data[63] = Int_to_ASCLL(valueH/0x10);
  data[64] = Int_to_ASCLL(valueH%0x10);
  data[65] = Int_to_ASCLL(valueL/0x10);
  data[66] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[4]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[4]%0x10);
  data[67] = Int_to_ASCLL(valueH/0x10);
  data[68] = Int_to_ASCLL(valueH%0x10);
  data[69] = Int_to_ASCLL(valueL/0x10);
  data[70] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[5]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[5]%0x10);
  data[71] = Int_to_ASCLL(valueH/0x10);
  data[72] = Int_to_ASCLL(valueH%0x10);
  data[73] = Int_to_ASCLL(valueL/0x10);
  data[74] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(Meter_Number[6]/0x10);
  valueL = Int_to_ASCLL(Meter_Number[6]%0x10);
  data[75] = Int_to_ASCLL(valueH/0x10);
  data[76] = Int_to_ASCLL(valueH%0x10);
  data[77] = Int_to_ASCLL(valueL/0x10);
  data[78] = Int_to_ASCLL(valueL%0x10);
   //结算日期
  data[79] = Int_to_ASCLL(Settle_Date/0x10);
  data[80] = Int_to_ASCLL(Settle_Date%0x10);
  //上报周期
  data[81] = Int_to_ASCLL(Report_Cycle/0x1000);
  data[82] = Int_to_ASCLL(Report_Cycle%0x1000/0x100);
  data[83] = Int_to_ASCLL(Report_Cycle%0x100/0x10);
  data[84] = Int_to_ASCLL(Report_Cycle%0x10);
  //告警电压
  data[85] = Int_to_ASCLL(BAT_Alarm_Vol/0x1000);
  data[86] = Int_to_ASCLL(BAT_Alarm_Vol%0x1000/0x100);
  data[87] = Int_to_ASCLL(BAT_Alarm_Vol%0x100/0x10);
  data[88] = Int_to_ASCLL(BAT_Alarm_Vol%0x10);
  //阀门状态
  data[89] = 0x30;
  data[90] = 0x30;
  //霍尔状态
  data[91] = Int_to_ASCLL(Cal.Error/0x10);
  data[92] = Int_to_ASCLL(Cal.Error%0x10);
  //IMEI
  data[93] = Int_to_ASCLL(BC95.IMEI[0]/0x10);
  data[94] = Int_to_ASCLL(BC95.IMEI[0]%0x10);
  data[95] = Int_to_ASCLL(BC95.IMEI[1]/0x10);
  data[96] = Int_to_ASCLL(BC95.IMEI[1]%0x10);
  data[97] = Int_to_ASCLL(BC95.IMEI[2]/0x10);
  data[98] = Int_to_ASCLL(BC95.IMEI[2]%0x10);
  data[99] = Int_to_ASCLL(BC95.IMEI[3]/0x10);
  data[100] = Int_to_ASCLL(BC95.IMEI[3]%0x10);
  data[101] = Int_to_ASCLL(BC95.IMEI[4]/0x10);
  data[102] = Int_to_ASCLL(BC95.IMEI[4]%0x10);
  data[103] = Int_to_ASCLL(BC95.IMEI[5]/0x10);
  data[104] = Int_to_ASCLL(BC95.IMEI[5]%0x10);
  data[105] = Int_to_ASCLL(BC95.IMEI[6]/0x10);
  data[106] = Int_to_ASCLL(BC95.IMEI[6]%0x10);
  data[107] = Int_to_ASCLL(BC95.IMEI[7]/0x10);
  data[108] = Int_to_ASCLL(BC95.IMEI[7]%0x10);
  data[109] = Int_to_ASCLL(BC95.IMEI[8]/0x10);
  data[110] = Int_to_ASCLL(BC95.IMEI[8]%0x10);
  data[111] = Int_to_ASCLL(BC95.IMEI[9]/0x10);
  data[112] = Int_to_ASCLL(BC95.IMEI[9]%0x10);
  data[113] = Int_to_ASCLL(BC95.IMEI[10]/0x10);
  data[114] = Int_to_ASCLL(BC95.IMEI[10]%0x10);
  data[115] = Int_to_ASCLL(BC95.IMEI[11]/0x10);
  data[116] = Int_to_ASCLL(BC95.IMEI[11]%0x10);
  data[117] = Int_to_ASCLL(BC95.IMEI[12]/0x10);
  data[118] = Int_to_ASCLL(BC95.IMEI[12]%0x10);
  data[119] = Int_to_ASCLL(BC95.IMEI[13]/0x10);
  data[120] = Int_to_ASCLL(BC95.IMEI[13]%0x10);
  data[121] = Int_to_ASCLL(BC95.IMEI[14]/0x10);
  data[122] = Int_to_ASCLL(BC95.IMEI[14]%0x10);
  //ICCID
  data[123] = Int_to_ASCLL(BC95.ICCID[0]/0x10);
  data[124] = Int_to_ASCLL(BC95.ICCID[0]%0x10);
  data[125] = Int_to_ASCLL(BC95.ICCID[1]/0x10);
  data[126] = Int_to_ASCLL(BC95.ICCID[1]%0x10);
  data[127] = Int_to_ASCLL(BC95.ICCID[2]/0x10);
  data[128] = Int_to_ASCLL(BC95.ICCID[2]%0x10);
  data[129] = Int_to_ASCLL(BC95.ICCID[3]/0x10);
  data[130] = Int_to_ASCLL(BC95.ICCID[3]%0x10);
  data[131] = Int_to_ASCLL(BC95.ICCID[4]/0x10);
  data[132] = Int_to_ASCLL(BC95.ICCID[4]%0x10);
  data[133] = Int_to_ASCLL(BC95.ICCID[5]/0x10);
  data[134] = Int_to_ASCLL(BC95.ICCID[5]%0x10);
  data[135] = Int_to_ASCLL(BC95.ICCID[6]/0x10);
  data[136] = Int_to_ASCLL(BC95.ICCID[6]%0x10);
  data[137] = Int_to_ASCLL(BC95.ICCID[7]/0x10);
  data[138] = Int_to_ASCLL(BC95.ICCID[7]%0x10);
  data[139] = Int_to_ASCLL(BC95.ICCID[8]/0x10);
  data[140] = Int_to_ASCLL(BC95.ICCID[8]%0x10);
  data[141] = Int_to_ASCLL(BC95.ICCID[9]/0x10);
  data[142] = Int_to_ASCLL(BC95.ICCID[9]%0x10);
  data[143] = Int_to_ASCLL(BC95.ICCID[10]/0x10);
  data[144] = Int_to_ASCLL(BC95.ICCID[10]%0x10);
  data[145] = Int_to_ASCLL(BC95.ICCID[11]/0x10);
  data[146] = Int_to_ASCLL(BC95.ICCID[11]%0x10);
  data[147] = Int_to_ASCLL(BC95.ICCID[12]/0x10);
  data[148] = Int_to_ASCLL(BC95.ICCID[12]%0x10);
  data[149] = Int_to_ASCLL(BC95.ICCID[13]/0x10);
  data[150] = Int_to_ASCLL(BC95.ICCID[13]%0x10);
  data[151] = Int_to_ASCLL(BC95.ICCID[14]/0x10);
  data[152] = Int_to_ASCLL(BC95.ICCID[14]%0x10);
  data[153] = Int_to_ASCLL(BC95.ICCID[15]/0x10);
  data[154] = Int_to_ASCLL(BC95.ICCID[15]%0x10);
  data[155] = Int_to_ASCLL(BC95.ICCID[16]/0x10);
  data[156] = Int_to_ASCLL(BC95.ICCID[16]%0x10);
  data[157] = Int_to_ASCLL(BC95.ICCID[17]/0x10);
  data[158] = Int_to_ASCLL(BC95.ICCID[17]%0x10);
  data[159] = Int_to_ASCLL(BC95.ICCID[18]/0x10);
  data[160] = Int_to_ASCLL(BC95.ICCID[18]%0x10);
  data[161] = Int_to_ASCLL(BC95.ICCID[19]/0x10);
  data[162] = Int_to_ASCLL(BC95.ICCID[19]%0x10);
  
  //上次联网错误信息
  data[163] = Int_to_ASCLL(BC95.ErrorRecord/0x10);
  data[164] = Int_to_ASCLL(BC95.ErrorRecord%0x10);
  
  BC95_Data_Send(data,167);
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
void Report_HC_Flow(void)
{
  uint8_t data[128] = "AT+NMGS=53,0100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\r\n";
  union flow_union flow;
  
  //上1月累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF1_ADDR,&flow);
  data[13] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[14] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[15] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[16] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[17] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[18] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[19] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[20] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上2月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF2_ADDR,&flow);
  data[21] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[22] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[23] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[24] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[25] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[26] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[27] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[28] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上3月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF3_ADDR,&flow);
  data[29] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[30] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[31] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[32] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[33] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[34] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[35] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[36] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上4月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF4_ADDR,&flow);
  data[37] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[38] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[39] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[40] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[41] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[42] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[43] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[44] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上5月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF5_ADDR,&flow);
  data[45] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[46] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[47] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[48] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[49] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[50] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[51] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[52] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上6月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF6_ADDR,&flow);
  data[53] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[54] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[55] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[56] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[57] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[58] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[59] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[60] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上7月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF7_ADDR,&flow);
  data[61] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[62] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[63] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[64] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[65] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[66] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[67] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[68] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上8月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF8_ADDR,&flow);
  data[69] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[70] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[71] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[72] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[73] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[74] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[75] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[76] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上9月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF9_ADDR,&flow);
  data[77] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[78] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[79] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[80] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[81] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[82] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[83] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[84] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上10月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF10_ADDR,&flow);
  data[85] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[86] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[87] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[88] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[89] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[90] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[91] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[92] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上11月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF11_ADDR,&flow);
  data[93] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[94] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[95] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[96] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[97] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[98] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[99] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[100] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上12月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF12_ADDR,&flow); 
  data[101] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[102] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[103] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[104] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[105] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[106] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[107] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[108] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  //上13月结算日累积流量
  flow.flow32 = 0;
  Read_ACUM_Flow(SDCF13_ADDR,&flow);
  data[109] = Int_to_ASCLL(flow.flow8[0]/0x10);
  data[110] = Int_to_ASCLL(flow.flow8[0]%0x10);
  data[111] = Int_to_ASCLL(flow.flow8[1]/0x10);
  data[112] = Int_to_ASCLL(flow.flow8[1]%0x10);
  data[113] = Int_to_ASCLL(flow.flow8[2]/0x10);
  data[114] = Int_to_ASCLL(flow.flow8[2]%0x10);
  data[115] = Int_to_ASCLL(flow.flow8[3]/0x10);
  data[116] = Int_to_ASCLL(flow.flow8[3]%0x10);
  
  BC95_Data_Send(data,119);
}
/******************************************END********************************************************/