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
  MeterParameter.DeviceStatus = RUN;
  
  USART2_Configuration();       //初始化串口2
  
  GPIO_SetBits(GPIOE,GPIO_Pin_2);       //VBAT拉高        3.1-4.2V，典型值3.6V
  GPIO_SetBits(GPIOE,GPIO_Pin_1);      //复位脚拉低
  
  BC95.Report_Bit = 1;
  
  Create_Timer(ONCE,1,
                     BC95_Reset,0,PROCESS); 
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
  
  BC95.Report_Bit = 0;
  BC95.Start_Process = BC95_POWER_DOWN;
  BC95.Incident_Pend = FALSE; //清除事件挂起
  
  Free_Uart2();
  USART_DeInit(USART2);
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2,DISABLE);
  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_3 , GPIO_Mode_Out_PP_Low_Slow);
  
  MeterParameter.DeviceStatus = SLEEP;
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
  
//  Create_Timer(ONCE,5,
//               BC95_Start,0,PROCESS); 
  BC95_Start();
}
/*********************************************************************************
 Function:      //
 Description:   //BC95启动
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void BC95_Start(void)        
{  
  BC95.Start_Process = NRB; //指向下一个流程
  BC95.Incident_Pend = TRUE; //事件标志挂起
  BC95.TimeoutNum = 0;   
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
  char *str1 = NULL;
  char *str2 = NULL;

  if(BC95.Incident_Pend != FALSE) //检测是否有事件挂起
  {
    BC95.Incident_Pend = FALSE; //清除事件挂起
    switch(BC95.Start_Process)
    {
    case NRB:                  //重启
      {
        BC95_Data_Send("AT+NRB\r\n",8);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;
    case AT:                  //同步波特率
      {
        BC95_Data_Send("AT\r\n",4);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS);
      }
      break;
    case CMEE:               //报告移动终端错误
      {
        BC95_Data_Send("AT+CMEE=1\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      } 
      break;
    case CGSN:                //查询IMEI      
      {
        BC95_Data_Send("AT+CGSN=1\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;  
     case CCID:               //查询CCID
      {
        BC95_Data_Send("AT+NCCID\r\n",10); 
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break; 
    case NCDP:                //设置CDP服务器 
      {
        BC95_Data_Send("AT+NCDP=180.101.147.115,5683\r\n",30);    //测试平台

//        BC95_Data_Send("AT+NCDP=117.60.157.137,5683\r\n",29);      //正式平台
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break; 
    case CFUN:               //查询全功能
      {
        BC95_Data_Send("AT+CFUN?\r\n",10);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      } 
      break;
    case NBAND:               //查询频段
      {        
        BC95_Data_Send("AT+NBAND?\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS);
      }
      break;
    case CSQ:                 //查询信号强度
      {
        BC95_Data_Send("AT+CSQ\r\n",8);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      } 
      break;  
    case CGATT:               //查询入网  
      {
        BC95_Data_Send("AT+CGATT?\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;
    case CEREG:                //查询网络注册状态     
      {
        BC95_Data_Send("AT+CEREG?\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;  
    case CSCON:                 //查询信令连接状态
      {
        BC95_Data_Send("AT+CSCON?\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS);
      }
      break; 
    case CCLK:                //查询实时时间 
      {
        BC95_Data_Send("AT+CCLK?\r\n",10);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;
    case NSMI:                 //设置发送消息指示
      {
        BC95_Data_Send("AT+NSMI=1\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;
    case NNMI:                 //设置接收消息指示
      {
        BC95_Data_Send("AT+NNMI=1\r\n",11);
        Create_Timer(ONCE,BC95_TIMEROUT_TIME,
                     BC95_Recv_Timeout_CallBack,0,PROCESS); 
      }
      break;
    case NMGS:                 //发送消息     
      {     
        Send_Data_Process();   
      }
      break;
    case BC95_RECONNECT:      //连接失败
      {
        BC95.Reconnect_Times++;
        if(BC95.Reconnect_Times >= 2)  //重连超次数则睡眠
        {
          BC95.Reconnect_Times = 0;   
          Save_History_Data();    //保存本次数据
          BC95_Power_Off(); 
        }
        else     //否则重连
        {
          BC95.Start_Process = NRB; //指向下一个流程
          BC95.Incident_Pend = TRUE; //事件标志挂起
          BC95.TimeoutNum = 0;  
          Free_Uart2();
        }
      }
      break;
    case BC95_POWER_DOWN:       //发送接收完成则直接睡眠 
      BC95_Power_Off();       
      break;
    default:
      break;
    }
  }
  if(Uart2.Receive_Pend != FALSE)//判断有数据
  {
    memset(BC95.R_Buffer,'\0',RECV_BUFF_SIZE);//清缓存
    BC95.Recv_Length = Uart2_Receive((unsigned char *)BC95.R_Buffer);//接收数据
    
//    str = strstr(BC95.R_Buffer,"ERROR");
//    if(str != NULL)
//    {
//      BC95.ErrorStep = BC95.Start_Process;
//      BC95.ErrorCode = 0;
//      if( (str[6] >= '0') && (str[6] <= '9') )
//      {
//        BC95.ErrorCode += str[5]-0x30;
//      }
//      if( (str[7] >= '0') && (str[7] <= '9') )
//      {
//        BC95.ErrorCode *=10;
//        BC95.ErrorCode += str[7]-0x30;
//      }
//      if( (str[8] >= '0') && (str[8] <= '9') )
//      {
//        BC95.ErrorCode *=10;
//        BC95.ErrorCode += str[8]-0x30;
//      }
//    }
    
    switch(BC95.Start_Process)
    {
    case NRB:                  //重启
      {
//        if(strstr(BC95.R_Buffer,"REBOOT_CAUSE_APPLICATION_AT") != NULL)
        {
          BC95.Start_Process = AT;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调 
        }
      }
      break;
    case AT:            //同步波特率
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = CMEE;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
        else
        {
          BC95.ErrorStep = AT;
        }
      }
      break;
    case CMEE:                 //报告移动终端错误
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = CGSN;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      } 
      break;
    case CGSN:                //查询IMEI
      {
        str = strstr(BC95.R_Buffer,"+CGSN");
        if( str != NULL)
        {
          memcpy(BC95.IMEI,&str[6],15);
          BC95.Start_Process = CCID;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case CCID:                //查询CCID
      {
        str = strstr(BC95.R_Buffer,"+NCCID");
        if( str != NULL)
        {
          memcpy(BC95.ICCID,&str[7],20);
          BC95.Start_Process = NCDP;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;  
    case NCDP:                 //设置CDP服务器 
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = CFUN;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;  
    case CFUN:               //查询全功能
      {
        if(strstr(BC95.R_Buffer,"+CFUN:1") != NULL)
        {         
          BC95.Start_Process = NBAND;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case NBAND:               //查询频段
      {       
        if(strstr(BC95.R_Buffer,"+NBAND:5") != NULL)    //支持频段5
        {
          BC95.Start_Process = CSQ;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
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
    
          if(BC95.Rssi < 99)
          {
            BC95.Start_Process = CGATT;
            BC95.Incident_Pend = TRUE;//标记挂起
            BC95.TimeoutNum = 0;
            Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
          }
        }
      }
      break;
    case CGATT:              //查询入网
      {
        if( strstr(BC95.R_Buffer,"+CGATT:1") != NULL)
        {        
          BC95.Start_Process = CEREG;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }       
      }
      break;
    case CEREG:       //查询网络注册状态
      {
        if( strstr(BC95.R_Buffer,"+CEREG:0,1") != NULL )//已注册
        {        
          BC95.Start_Process = CSCON;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case CSCON:       //查询信令连接状态
      {
        if( strstr(BC95.R_Buffer,"+CSCON:0,1") != NULL )//已连接
        {        
          BC95.Start_Process = CCLK;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }
      }
      break;
    case CCLK:       //查询实时时间
      {
        str = strstr(BC95.R_Buffer,"+CCLK:");
        if( str != NULL)
        {  
          GMT_to_BT((unsigned char*)str);
          
          BC95.Start_Process = NSMI;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }  
      }
      break; 
    case NSMI:                 //设置发送消息指示
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = NNMI;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }  
      }
      break;
    case  NNMI:                 //设置接收消息指示 
      {
        if(strstr(BC95.R_Buffer,"OK") != NULL)
        {         
          BC95.Start_Process = NMGS;
          BC95.Incident_Pend = TRUE;//标记挂起
          BC95.TimeoutNum = 0;
          Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
        }  
      }
      break;
    case NMGS:        //发送消息
      {  
        str1 = strstr(BC95.R_Buffer,"+NNMI:"); 
        //处理消息粘包
        while(str1 != NULL)
        { 
          str2 = strstr(str1+6,"+NNMI:"); 
          if(strnstr(str1,"+NNMI:4,AAAA0000",16) != NULL)  //上报全部参数的响应
          {  
            BC95.TimeoutNum = 0;
            BC95.Report_Bit = 2; 
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调 
          }
          else if(strnstr(str1,"+NNMI:4,AAAA0001",16) != NULL)     //上报历史流量的响应
          {
            BC95.TimeoutNum = 0;
            BC95.Report_Bit = 3;
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
          }
          else if(strnstr(str1,"+NNMI:4,AAAA0002",16) != NULL)     //上报历史数据的响应
          {
            HistoryData.Total--;
            HistoryData.Front = (HistoryData.Front+1)%HistoryDataMaxNum;
            WriteRom(HISTORY_DATA_FRONT_ADDR,&HistoryData.Front,1);
            WriteRom(HISTORY_DATA_TOTAL_ADDR,&HistoryData.Total,1);
          
            BC95.TimeoutNum = 0;
            BC95.Incident_Pend = TRUE;//标记挂起
            Delete_Timer(BC95_Recv_Timeout_CallBack);//删除超时回调
          }
          else if(strnstr(str1,"+NNMI:24,02",16) != NULL)     //设置基础参数命令
          {
            Recv_Data_Process((unsigned char*)str1);
          }
          else if(strnstr(str1,"+NNMI:8,04",16) != NULL)     //校表命令
          {
            Recv_Data_Process((unsigned char*)str1);
          }
          else if(strnstr(str1,"+NNMI:17,06",16) != NULL)     //校时命令
          {
            Recv_Data_Process((unsigned char*)str1);
          } 
          else if(strnstr(str1,"+NNMI:9,09",16) != NULL)     //设置首发时间、上传间隔、采集间隔
          {
            Recv_Data_Process((unsigned char*)str1);
          } 

          str1 = str2;
        }
      }
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
  memset(Uart2.R_Buffer,'\0',RECV_BUFF_SIZE);//清接收缓冲区
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
void BC95_Recv_Timeout_CallBack(void)//启动超时重发
{
  unsigned char TimeoutNum = 0;
  
  BC95.TimeoutNum++;
  
  if( BC95.Start_Process == NMGS )
  {
    TimeoutNum = 2;
  }
  else
  {
    TimeoutNum = 10;
  }
  if(BC95.TimeoutNum < TimeoutNum)//判断超时是否超次数
  {
    BC95.Incident_Pend = TRUE;  
  }
  else
  { 
    BC95.ErrorStep = BC95.Start_Process;
    BC95.Start_Process = BC95_RECONNECT;//启动错误
    BC95.Incident_Pend = TRUE;
    BC95.TimeoutNum = 0;
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
void BC95_Delay_CallBack(void)
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
void Recv_Data_Process(unsigned char* buff)
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
  
  i = 6;
  while(buff[i] != ',')
  {
    if( (buff[i] >= '0')&&(buff[i] <= '9') )
    {
      DataLength = DataLength*10+ASCLL_to_Int(buff[i]);
    }
    i++;
  }
  
  str = (unsigned char*)&buff[i];
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
      {//24,020004 3030303031383035303030303031 01 02D0 0140 001E
        //表号
        valueH = str[7]*0x10+str[8];
        valueL = str[9]*0x10+str[10];
        MeterParameter.MeterNumber[0] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[11]*0x10+str[12];
        valueL = str[13]*0x10+str[14];
        MeterParameter.MeterNumber[1] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[15]*0x10+str[16];
        valueL = str[17]*0x10+str[18];
        MeterParameter.MeterNumber[2] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[19]*0x10+str[20];
        valueL = str[21]*0x10+str[22];
        MeterParameter.MeterNumber[3] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[23]*0x10+str[24];
        valueL = str[25]*0x10+str[26];
        MeterParameter.MeterNumber[4] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[27]*0x10+str[28];
        valueL = str[29]*0x10+str[30];
        MeterParameter.MeterNumber[5] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        valueH = str[31]*0x10+str[32];
        valueL = str[33]*0x10+str[34];
        MeterParameter.MeterNumber[6] = ASCLL_to_Int(valueH)*0x10+ASCLL_to_Int(valueL);
        //结算日期
        MeterParameter.SettleDate = str[35]*0x10+str[36];   //设置结算日期    

        //上报频率
        MeterParameter.ReportFrequency = str[37]*0x1000+str[38]*0x100+str[39]*0x10+str[40]; //设置上报周期

        //告警电压
        MeterParameter.AlarmVoltage = str[41]*0x1000+str[42]*0x100+str[43]*0x10+str[44];
 
        //采样频率
        MeterParameter.SampleFrequency = str[45]*0x1000+str[46]*0x100+str[47]*0x10+str[48];
        
        Save_Meter_Parameter(); ///存储水表参数
        
        MeterParameter.SampleTiming = 0;
        MeterParameter.ReportTiming = 0;
        
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
      {//17,060001 3230313830313031303030303030
        //时间       
        RTC_Date.RTC_Year = str[12]*10+str[14];
        RTC_Date.RTC_Month = (RTC_Month_TypeDef)(str[16]*10+str[18]);
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
    case 0x09:           //设置首发时间、上传间隔、采集间隔
      {
        MeterParameter.FirstReportHour = str[7]*0x10+str[8];
        MeterParameter.FirstReportMinute = str[9]*0x10+str[10];
        Save_Meter_Parameter(); ///存储水表参数
        //0x0A响应
        ACK(0x0A,0x00,mid);
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
    case 1:            //发送全部参数
      {
        Report_All_Parameters();
        Create_Timer(ONCE,5,
                     BC95_Recv_Timeout_CallBack,0,PROCESS);
      }
      break;
    case 2:            //发送历史累积流量
      {
        Report_HC_Flow();
        Create_Timer(ONCE,5,
                     BC95_Recv_Timeout_CallBack,0,PROCESS);
      }
      break;
    case 3:            //发送历史数据
      {       
        if(HistoryData.Total > 0)
        {
          Report_History_Data();
          Create_Timer(ONCE,5,
                       BC95_Recv_Timeout_CallBack,0,PROCESS);
        }
        else
        {
          BC95.Report_Bit++;
          BC95.Incident_Pend = TRUE;
        }
      }
      break;
    default:
      {
        BC95.Report_Bit = 0;
        BC95.FailTimes = 0;
        Create_Timer(ONCE,5,
                     BC95_Power_Off,0,PROCESS);
      }
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
void Report_All_Parameters(void)
{
  uint8_t data[200] = "AT+NMGS=79,00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\r\n";
  union flow_union LastMonthFlow;     //上一月结算日累积流量
  uint8_t month,date,hour,minute,second;
  unsigned short year = 0;
  uint8_t valueH = 0,valueL = 0;
   
  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
  year = RTC_DateStr.RTC_Year+2000;
  month = RTC_DateStr.RTC_Month;
  date = RTC_DateStr.RTC_Date;
  hour = RTC_TimeStr.RTC_Hours;
  minute = RTC_TimeStr.RTC_Minutes;
  second = RTC_TimeStr.RTC_Seconds;
  //获取上一月累计流量
  Read_ACUM_Flow(SDCF1_ADDR,&LastMonthFlow);
  
  //测量温度
  Read_Temp();
  
  //测量电压
  Read_Voltage();
  
  //当前累积流量
  data[13] = Int_to_ASCLL(Cal.Water_Data.flow8[0]/0x10);
  data[14] = Int_to_ASCLL(Cal.Water_Data.flow8[0]%0x10);
  data[15] = Int_to_ASCLL(Cal.Water_Data.flow8[1]/0x10);
  data[16] = Int_to_ASCLL(Cal.Water_Data.flow8[1]%0x10);
  data[17] = Int_to_ASCLL(Cal.Water_Data.flow8[2]/0x10);
  data[18] = Int_to_ASCLL(Cal.Water_Data.flow8[2]%0x10);
  data[19] = Int_to_ASCLL(Cal.Water_Data.flow8[3]/0x10);
  data[20] = Int_to_ASCLL(Cal.Water_Data.flow8[3]%0x10);

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
  data[29] = Int_to_ASCLL(MeterParameter.Voltage/0x1000);
  data[30] = Int_to_ASCLL(MeterParameter.Voltage%0x1000/0x100);
  data[31] = Int_to_ASCLL(MeterParameter.Voltage%0x100/0x10);
  data[32] = Int_to_ASCLL(MeterParameter.Voltage%0x10);
  
  //信号强度
  data[33] = Int_to_ASCLL(BC95.Rssi/0x10);
  data[34] = Int_to_ASCLL(BC95.Rssi%0x10);
  //温度 
  data[35] = Int_to_ASCLL((u8)MeterParameter.Temp/0x10);
  data[36] = Int_to_ASCLL((u8)MeterParameter.Temp%0x10);
  
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
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[0]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[0]%0x10);
  data[51] = Int_to_ASCLL(valueH/0x10);
  data[52] = Int_to_ASCLL(valueH%0x10);
  data[53] = Int_to_ASCLL(valueL/0x10);
  data[54] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[1]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[1]%0x10);
  data[55] = Int_to_ASCLL(valueH/0x10);
  data[56] = Int_to_ASCLL(valueH%0x10);
  data[57] = Int_to_ASCLL(valueL/0x10);
  data[58] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[2]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[2]%0x10);
  data[59] = Int_to_ASCLL(valueH/0x10);
  data[60] = Int_to_ASCLL(valueH%0x10);
  data[61] = Int_to_ASCLL(valueL/0x10);
  data[62] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[3]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[3]%0x10);
  data[63] = Int_to_ASCLL(valueH/0x10);
  data[64] = Int_to_ASCLL(valueH%0x10);
  data[65] = Int_to_ASCLL(valueL/0x10);
  data[66] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[4]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[4]%0x10);
  data[67] = Int_to_ASCLL(valueH/0x10);
  data[68] = Int_to_ASCLL(valueH%0x10);
  data[69] = Int_to_ASCLL(valueL/0x10);
  data[70] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[5]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[5]%0x10);
  data[71] = Int_to_ASCLL(valueH/0x10);
  data[72] = Int_to_ASCLL(valueH%0x10);
  data[73] = Int_to_ASCLL(valueL/0x10);
  data[74] = Int_to_ASCLL(valueL%0x10);
  valueH = Int_to_ASCLL(MeterParameter.MeterNumber[6]/0x10);
  valueL = Int_to_ASCLL(MeterParameter.MeterNumber[6]%0x10);
  data[75] = Int_to_ASCLL(valueH/0x10);
  data[76] = Int_to_ASCLL(valueH%0x10);
  data[77] = Int_to_ASCLL(valueL/0x10);
  data[78] = Int_to_ASCLL(valueL%0x10);
   //结算日期
  data[79] = Int_to_ASCLL(MeterParameter.SettleDate/0x10);
  data[80] = Int_to_ASCLL(MeterParameter.SettleDate%0x10);
  //上报频率
  data[81] = Int_to_ASCLL(MeterParameter.ReportFrequency/0x1000);
  data[82] = Int_to_ASCLL(MeterParameter.ReportFrequency%0x1000/0x100);
  data[83] = Int_to_ASCLL(MeterParameter.ReportFrequency%0x100/0x10);
  data[84] = Int_to_ASCLL(MeterParameter.ReportFrequency%0x10);
  //告警电压
  data[85] = Int_to_ASCLL(MeterParameter.AlarmVoltage/0x1000);
  data[86] = Int_to_ASCLL(MeterParameter.AlarmVoltage%0x1000/0x100);
  data[87] = Int_to_ASCLL(MeterParameter.AlarmVoltage%0x100/0x10);
  data[88] = Int_to_ASCLL(MeterParameter.AlarmVoltage%0x10);
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
  
  //上次联网故障信息
  data[163] = Int_to_ASCLL(BC95.ErrorStep/0x10);
  data[164] = Int_to_ASCLL(BC95.ErrorStep%0x10);
  //采样频率
  data[165] = Int_to_ASCLL(MeterParameter.SampleFrequency/0x1000);
  data[166] = Int_to_ASCLL(MeterParameter.SampleFrequency%0x1000/0x100);
  data[167] = Int_to_ASCLL(MeterParameter.SampleFrequency%0x100/0x10);
  data[168] = Int_to_ASCLL(MeterParameter.SampleFrequency%0x10);
  
  BC95_Data_Send(data,171);
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
/*********************************************************************************
 Function:      //
 Description:   //上报历史数据
 Input:         //
                //
 Output:        //
 Return:        //
 Others:        //
*********************************************************************************/
unsigned char Report_History_Data(void)
{
  uint8_t data[40] = "AT+NMGS=12,080000000000000000000000\r\n";
  unsigned char buff[9] = {0};
    
  Read_History_Data(buff);

  //累积流量
  data[13] = Int_to_ASCLL(buff[0]/0x10);
  data[14] = Int_to_ASCLL(buff[0]%0x10);
  data[15] = Int_to_ASCLL(buff[1]/0x10);
  data[16] = Int_to_ASCLL(buff[1]%0x10);
  data[17] = Int_to_ASCLL(buff[2]/0x10);
  data[18] = Int_to_ASCLL(buff[2]%0x10);
  data[19] = Int_to_ASCLL(buff[3]/0x10);
  data[20] = Int_to_ASCLL(buff[3]%0x10);
  //年
  data[21] = Int_to_ASCLL((buff[4]+2000)/0x1000);
  data[22] = Int_to_ASCLL((buff[4]+2000)%0x1000/0x100);
  data[23] = Int_to_ASCLL((buff[4]+2000)%0x100/0x10);
  data[24] = Int_to_ASCLL((buff[4]+2000)%0x10); 
  //月
  data[25] = Int_to_ASCLL(buff[5]/0x10);
  data[26] = Int_to_ASCLL(buff[5]%0x10);
  //日
  data[27] = Int_to_ASCLL(buff[6]/0x10);
  data[28] = Int_to_ASCLL(buff[6]%0x10);
  //时
  data[29] = Int_to_ASCLL(buff[7]/0x10);
  data[30] = Int_to_ASCLL(buff[7]%0x10);
  //分
  data[31] = Int_to_ASCLL(buff[8]/0x10);
  data[32] = Int_to_ASCLL(buff[8]%0x10);
  //秒
  data[33] = 0x30;
  data[34] = 0x30;
  
  BC95_Data_Send(data,37);
  
  return 1;
}
/******************************************END********************************************************/