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
NEAR struct Get_Cal_Str Cal;
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
void Pulse_Acquire_Config(void)
{
  GPIO_Init(Cai1_PORT, Cai1_Pin , Cai1_Mode);   //初始化霍尔开关1
  GPIO_Init(Cai2_PORT, Cai2_Pin , Cai2_Mode);   //初始化霍尔开关2
  
  GPIO_Init(Weak_Up_PORT, Weak_Up_Pin , Weak_Up_Mode);   //初始化霍尔开关唤醒
  
  EXTI_SelectPort(EXTI_Port_D);
  EXTI_SetHalfPortSelection(EXTI_HalfPort_D_LSB ,ENABLE);
  EXTI_SetPortSensitivity(EXTI_Port_D,EXTI_Trigger_Falling); //GPIOD接口 下降沿中断
  EXTI_ClearITPendingBit (EXTI_IT_PortD);                    //清中断标志位
  ITC_SetSoftwarePriority(EXTID_H_IRQn , ITC_PriorityLevel_1);//中断优先级设定
  

  EXTI_SetPinSensitivity(EXTI_Pin_0, EXTI_Trigger_Falling);
  EXTI_ClearITPendingBit (EXTI_IT_Pin0);                    //清中断标志位
  ITC_SetSoftwarePriority(EXTI0_IRQn , ITC_PriorityLevel_2);//中断优先级设定
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
void ExtiD_Interrupt (void)                        //外中断D
{
  if(RESET == Cai1 || RESET == Cai2)
  {
    if(RESET == Cai1 && RESET == Cai2)       //强磁干扰
    {
      if(Cal.Error != INTERFERE) 
      {
        Cal.Error = INTERFERE;
        Cal.ErrorTimes = 0;
        BC95.Report_Bit = 1;
        if(BC95.Start_Process == BC95_POWER_DOWN)       //第一次出现，立即上报
        {
          MeterParameter.DeviceStatus = RUN;                
          BC95.Start_Process = BC95_RECONNECT;
        }
      }
    }
    else
    { 
      if(Cal.Cal_State == CAL2 && RESET == Cai1) //第1个霍尔触发 且 上次状态为第2个霍尔触发
      {
        Cal.Cal_State = CAL1;
        
        Cal.Error = NORMAL;
        Cal.ErrorTimes = 0;
      }
      else if(Cal.Cal_State == CAL1 && RESET == Cai2) //第2个霍尔触发 且 上次状态为第1个霍尔触发
      {
        Cal.Water_Data.flow32++;
        Cal.Cal_State = CAL2;
               
        Cal.Error = NORMAL;
        Cal.ErrorTimes = 0;
      }
      else if(Cal.Cal_State == CAL1 && RESET == Cai1) //第1个霍尔触发 且 上次状态为第1个霍尔触发
      {
        Cal.ErrorTimes++;
        if(Cal.ErrorTimes >= 3)
        {
          if(Cal.Error != HALL1) 
          {
            Cal.Error = HALL1;
            BC95.Report_Bit = 1;
            if(BC95.Start_Process == BC95_POWER_DOWN)
            {
              MeterParameter.DeviceStatus = RUN;      
              BC95.Start_Process = BC95_RECONNECT;
            }
          }
        }
      }
      else if(Cal.Cal_State == CAL2 && RESET == Cai2) //第2个霍尔触发 且 上次状态为第2个霍尔触发
      {
        Cal.ErrorTimes++;
        if(Cal.ErrorTimes >= 3)
        {
          if(Cal.Error != HALL2) 
          {
            Cal.Error = HALL2;
            BC95.Report_Bit = 1;
            if(BC95.Start_Process == BC95_POWER_DOWN)
            {
              MeterParameter.DeviceStatus = RUN;      
              BC95.Start_Process = BC95_RECONNECT;
            }
          }
        }
      }
    }
  }
  EXTI_ClearITPendingBit (EXTI_IT_PortD);            //清中断标志位
  EXTI_ClearITPendingBit (EXTI_IT_PortH);            //清中断标志位
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
void Exti0_Interrupt (void)                        //外中断F
{
  if(RESET == Weak_Up)
  {
    BC95.Report_Bit= 1;
    if(BC95.Start_Process == BC95_POWER_DOWN)
    {
      MeterParameter.DeviceStatus = RUN;  
      BC95.Start_Process = BC95_RECONNECT;    
    }
  }
  EXTI_ClearITPendingBit (EXTI_IT_Pin0);            //清中断标志位
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

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

