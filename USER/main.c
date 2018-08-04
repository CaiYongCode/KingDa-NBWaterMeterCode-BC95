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
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void main(void)
{ 
  disableInterrupts();                                      //关总中断
  RCC_Configuration();
  GPIO_Configuration();
  Rtc_Config();
  Set_Alarm();
  Pulse_Acquire_Config();
  
  IWDG_INIT(); 
  enableInterrupts();                                       //开总中断
/////////////////////////////////////////////////////////    
  Read_ACUM_Flow(ADD_FLOW_ADD,&Cal.Water_Data);         //读取当前累积流量
  Read_Meter_Parameter();                               //读取水表参数
  Read_History_Save_Index();                            //读取历史数据保存索引
  
  BC95.Report_Bit = 1;
  BC95.Start_Process = BC95_RECONNECT;
  
  while (1)
  {
//    RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
//    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
    //设备运行24小时且不在上报状态则复位
    if( (MeterParameter.DeviceRunTiming > ((u32)24*60*60))&&(BC95.Start_Process == BC95_POWER_DOWN) )
    {
      Save_Add_Flow(ADD_FLOW_ADD,&Cal.Water_Data);       //保存当前水量
      WWDG->CR = 0x80;  //看门狗复位
    }
    else
    {
      IWDG_ReloadCounter();//重载看门狗计数器
    }
    
    Sys_Timer_Process();
    BC95_Process();  
    
    if(MeterParameter.DeviceStatus == SLEEP)     //设备进入睡眠状态
    {
      Sleep();
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
void Sleep(void)
{ 
  USART_DeInit(USART2);                                         //清除USART2寄存器
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2, DISABLE);    //关闭USART2时钟
  USART_DeInit(USART3);                                         //清除USART3寄存器
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, DISABLE);    //关闭USART3时钟
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, DISABLE);
  
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow);         // 热敏电阻
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_Out_PP_Low_Slow);         // 热敏电阻ADC检测端
  
  GPIO_Init(GPIOE,GPIO_Pin_0,GPIO_Mode_Out_PP_Low_Slow);       //BC95 RI
  GPIO_Init(GPIOE,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Slow);       //BC95 复位脚
  GPIO_Init(GPIOE,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Slow);        //BC95 VBAT
  GPIO_Init(GPIOD,GPIO_Pin_6,GPIO_Mode_Out_PP_Low_Slow);        //绿灯
  GPIO_Init(GPIOD,GPIO_Pin_7,GPIO_Mode_Out_PP_Low_Slow);        //黄灯

  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_Low_Slow);    //USART2 TXD
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);    //USART3 TXD
  
  if(BC95.Report_Bit == 1)
  {
    Save_History_Data();    //保存本次数据
  }
  HistoryData.ReadIndex = 0;
  BC95.Report_Bit = 0;
  BC95.Start_Process = BC95_POWER_DOWN;
  BC95.Run_Time = 0;

  CLK_HaltConfig(CLK_Halt_FastWakeup,ENABLE);   //快速唤醒后时钟为HSI  
  PWR_FastWakeUpCmd(ENABLE);                    //开启电源管理里的快速唤醒  
  PWR_UltraLowPowerCmd(ENABLE);                 //使能电源的低功耗模式          //开启后内部参考电压获取值变小
  CLK_HSICmd(DISABLE);                          //关闭内部高速时钟

  halt();
}
/**
*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void IWDG_INIT(void)  //看门狗初始化
{ 
  IWDG_Enable();//启动看门狗
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//允许写预分频器和重载寄存器
  IWDG_SetPrescaler(IWDG_Prescaler_256);//设置IWDG预分频值
  IWDG_SetReload(0xFF);//设置重载值1.7s：(255+1)*256/38K = 1.72s
  IWDG_ReloadCounter();//重载计数器
}
/*********************************************************************************
 Function:      //
 Description:   //独立看门狗复位
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

