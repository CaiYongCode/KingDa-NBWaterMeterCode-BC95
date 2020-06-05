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
#include "valve_ctrl.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
ValveCtrl_TypeDef ValveCtrl;
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
内部函数定义
*******************************************************************************/
/*******************************************************************************
功能代码定义区
*******************************************************************************/
/*******************************************************************************
 Function:      //
 Description:   //获取阀门状态
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
uint8_t ValveCtrl_GetStatus(void)
{ 
  if(ValveCtrl.Status == OCPStatus)     //过流
  {

  }
  else if( Motor_OL_Data == RESET )     //全开
  {
    ValveCtrl.Status = FullOpenStatus;
  }
  else if( Motor_CL_Data == RESET )     //全关
  {
    ValveCtrl.Status = FullCloseStatus;
  }
  else                                  //半开
  {
    ValveCtrl.Status = HalfOpenStatus;
  }
  return (uint8_t)ValveCtrl.Status;
}
/*******************************************************************************
 Function:      //
 Description:   //取消初始化为默认复位状态
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_Init(void)
{
  DevicePara.Mode.ValveCtrl = WAKE;
  SoftTimer_CreateTimer(CONTINUOUS, 20000, ValveCtrl_DeInit); 
  Motor_Init();
}
/*******************************************************************************
 Function:      //
 Description:   //取消初始化为默认复位状态
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_DeInit(void)
{
  SoftTimer_DeleteTimer(ValveCtrl_DeInit);
  SoftTimer_DeleteTimer(ValveCtrl_TimeoutCallback);
  ValveCtrl.LastCmd = IdleCmd;
  ValveCtrl.NextCmd = IdleCmd;
  ValveCtrl_GetStatus();
  Motor_DeInit();
  
  DevicePara.Mode.ValveCtrl = SLEEP;
  DevicePara.Mode.MaintainValve = SLEEP;
}
/*******************************************************************************
 Function:      //
 Description:   //阀门控制命令处理
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_Process(uint8_t cmd)
{
  ValveCtrl_Init();
  ValveCtrl_GetStatus();
  switch(cmd)
  {
  case FullOpenCmd:
    {
      ValveCtrl_FullOpen();
    }
    break;
  case HalfOpenCmd:
    {
      ValveCtrl_HalfOpen();
    }
    break;
  case FullCloseCmd:
    {
      ValveCtrl_FullClose();
    }
    break;
  case MaintainCmd:
    {
      ValveCtrl_Maintain();
    }
    break;
  default:
    {
      ValveCtrl_DeInit();
    }
    break;
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀控全开
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_FullOpen(void)
{
  if( ValveCtrl.Status == FullOpenStatus )      //如果阀门已全开，返回成功
  {
    ValveCtrl_DeInit();
  }
  else                                          //全开
  {
    Motor.State = ENABLE;
    Motor.Direction = CW;
    SoftTimer_CreateTimer(ONCE, FULL_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = FullOpenCmd;
    ValveCtrl.NextCmd = IdleCmd;       //无后续控制
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀门半开
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_HalfOpen(void)
{ 
  if( ValveCtrl.Status == HalfOpenStatus )      //如果阀门已半开，返回成功
  {
    ValveCtrl_DeInit();
  }
  if( ValveCtrl.Status == FullOpenStatus )      //如果阀门已全开，半开
  {
    Motor.State = ENABLE;
    Motor.Direction = CCW;
    SoftTimer_CreateTimer(ONCE, CCWHALF_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = HalfOpenCmd;
    ValveCtrl.NextCmd = IdleCmd;       //无后续控制
  }
  else if( ValveCtrl.Status == FullCloseStatus )//如果阀门已全关，半开
  { 
    Motor.State = ENABLE;
    Motor.Direction = CW;
    SoftTimer_CreateTimer(ONCE, CWHALF_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = HalfOpenCmd;
    ValveCtrl.NextCmd = IdleCmd;       //无后续控制
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀门全关
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_FullClose(void)
{
  if( ValveCtrl.Status == FullCloseStatus )      //如果阀门已全关，返回成功
  {
    ValveCtrl_DeInit();
  }
  else                                          //关阀
  {
    Motor.State = ENABLE;
    Motor.Direction = CCW;
    SoftTimer_CreateTimer(ONCE, FULL_CTRL_TIME,
                          ValveCtrl_TimeoutCallback); 
    
    ValveCtrl.LastCmd = FullCloseCmd;
    ValveCtrl.NextCmd = IdleCmd;       //无后续控制
  }
}
/*******************************************************************************
 Function:      //
 Description:   //洗阀
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_Maintain(void)
{
  if( ValveCtrl.Status == FullOpenStatus )      //如果阀门已全开，先半开，再全开
  {  
    Motor.State = ENABLE;
    Motor.Direction = CCW;
    SoftTimer_CreateTimer(ONCE, CCWHALF_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = HalfOpenCmd;
    ValveCtrl.NextCmd = FullOpenCmd;    //下一步全开
  }
  else if(ValveCtrl.Status == FullCloseStatus)  //如果阀门已全关，先半开，再全关                    
  {
    Motor.State = ENABLE;
    Motor.Direction = CW;
    SoftTimer_CreateTimer(ONCE, CWHALF_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = HalfOpenCmd;
    ValveCtrl.NextCmd = FullCloseCmd;   //下一步全关
  }
  else                                          //如果阀门已半开，先全关，再半开
  {
    Motor.State = ENABLE;
    Motor.Direction = CCW;
    SoftTimer_CreateTimer(ONCE, FULL_CTRL_TIME,
                          ValveCtrl_TimeoutCallback);
    
    ValveCtrl.LastCmd = FullCloseCmd;
    ValveCtrl.NextCmd = HalfOpenCmd;   //下一步半开
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀控超时回调函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_TimeoutCallback(void)
{
  switch(ValveCtrl.NextCmd)
    {
    case  IdleCmd:              //空闲命令
      {
        ValveCtrl_DeInit();
      }
      break;   
    case FullOpenCmd:           //全开阀命令
      {
        Motor.State = ENABLE;
        Motor.Direction = CW;
        SoftTimer_CreateTimer(ONCE, FULL_CTRL_TIME,
                              ValveCtrl_TimeoutCallback); 
        
        ValveCtrl.LastCmd = FullOpenCmd;
        ValveCtrl.NextCmd = IdleCmd;       //无后续控制
      }
      break;
    case HalfOpenCmd:           //半开阀命令
      {
        Motor.State = ENABLE;
        Motor.Direction = CW;
        SoftTimer_CreateTimer(ONCE, CWHALF_CTRL_TIME,
                              ValveCtrl_TimeoutCallback);
        
        ValveCtrl.LastCmd = HalfOpenCmd;
        ValveCtrl.NextCmd = IdleCmd;       //无后续控制
      }
      break;
    case FullCloseCmd:          //全关阀命令
      {
        Motor.State = ENABLE;
        Motor.Direction = CCW;
        SoftTimer_CreateTimer(ONCE, FULL_CTRL_TIME,
                              ValveCtrl_TimeoutCallback); 
        
        ValveCtrl.LastCmd = FullCloseCmd;
        ValveCtrl.NextCmd = IdleCmd;       //无后续控制
      }
      break;
    default:
      break;
    }
}
/*******************************************************************************
 Function:      //
 Description:   //阀控全开处理函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_FullOpenHandler(void)
{
  switch(ValveCtrl.NextCmd)
  {
  case  IdleCmd:      //空闲命令
    {
      if(ValveCtrl.LastCmd == FullOpenCmd)
      {
        ValveCtrl_DeInit();
      }
    }
    break;   
  default:
    break;
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀控全关处理函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_FullCloseHandler(void)
{
  switch(ValveCtrl.NextCmd)
  {
  case  IdleCmd:        //空闲命令
    {
      if(ValveCtrl.LastCmd == FullCloseCmd)
      {
        ValveCtrl_DeInit();
      }
    }
    break;   
  case HalfOpenCmd:     //半开阀命令
    {
      Motor.State = ENABLE;
      Motor.Direction = CW;
      SoftTimer_CreateTimer(ONCE, CWHALF_CTRL_TIME,
                            ValveCtrl_TimeoutCallback);
      
      ValveCtrl.LastCmd = HalfOpenCmd;
      ValveCtrl.NextCmd = IdleCmd;       //无后续控制
    }
    break;
  default:
    break;
  }
}
/*******************************************************************************
 Function:      //
 Description:   //阀控全关处理函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void ValveCtrl_OCPHandler(void)
{
  ValveCtrl.Status = OCPStatus;
  ValveCtrl_DeInit();
}
/*************************************END**************************************/