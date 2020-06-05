/*******************************************************************************
Copyright: 
File name: valveCtrl.c
Description: 阀门控制相关函数、变量
Author: 初学者cy
Version: 
Date: 
History: 
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "motor.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
Motor_TypeDef Motor;
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
 Description:   //电机初始化
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_Init(void)
{  
  GPIO_Init(Motor_PWR_PORT, Motor_PWR_Pin, Motor_PWR_Mode);     // 电机电源
  GPIO_Init(Motor_IA_PORT, Motor_IA_Pin, Motor_IA_Mode);        // 电机控制 A
  GPIO_Init(Motor_IB_PORT, Motor_IB_Pin, Motor_IB_Mode);        // 电机控制 B
  
  TIM2_OC1Init(TIM2_OCMode_PWM1 , 
               TIM2_OutputState_Enable , 
               0 , 
               TIM2_OCPolarity_High , 
               TIM2_OCIdleState_Reset);
  TIM2_OC1PreloadConfig(ENABLE);
  TIM2_SetCompare1(0);
  
  TIM2_OC2Init(TIM2_OCMode_PWM1 , 
               TIM2_OutputState_Enable , 
               0 , 
               TIM2_OCPolarity_High , 
               TIM2_OCIdleState_Reset);
  TIM2_OC2PreloadConfig(ENABLE);
  TIM2_SetCompare2(0);
  
  TIM2_CtrlPWMOutputs(ENABLE);

  Motor_ExtiInit();
}
/*******************************************************************************
 Function:      //
 Description:   //电机取消初始化
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_DeInit(void)
{
  Motor_ExtiDeInit();
  
  Motor_PWR_Rst;        //电机电源关
  Motor_IA_Rst;         //电机控制 A 置低
  Motor_IB_Rst;         //电机控制 B 置低
  
  TIM2_SetCompare1(0);
  TIM2_SetCompare2(0);
  TIM2_CtrlPWMOutputs(DISABLE);
  

  Motor.State = DISABLE;
  Motor.Direction = MotorIdle;
}
/*******************************************************************************
 Function:      //
 Description:   //电机外部中断初始化
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_ExtiInit(void)
{
  disableInterrupts();  //关总中断
   
  GPIO_Init(Motor_OL_PORT,Motor_OL_Pin, Motor_OL_Mode);         // 阀门开限位标志
  GPIO_Init(Motor_CL_PORT, Motor_CL_Pin, Motor_CL_Mode);        // 阀门关限位标志
  EXTI_SelectPort(EXTI_Port_B);                                 //选择B端口              
  EXTI_SetHalfPortSelection(EXTI_HalfPort_B_MSB ,ENABLE);       //选择PB(7:4)
  EXTI_SetPortSensitivity(EXTI_Port_B,EXTI_Trigger_Falling);    //GPIOB接口下降沿中断
  EXTI_ClearITPendingBit (EXTI_IT_PortB);                       //清中断标志位
  ITC_SetSoftwarePriority(EXTIB_G_IRQn, ITC_PriorityLevel_2);   //中断优先级设定
  
  /*比较器初始化*/
  COMP_DeInit();
  CLK_PeripheralClockConfig(CLK_Peripheral_COMP, ENABLE);
  SYSCFG_RIIOSwitchConfig(RI_IOSwitch_24, ENABLE);
  COMP_Init(COMP_InvertingInput_3_4VREFINT,COMP_OutputSelect_TIM1OCREFCLR,COMP_Speed_Fast);
  COMP_TriggerConfig(COMP_TriggerGroup_NonInvertingInput,COMP_TriggerPin_0,ENABLE);
  COMP_EdgeConfig(COMP_Selection_COMP2,COMP_Edge_Rising);
  COMP_ITConfig(COMP_Selection_COMP2,ENABLE);
  COMP_ClearITPendingBit(COMP_Selection_COMP2);
  COMP_ClearFlag(COMP_Selection_COMP2);
  
  enableInterrupts();   //开总中断
}
/*******************************************************************************
 Function:      //
 Description:   //取消初始化为默认复位状态
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_ExtiDeInit(void)
{
  GPIO_Init(Motor_OL_PORT, Motor_OL_Pin, GPIO_Mode_Out_PP_Low_Slow);    // 阀门开限位标志
  GPIO_Init(Motor_CL_PORT, Motor_CL_Pin, GPIO_Mode_Out_PP_Low_Slow);    // 阀门关限位标志
  
  COMP_ITConfig(COMP_Selection_COMP2,DISABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_COMP, DISABLE);              //关闭比较器
  COMP_DeInit();
}
/*******************************************************************************
 Function:      //
 Description:   //电机运行
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_Run(void)
{
  unsigned short ccr2;
  
  if(Motor.State != DISABLE)    //判断当前电机运行
  {
    if(Motor.Direction == CW)   //开阀处理  
    {
     ccr2 = TIM2_GetCapture1();
     if(ccr2<1000)
     {
       TIM2_SetCompare1(ccr2+1);
       TIM2_SetCompare2(0);
     }
    }
    else                        //关阀处理
    {
     ccr2 = TIM2_GetCapture2();
     if(ccr2<1000)
     {
       TIM2_SetCompare2(ccr2+1);
       TIM2_SetCompare1(0);
     }
    }
  }
}
//******************************************************************************
// Function:      //
// Description:   //电机限位中断
// Input:         //
// Output:        //
// Return:        //
// Others:        //
//*****************************************************************************/
void Motor_LimitIT(void)
{
  if(Motor.State != DISABLE)    //电机运行
  {
    if(Motor_OL_Data == RESET)         //开限位低电平
    {
      if(Motor.Direction == CW)         //正向转，开限位有效
      {
        ValveCtrl_FullOpenHandler();
      }
    }
    else if(Motor_CL_Data == RESET)     //关限位低电平
    {
      if(Motor.Direction == CCW)        //反向转，关限位有效
      {
        ValveCtrl_FullCloseHandler();
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //电机OCP中断
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void Motor_OCPIT(void)
{
  if(Motor.State != DISABLE)
  {
    ValveCtrl_OCPHandler();
    SoftTimer_DeleteTimer(ValveCtrl_TimeoutCallback);
  }
}
/*************************************END**************************************/