/*******************************************************************************
Copyright: 
File name: pulse.c
Description: 脉冲相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "pulse.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
/*******************************************************************************
外部变量声明区
*******************************************************************************/
/*******************************************************************************
私有变量定义区
*******************************************************************************/ 
Pulse_Struct Pulse;
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
 Description:   //脉冲配置
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_Config(void)
{
  GPIO_Init(Pulse_Cal1_Port, Pulse_Cal1_Pin, Pulse_Cal1_Mode);          //脉冲计数1引脚初始化 
  EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);             //选择引脚1，上升和下降沿中断
  EXTI_ClearITPendingBit (EXTI_IT_Pin1);                                //清中断标志位
  ITC_SetSoftwarePriority(EXTI1_IRQn, ITC_PriorityLevel_2);             //中断优先级设定2
  
  GPIO_Init(Pulse_Cal2_Port, Pulse_Cal2_Pin, Pulse_Cal2_Mode);          //脉冲计数2引脚初始化 
  EXTI_SetPinSensitivity(EXTI_Pin_0, EXTI_Trigger_Falling);             //选择引脚0，上升和下降沿中断
  EXTI_ClearITPendingBit (EXTI_IT_Pin0);                                //清中断标志位
  ITC_SetSoftwarePriority(EXTI0_IRQn, ITC_PriorityLevel_2);             //中断优先级设定2

  GPIO_Init(Pulse_Weak_Port, Pulse_Weak_Pin, Pulse_Weak_Mode);          //脉冲唤醒引脚初始化 
  EXTI_SelectPort(EXTI_Port_F);                                         //选择F端口              
  EXTI_SetHalfPortSelection(EXTI_HalfPort_F_LSB ,ENABLE);               //选择PF(3:0)
  EXTI_SetPortSensitivity(EXTI_Port_F,EXTI_Trigger_Rising_Falling);     //GPIOF接口 下降沿中断
  EXTI_ClearITPendingBit (EXTI_IT_PortF);                               //清中断标志位
  ITC_SetSoftwarePriority(EXTIE_F_PVD_IRQn, ITC_PriorityLevel_2);       //中断优先级设定

}
/*******************************************************************************
 Function:      //
 Description:   //计量1
                //反转经过4种状态，则反转水量加1
                //若连续10次只检测到计量1脉冲，则计量2霍尔故障
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_Calculate1(void)
{
  uint8_t alarm = 0;
  
  if(Pulse_Cal1_Data() == RESET)        //脉冲1下降沿
  {
    Pulse.ForwardStatus = PulseStatus1; //正转状态1

    Pulse.Sensor1LostTimes = 0;
    if(DevicePara.SensorError == SENSOR1)
    {
      DevicePara.SensorError = NORMAL;
    }
   
    alarm += Pulse_Sensor2Check();
    alarm += Pulse_MgtIfrCheck();
    if(alarm > 0)
    {
      if(FALSE == UplinkProtocol_IsReporting())
      {
        DevicePara.Mode.AlarmReport = WAKE;
        DevicePara.Event.AlarmReport = PEND;  
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //计量2
                //正转经过4种状态，则正转水量加1
                //若连续10次只检测到计量2脉冲，则计量1传感器故障
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_Calculate2(void)
{
  uint8_t alarm = 0;
  
  if(Pulse_Cal2_Data() == RESET)        //脉冲2下降沿
  {
    Pulse.ForwardStatus++;              //正转状态2
    if(Pulse.ForwardStatus == PulseStatus2)
    {
      DevicePara.ForwardFlow.flow32++;      //正转水量加1
    }
    Pulse.ForwardStatus = PulseIdle;
    
    Pulse.Sensor2LostTimes = 0;
    if(DevicePara.SensorError == SENSOR2)
    {
      DevicePara.SensorError = NORMAL;
    }
   
    alarm += Pulse_Sensor1Check();
    alarm += Pulse_MgtIfrCheck();
    if(alarm > 0)
    {
      if(FALSE == UplinkProtocol_IsReporting())
      {
        DevicePara.Mode.AlarmReport = WAKE;
        DevicePara.Event.AlarmReport = PEND;  
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //传感器1检查
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
uint8_t Pulse_Sensor1Check(void)
{
  Pulse.Sensor1LostTimes++;
  if(Pulse.Sensor1LostTimes > 10)
  {
    DevicePara.SensorError = SENSOR1;
    if(DevicePara.AlarmMark.Sensor1 == 0)  //首次故障，上报
    {
      DevicePara.AlarmMark.Sensor1 = 1;
      return 1;
    }
  }
  
  return 0;
}
/*******************************************************************************
 Function:      //
 Description:   //传感器2检查
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
uint8_t Pulse_Sensor2Check(void)
{
  Pulse.Sensor2LostTimes++;
  if(Pulse.Sensor2LostTimes > 10)
  {
    DevicePara.SensorError = SENSOR2;
    if(DevicePara.AlarmMark.Sensor2 == 0)  //首次故障，上报
    {
      DevicePara.AlarmMark.Sensor2 = 1;
      return 1;
    }
  }
  
  return 0;
}
/*******************************************************************************
 Function:      //
 Description:   //磁干扰检查 magnetic interference
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
uint8_t Pulse_MgtIfrCheck(void)
{
  uint8_t data = 0;

  data = GPIO_ReadInputData(GPIOD)&0x03;
  if(data == 0)
  {
    DevicePara.SensorError = INTERFERE;
    if(DevicePara.AlarmMark.Interfere == 0)  //首次故障，上报
    {
      DevicePara.AlarmMark.Interfere = 1;
      return 1;
    }
  }
  else
  {
    if(DevicePara.SensorError == INTERFERE)
    {
      DevicePara.SensorError = NORMAL;
    }
  }
  
  return 0;
}
/*******************************************************************************
 Function:      //
 Description:   //手动唤醒
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_ManualWake(void)
{
  uint32_t counter = 0;
  if(Pulse_Weak_Data() == RESET)
  {
    DevicePara.Mode.ManualWake = WAKE;
    SoftTimer_CreateTimer(ONCE,20000,
                          Pulse_ManualEnd);   
  }
  else
  {
    counter = SoftTimer_GetCounter(Pulse_ManualEnd);
    if( (counter > 0)&&(counter <= 5000) )              //0-5s内低电平激活上报
    {
      Pulse_ManualReport();
    }
    else if( (counter > 5000)&&(counter <= 10000) )     //5-10s低电平激活调试
    {
      Pulse_ManualDebug();
    }
    else if( (counter > 15000)&&(counter < 20000) )     //15-20s低电平激活复位
    {
      Pulse_ManualReset();
    }

    Pulse_ManualEnd();
  }
}            
/*******************************************************************************
 Function:      //
 Description:   //手动上报
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_ManualReport(void)
{
  if(FALSE == UplinkProtocol_IsReporting())
  {
    DevicePara.Mode.ManualReport = WAKE;
    DevicePara.Event.ManualReport = PEND;
  }  
}  
/*******************************************************************************
 Function:      //
 Description:   //手动调试
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_ManualDebug(void)
{
  if(DevicePara.Mode.ManualDebug == SLEEP)
  {
    DevicePara.Mode.ManualDebug = WAKE;
    DevicePara.Event.ManualDebug = PEND;
  }
} 
/*******************************************************************************
 Function:      //
 Description:   //手动复位
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_ManualReset(void)
{
  DevicePara.Mode.ManualRst = WAKE;
  DevicePara.Event.ManualRst = PEND;
}    
/*******************************************************************************
 Function:      //
 Description:   //手动复位
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Pulse_ManualEnd(void)
{
  SoftTimer_DeleteTimer(Pulse_ManualEnd);
  DevicePara.Mode.ManualWake = SLEEP;
}     
/*************************************END**************************************/

