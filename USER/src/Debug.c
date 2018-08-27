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
struct Debug_EN Debug;
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
void Debug_Process(void)
{
  unsigned char cmd = 0;

  if( (BC95.Start_Process == BC95_POWER_DOWN)
        &&(Debug.Status == 1)
         &&(Debug.SendData == 0) )
  {
    Debug.SendData = 1;
    Send_Debug_Data();
  }
  
  if(Uart3.Receive_Pend == TRUE)//判断有数据
  { 
    Uart3_Receive(Uart3.R_Buffer);
    
    if( (Uart3.R_Buffer[0] == 0xAB)&&(Uart3.R_Buffer[1] == 0xAB) )
    {
      cmd = Uart3.R_Buffer[2];
      switch(cmd)
      {
        case 0x01:
          {
            Debug.Status = 1;
            Debug_ACK_OK(cmd);
          }
          break;
        case 0x02:      //读取数据
          {
            if(BC95.Start_Process != BC95_POWER_DOWN)
            {
              Debug_ACK_Busy(cmd);
            }
            else
            {
              Send_Debug_Data();
            }
          }
          break;
        case 0x03:      //校表
          {
            Cal.Water_Data.flow8[0] = Uart3.R_Buffer[4];
            Cal.Water_Data.flow8[1] = Uart3.R_Buffer[5];
            Cal.Water_Data.flow8[2] = Uart3.R_Buffer[6];
            Cal.Water_Data.flow8[3] = Uart3.R_Buffer[7];
            Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);
            
            Debug_ACK_OK(cmd);
          }
          break;
        case 0x04:      //调试结束
          {
            Debug.Status = 0;
            Create_Timer(ONCE,2,MCU_DeInit,0,PROCESS); 
            Debug_ACK_OK(cmd);
          }
          break;
        default:
          break;
      }
      
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
void Debug_ACK_Busy(unsigned char cmd)
{
  unsigned char data[4] = {0};

  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = cmd;
  data[3] = 0x00;
  
  Uart3_Send(data,4);
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
void Debug_ACK_OK(unsigned char cmd)
{
  unsigned char data[4] = {0};

  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = cmd;
  data[3] = 0x01;
  
  Uart3_Send(data,4);
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
void Send_Debug_Data(void)
{
  unsigned char data[24] = {0};
   
  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);

  //获取上次联网错误信息
  Read_BC95_ErrorRecord();
  
  data[0] = 0xBA;
  data[1] = 0xBA;
  data[2] = 0x02;
  data[3] = 0x01;
  
  //当前累积流量
  data[4] = Cal.Water_Data.flow8[0];
  data[5] = Cal.Water_Data.flow8[1];
  data[6] = Cal.Water_Data.flow8[2];
  data[7] = Cal.Water_Data.flow8[3];
  //电池电压
  data[8] = MeterParameter.Voltage/0x100;
  data[9] = MeterParameter.Voltage%0x100;
  //温度 
  data[10] = (u8)MeterParameter.Temp;
  //年
  data[11] = (RTC_DateStr.RTC_Year+2000)/0x100;
  data[12] = (RTC_DateStr.RTC_Year+2000)%0x100;
  //月
  data[13] = RTC_DateStr.RTC_Month;
  //日
  data[14] = RTC_DateStr.RTC_Date;
  //时
  data[15] = RTC_TimeStr.RTC_Hours;
  //分
  data[16] = RTC_TimeStr.RTC_Minutes;
  //秒
  data[17] = RTC_TimeStr.RTC_Seconds;
  //霍尔状态
  data[18] = Cal.Error;
   //信号强度
  data[19] = BC95.Rssi;
  //上次联网故障信息
  data[20] = BC95.ErrorRecord;
  
  Uart3_Send(data,21);
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

