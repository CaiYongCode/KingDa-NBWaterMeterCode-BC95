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
unsigned char mid[4];           //命令序列号
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
  
  Create_Timer(ONCE,30,
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
  //如果需要上报消息，启动BC95
  if((BC95.Send_Bit.All_Para == 1)||(BC95.Send_Bit.HC_Flow == 1)\
    ||(BC95.Send_Bit.Vol_Alarm == 1)||(BC95.Send_Bit.Mag_Alarm == 1))
  {
    if(BC95.Start_Process == BC95_RECONNECT)
    {
      if(BC95.Reconnect_Times >= 3)  //重连超次数则睡眠
      {
        BC95.Reconnect_Times = 0;
//        BC95.Send_Bit.All_Para = 0;
//        BC95.Send_Bit.HC_Flow = 0;
//        BC95.Send_Bit.Vol_Alarm = 0;
//        BC95.Send_Bit.Mag_Alarm = 0;
        
        BC95.Start_Process = BC95_POWER_DOWN;
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
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETNBAND:               //查询频段
      {
        
        BC95_Data_Send("AT+NBAND?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETCFUN:                //查询电话功能
      {
        BC95_Data_Send("AT+CFUN?\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      } 
      break;
    case CGSN:                 //查询IMEI      
      {
        BC95_Data_Send("AT+CGSN=1\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;  
     case CIMI:                 //查询IMSI
      {
        BC95_Data_Send("AT+CIMI\r\n",9); 
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;  
    case CSQ:                //查询电话功能
      {
        BC95_Data_Send("AT+CSQ\r\n",8);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      } 
      break;
    case GETCGATT:                //查询网络激活状态    
      {
        BC95_Data_Send("AT+CGATT?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;    
    case CEREG:                //查询网络注册状态     
      {
        BC95_Data_Send("AT+CEREG?\r\n",11);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case GETNCDP:                 //查询CDP服务器
      {
        BC95_Data_Send("AT+NCDP?\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case SETNCDP:                 //设置CDP服务器 
      {
        BC95_Data_Send("AT+NCDP=180.101.147.115,5683\r\n",30);   
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case NQMGR:                 //查询消息接收缓存
      {
        BC95_Data_Send("AT+NQMGR\r\n",10);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case NMGR:                 //接收消息
      {
        BC95_Data_Send("AT+NMGR\r\n",9);
        Create_Timer(ONCE,BC95_R_TIMEROUT_TIME,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
      }
      break;
    case NMGS:                 //发送消息     
      {       
        if(Send_Data_Process() != 0)   //有消息发送
        {         
          Create_Timer(ONCE,1,
                     BC95_Start_Timeout_CallBalk,0,PROCESS);//建议定时器延时回调
        }
        else                            //消息全部发送，关机
        {
          BC95.Start_Process = BC95_POWER_DOWN;
          BC95.Incident_Pend = TRUE;//标记挂起
        }
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
  if(Uart2.Receive_Pend == TRUE)//判断是否有数据
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
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
     case GETNBAND:               //查询频段
      {       
        if(strstr(BC95.R_Buffer,"+NBAND:5") != NULL)    //支持频段5
        {
          BC95.Start_Process = GETCFUN;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
    case GETCFUN:                //查询电话功能
      {
        if(strstr(BC95.R_Buffer,"+CFUN:1") != NULL)     //全功能
        {         
          BC95.Start_Process = CGSN;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      } 
      break;
    case CGSN:         // 查询IMEI
      {
        if( strstr(BC95.R_Buffer,"+CGSN:") != NULL)//获取到IMEI
        {
          BC95.Start_Process = CIMI;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
     case CIMI:          //查询IMSI
      {
        if( strstr(BC95.R_Buffer,"OK") != NULL)
        {
          BC95.Start_Process = CSQ;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
    case CSQ:           //查询信号强度
      {
        if(strstr(BC95.R_Buffer,"+CSQ") != NULL)
        {
          BC95.Rssi =0;//保存信号强度
          BC95.Rssi += BC95.R_Buffer[7]-0x30;
          BC95.Rssi *=10;
          BC95.Rssi += BC95.R_Buffer[8]-0x30;
          BC95.Rssi %= 100;
          if(BC95.Rssi < 99)
          {
            BC95.Start_Process = GETCGATT;
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
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
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }       
      }
      break;
    case CEREG:       //查询网络注册状态
      {
        if( strstr(BC95.R_Buffer,"+CEREG:0,1") != NULL)//网络注册
        {        
          BC95.Start_Process = GETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;   
     case  GETNCDP:                 //查询CDP服务器
      {
        if( strstr(BC95.R_Buffer,"+NCDP:180.101.147.115,5683") != NULL)//获取到NCDP
        {        
          BC95.Start_Process = NQMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
        else
        {        
          BC95.Start_Process = SETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
    case  SETNCDP:                 //设置CDP服务器 
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = GETNCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }  
      }
      break;  
    case NQMGR:        //查询消息接收
      {
        if(strstr(BC95.R_Buffer,"BUFFERED=0") != NULL)  //待读消息数量为零,则开始发送消息
        {       
            BC95.Start_Process = NMGS;
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调   
        }
        else                                            //否则读取消息
        {
          BC95.Start_Process = NMGR;
          BC95.Incident_Pend = TRUE;//标记挂起
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        }
      }
      break;
    case NMGR:        //接收消息
      {
        Recv_Data_Process();
        BC95.Start_Process = NQMGR;
 //       BC95.Incident_Pend = TRUE;//标记挂起
        Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
        Create_Timer(ONCE,1,
                     BC95_Delay_CallBalk,0,PROCESS);//建议定时器延时回调,发送消息后等待1S查询消息
      }
      break;
    case NMGS:        //发送消息
      {
        if( strstr(BC95.R_Buffer,"OK") != NULL)//已发送
        { 
          BC95.Start_Process = NQMGR;
          Delete_Timer(BC95_Start_Timeout_CallBalk);//删除超时回调
          Create_Timer(ONCE,2,
                     BC95_Delay_CallBalk,0,PROCESS);//建议定时器延时回调,发送消息后等待1S查询消息
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
void BC95_Start_Timeout_CallBalk(void)//启动超时重发
{
  if(BC95.Err_Conner.Connect != 0)//判断次数是否超时
  {
    BC95.Incident_Pend = TRUE;
    BC95.Err_Conner.Connect--;
  }
  else
  {
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
  u8 messageId = 0;
  u8 month = 0;
  u8 *buff = NULL;
  u16 Data_Len = 0;
  u8 valueH = 0,valueL = 0;
  
  buff = (u8 *)strstr(BC95.R_Buffer,",");
  if(buff != NULL)
  {
    for(i = 0;i < BC95.Recv_Length;i++)
    {
      BC95.R_Buffer[i] = ASCLL_to_Int(BC95.R_Buffer[i]);
    }
    i = 0;
    while(BC95.R_Buffer[2+i] != ',')
    {
      Data_Len = Data_Len*10+BC95.R_Buffer[2+i];
      i++;
    }
    messageId = buff[1]*16+buff[2];
    mid[0] = buff[3];
    mid[1] = buff[4];
    mid[2] = buff[5];
    mid[3] = buff[6];
    
    switch(messageId)
    {
      case 0x01:            //设置实时时间
        {//17,0100013230313830343039313730323330
          Set_RTC((unsigned char *)buff);
          //0x02响应
          ACK(0x02,0x00);
        }
        break;
      case 0x04:           //校准当前累积水量
        {//7,04000200BC614E       
          Cal.Water_Data.flow8[0] = buff[7]*0x10+buff[8];
          Cal.Water_Data.flow8[1] = buff[9]*0x10+buff[10];
          Cal.Water_Data.flow8[2] = buff[11]*0x10+buff[12];
          Cal.Water_Data.flow8[3] = buff[13]*0x10+buff[14];
          Save_Add_Flow(&Cal.Water_Data);
          //0x05响应
          ACK(0x05,0x00);
          
          BC95.Send_Bit.All_Para = 1;   //校表后，立即上传全部数据
        } 
        break;
      case 0x06:           //设置结算时间
        {//6,0600041402D0
          Settle_Date = buff[7]*0x10+buff[8];   //设置结算日期
          Save_Settle_Date(); 
          Report_Cycle = buff[9]*0x1000+buff[10]*0x100+buff[11]*0x10+buff[12]; //设置上报周期
          Save_Report_Cycle();
          //0x07响应
          ACK(0x07,0x00);
        } 
        break;
      case 0x08:            //设置电池报警电压
        {//5,0800030140
          BAT_Alarm_Vol = buff[7]*0x1000+buff[8]*0x100+buff[9]*0x10+buff[10];
          Save_BAT_Alarm_Value();
          //0x09响应
          ACK(0x09,0x00);
        }
        break;
      case 0x0a:            //设置表号
        { // 17,0a00013030303031383034303030303031
          valueH = buff[7]*0x10+buff[8];
          valueL = buff[9]*0x10+buff[10];
          Meter_Number[0] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[11]*0x10+buff[12];
          valueL = buff[13]*0x10+buff[14];
          Meter_Number[1] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[15]*0x10+buff[16];
          valueL = buff[17]*0x10+buff[18];
          Meter_Number[2] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[19]*0x10+buff[20];
          valueL = buff[21]*0x10+buff[22];
          Meter_Number[3] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[23]*0x10+buff[24];
          valueL = buff[25]*0x10+buff[26];
          Meter_Number[4] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[27]*0x10+buff[28];
          valueL = buff[29]*0x10+buff[30];
          Meter_Number[5] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
          valueH = buff[31]*0x10+buff[32];
          valueL = buff[33]*0x10+buff[34];
          Meter_Number[6] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);

          Save_Meter_Number();
          //0x0b响应
          ACK(0x0b,0x00);
        }
        break;
      case 0x0c:            //设置阀门开关
        {//4,1E000601
          
          //0x0d响应
          ACK(0x0d,0x00);
        }
        break;  
      default:
        break;
    }
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
unsigned char Send_Data_Process(void)
{
  if(BC95.Send_Bit.All_Para == 1)       //发送全部参数
  {         
    Report_All_Parameters();
    BC95.Send_Bit.All_Para = 0;
    BC95.Send_Bit.HC_Flow = 1;
    return 1;
  }
  
  if(BC95.Send_Bit.HC_Flow == 1)        //发送历史累积流量
  { 
    Report_HC_Flow();
    BC95.Send_Bit.HC_Flow = 0;
    return 1;
  }
  
  if(BC95.Send_Bit.Vol_Alarm == 1)      //发送电池告警
  { 
    Report_Battery_Alarm();
    BC95.Send_Bit.Vol_Alarm = 0;
    return 1;
  }
  
  if(BC95.Send_Bit.Mag_Alarm == 1)      //发送磁告警
  {  
    Report_Magnetic_Alarm(1);
    BC95.Send_Bit.Mag_Alarm = 0;
    return 1;
  }
  
  return 0;

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
void ACK(unsigned char messageId,unsigned char errcode)
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
//unsigned char data[128] = "AT+NMGS=40,00000000DE0000006F01681F18001205020F391530303030313830353030303030310105A0014000\r\n";
void Report_All_Parameters(void)
{
  uint8_t data[128] = "AT+NMGS=40,00000000000000000000000000000000000000000000000000000000000000000000000000000000\r\n";
  union flow_union flow;     //结算日累积流量
  uint8_t year,month,date,hour,minute,second;
  uint8_t valueH = 0,valueL = 0;
  
  //获取上一月累计流量
  Read_ACUM_Flow(SDCF1_ADDR,&flow);
  //采集温度
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_High_Fast);         // 热敏电阻
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_In_FL_No_IT);      // 热敏电阻ADC检测端
  Read_Temp();
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow); 
  //获取时间     
  year = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Year);
  month = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Month);
  date = BCD_to_Int((unsigned char)RTC_DateStr.RTC_Date);
  hour = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Hours);
  minute = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Minutes);
  second = BCD_to_Int((unsigned char)RTC_TimeStr.RTC_Seconds);
  
  //当前累积流量
  data[13] = Int_to_ASCLL(Cal.Water_Data.flow32/0x10000000);
  data[14] = Int_to_ASCLL(Cal.Water_Data.flow32%0x10000000/0x1000000);
  data[15] = Int_to_ASCLL(Cal.Water_Data.flow32%0x1000000/0x100000);
  data[16] = Int_to_ASCLL(Cal.Water_Data.flow32%0x100000/0x10000);
  data[17] = Int_to_ASCLL(Cal.Water_Data.flow32%0x10000/0x1000);
  data[18] = Int_to_ASCLL(Cal.Water_Data.flow32%0x1000/0x100);
  data[19] = Int_to_ASCLL(Cal.Water_Data.flow32%0x100/0x10);
  data[20] = Int_to_ASCLL(Cal.Water_Data.flow32%0x10);

  //结算日累积流量
  data[21] = Int_to_ASCLL(flow.flow32/0x10000000);
  data[22] = Int_to_ASCLL(flow.flow32%0x10000000/0x1000000);
  data[23] = Int_to_ASCLL(flow.flow32%0x1000000/0x100000);
  data[24] = Int_to_ASCLL(flow.flow32%0x100000/0x10000);
  data[25] = Int_to_ASCLL(flow.flow32%0x10000/0x1000);
  data[26] = Int_to_ASCLL(flow.flow32%0x1000/0x100);
  data[27] = Int_to_ASCLL(flow.flow32%0x100/0x10);
  data[28] = Int_to_ASCLL(flow.flow32%0x10);
  
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
  data[39] = Int_to_ASCLL(year/0x10);
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
  
  BC95_Data_Send(data,93);
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
  uint8_t data[128] = "AT+NMGS=53,0300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\r\n";
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

/*********************************************************************************
 Function:      //
 Description:   //上报磁报警
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void Report_Magnetic_Alarm(u8 value)
{
  uint8_t data[128] = "AT+NMGS=2,0e00\r\n";
  
  data[12] = Int_to_ASCLL(value/0x10);;
  data[13] = Int_to_ASCLL(value%0x10);;
 
  BC95_Data_Send(data,16);
}
/*********************************************************************************
 Function:      //
 Description:   //上报电池报警
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
void Report_Battery_Alarm(void)
{
  uint8_t data[128] = "AT+NMGS=3,0f0000\r\n";
  
  data[12] = Int_to_ASCLL(BAT_Vol/0x1000);
  data[13] = Int_to_ASCLL(BAT_Vol%0x1000/0x100);
  data[14] = Int_to_ASCLL(BAT_Vol%0x100/0x10);
  data[15] = Int_to_ASCLL(BAT_Vol%0x10);
  
  BC95_Data_Send(data,18);
}
/******************************************END********************************************************/