/*******************************************************************************
Copyright: 
File name: soft_timer.c
Description: 软定时器相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "soft_timer.h"  
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
NEAR static SoftTimer_TypeDef SoftTimer[SOFT_TIMER_MAX];
uint32_t DelayCounter_ms;             //延时计数器
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
 Description:   //软定时器进程
                //查找挂起的定时器，执行回调函数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void SoftTimer_Process(void)
{
  unsigned char i = 0;
  for(i=0;i<SOFT_TIMER_MAX;i++)
  {
    if(SoftTimer[i].Pend != FALSE)                      
    {
      SoftTimer[i].Pend = FALSE;
      SoftTimer[i].Callback();
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //滴答中断服务函数
                //判断定时任务时间已到达，则挂起
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void SoftTimer_SysTickHandler(void)                                                     
{
  uint8_t i = 0;
  for(i = 0;i < SOFT_TIMER_MAX;i++)
  {
    if(SoftTimer[i].State != DISABLE)   //判断启动的定时器
    {
      if(SoftTimer[i].Counter >= SoftTimer[i].Duration)
      {
        switch(SoftTimer[i].Mode)
        {
        case ONCE:              //单次执行
          {
            SoftTimer[i].State = DISABLE;       //定时器关闭
          }
          break;
        case CONTINUOUS:        //连续执行
          {
            //一直运行
          }
          break;
        default:
          break;     
        }
        SoftTimer[i].Pend = TRUE;
        SoftTimer[i].Counter = 0;
      }
      else
      {
        SoftTimer[i].Counter++;
      }
    }
  }
}
/*******************************************************************************
 Function:      //
 Description:   //创建定时任务
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus SoftTimer_CreateTimer(SoftTimer_Mode_TypeDef mode,uint32_t duration,void (*Callback)(void))
{
  ErrorStatus err = SUCCESS;
  uint8_t i = 0;
  
  SoftTimer_DeleteTimer(Callback);     //创建之前先删除相同定时任务
  for(i = 0;i < SOFT_TIMER_MAX;i++)
  {
    if( (SoftTimer[i].State == DISABLE)&&(SoftTimer[i].Pend == FALSE) )   //找到一个空闲的定时器
    {
      SoftTimer[i].State = ENABLE;
      SoftTimer[i].Pend = FALSE;
      SoftTimer[i].Mode = mode;
      SoftTimer[i].Duration = duration;
      SoftTimer[i].Callback = Callback;
      SoftTimer[i].Counter = 0;
      break;
    }
  }
  if(i == SOFT_TIMER_MAX)               //定时器溢出
    err = ERROR;
  return err;
}
/*******************************************************************************
 Function:      //
 Description:   //删除定时任务
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus SoftTimer_DeleteTimer(void (*Callback)(void))
{
  ErrorStatus err = ERROR;
  uint8_t i = 0;
  for(i=0;i < SOFT_TIMER_MAX;i++)
  {
    if(SoftTimer[i].Callback == Callback)
    {
      SoftTimer[i].State = DISABLE;
      SoftTimer[i].Pend = FALSE;
      err = SUCCESS;
      break;
    }
  }
  return err;
}
/*******************************************************************************
 Function:      //
 Description:   //获取定时器计数值
 Input:         //Call_Back:回调函数
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
uint32_t SoftTimer_GetCounter(void (*Callback)(void))
{
  uint32_t value = 0;
  uint8_t i = 0;
  for(i = 0;i < SOFT_TIMER_MAX;i++)
  {
    if( (SoftTimer[i].Callback == Callback)
        &&(SoftTimer[i].State != DISABLE) )
    {
      value = SoftTimer[i].Counter;
      break;
    }
  }
  return value;
}
/*******************************************************************************
 Function:      //
 Description:   //获取定时器计数值
 Input:         //Call_Back:回调函数
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void Delay_ms(uint32_t ms)
{
  DelayCounter_ms = 1;
  while(DelayCounter_ms <= ms);
  DelayCounter_ms = 0;
}
/*************************************END**************************************/
