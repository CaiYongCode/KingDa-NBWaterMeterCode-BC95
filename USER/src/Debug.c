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
 Description:   //初始化
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Debug_Init(void)
{
  MeterParameter.Peripheral.debug = RUN;
  USART3_Configuration();  
  Create_Timer(ONCE,60,
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
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_In_FL_IT);
  
  EXTI_SetPinSensitivity(EXTI_Pin_7, EXTI_Trigger_Falling);
  EXTI_ClearITPendingBit (EXTI_IT_Pin7);                    
  ITC_SetSoftwarePriority(EXTI7_IRQn , ITC_PriorityLevel_2);
  
  MeterParameter.Peripheral.debug = SLEEP;
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
  uint8_t msgID = 0;
  uint8_t msgLen = 0;
  uint8_t dataLen = 0;
  
  if(MeterParameter.Peripheral.debug != SLEEP)
  {
    if(Uart3.Receive_Pend == TRUE)//判断有数据
    { 
      MsgLen = Uart3_Receive(buff);
      
      dataLen = Uart3.R_Buffer[3];
      if( buff[MsgLen-1] == Check_Sum8(&Uart3.R_Buffer[4],MsgLen) )
      {
        Debug.Status = TRUE;
        MsgID = Uart3.R_Buffer[5];
        switch(MsgID)
        {
          case MessageID0:
            {
            }
            break;
          case MessageID1:      //读取数据
            {
              Send_Meter_Info();
            }
            break;
          case MessageID2:      //校表
            {
              Cal.Water_Data.flow8[0] = Uart3.R_Buffer[6];
              Cal.Water_Data.flow8[1] = Uart3.R_Buffer[7];
              Cal.Water_Data.flow8[2] = Uart3.R_Buffer[8];
              Cal.Water_Data.flow8[3] = Uart3.R_Buffer[9];
              Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);
              
              Send_Meter_Info();
            }
            break;
          default:
            break;
        }
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
void Send_Meter_Info(void)
{
  unsigned char data[24] = {0};
  unsigned char sum = 0;
  
  //获取时间   
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
  //测量温度
  Read_Temp();
  //测量电压
  Read_Voltage();
  
  data[0] = 0xFE;
  data[1] = 0xFE;
  data[2] = 0x5A;
  data[3] = 0;
  data[4] = 14;
  data[5] = MessageID1;
  
  //当前累积流量
  data[6] = Cal.Water_Data.flow8[0];
  data[7] = Cal.Water_Data.flow8[1];
  data[8] = Cal.Water_Data.flow8[2];
  data[9] = Cal.Water_Data.flow8[3];
  //电池电压
  data[10] = MeterParameter.Voltage/0x100;
  data[11] = MeterParameter.Voltage%0x100;
  //温度 
  data[12] = (u8)MeterParameter.Temp;
  //年
  data[13] = RTC_DateStr.RTC_Year;
  //月
  data[14] = RTC_DateStr.RTC_Month;
  //日
  data[15] = RTC_DateStr.RTC_Date;
  //时
  data[16] = RTC_TimeStr.RTC_Hours;
  //分
  data[17] = RTC_TimeStr.RTC_Minutes;
  //秒
  data[18] = RTC_TimeStr.RTC_Seconds;
  
  sum = Check_Sum8(&data[5],14);
  data[19] = sum;
  
  Uart3_Send(data,20);
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

