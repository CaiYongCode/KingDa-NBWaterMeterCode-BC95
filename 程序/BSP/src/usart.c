/*********************************************************************************
Copyright: 
File name: usart.c
Description: 串口相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "usart.h"
/*******************************************************************************
常量定义区
*******************************************************************************/
/*******************************************************************************
公共变量定义区
*******************************************************************************/
USART1_TypeDef  Usart1;
USART2_TypeDef  Usart2;
USART3_TypeDef  Usart3;
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
 Description:   //串口1配置函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART1_Config(uint32_t BaudRate)
{
  GPIO_Init(GPIOC, GPIO_Pin_3 , GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOC, GPIO_Pin_2 , GPIO_Mode_In_PU_No_IT);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
  USART_DeInit(USART1); 
  USART_Init(USART1, 
             BaudRate, 
             USART_WordLength_8b, 
             USART_StopBits_1,
             USART_Parity_No, 
             USART_Mode_TxRx);
  
  USART_IrDAConfig(USART1, USART_IrDAMode_Normal);
  USART_IrDACmd(USART1, ENABLE);
  
  USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
  USART_Cmd(USART1, ENABLE);

  
  
  ITC_SetSoftwarePriority(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQn, ITC_PriorityLevel_2);    //串口1发送优先级
  ITC_SetSoftwarePriority(USART1_RX_TIM5_CC_IRQn, ITC_PriorityLevel_2);                 //串口1接收优先级
}
/*******************************************************************************
 Function:      //
 Description:   //串口2配置函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART2_Config(uint32_t BaudRate)
{
  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_High_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_3 , GPIO_Mode_In_PU_No_IT);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2, ENABLE);
  USART_DeInit(USART2); 
  USART_Init(USART2, 
             BaudRate, 
             USART_WordLength_8b, 
             USART_StopBits_1,
             USART_Parity_No, 
             USART_Mode_TxRx);
  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
  USART_Cmd(USART2, ENABLE);
  
  ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn, ITC_PriorityLevel_2);    //串口2发送优先级
  ITC_SetSoftwarePriority(TIM2_CC_USART2_RX_IRQn, ITC_PriorityLevel_2);                 //串口2接收优先级
}
/*******************************************************************************
 Function:      //
 Description:   //串口3配置函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART3_Config(uint32_t BaudRate)
{
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_High_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_In_PU_No_IT);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);
  USART_DeInit(USART3);
  USART_Init(USART3,
             BaudRate,
             USART_WordLength_8b,
             USART_StopBits_1,
             USART_Parity_No,
             USART_Mode_TxRx);    
  USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);
  USART_Cmd(USART3,ENABLE);
  
  ITC_SetSoftwarePriority(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn, ITC_PriorityLevel_2);    //串口3发送优先级
  ITC_SetSoftwarePriority(TIM3_CC_USART3_RX_IRQn, ITC_PriorityLevel_2);                 //串口3接收优先级
}
/*******************************************************************************
 Function:      //
 Description:   //串口1接收中断服务函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART1_RX_IRQHandler(void)                                                   
{
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)//USART_IT_RXNE：接收中断  
  {
    if(Usart1.RxPend == FALSE)//判断当前数据已被取走
    {
      if(Usart1.RxBusy == FALSE)//判断为首次接包
      {
        Usart1.RxBusy = TRUE;//标志接收忙
        Usart1.RxLength = 0;//接收清零
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);            //允许总线空闲中断
      }
      Usart1.RxBuffer[Usart1.RxLength] = USART_ReceiveData8(USART1);//接收数据
      Usart1.RxLength++;
      if(Usart1.RxLength == USART1_RX_MAX)//接收数据超过缓冲区则串口提前挂起
      {
        Usart1.RxBusy = FALSE;//清空接收忙
        Usart1.RxPend = TRUE;//标志串口挂起
      }
    }
    else
    {
      USART_ReceiveData8(USART1);//接收数据,防止数据溢出一直进中断
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
  else if(USART_GetITStatus(USART1,USART_IT_IDLE)!= RESET)//检测总线空闲
  {
    if(Usart1.RxPend == FALSE)//判断当前数据已被取走
    {
      Usart1.RxBusy = FALSE;//清空接收忙
      Usart1.RxPend = TRUE;//标志串口挂起
      USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);            //禁止总线空闲中断
    }
    USART_ClearITPendingBit (USART1, USART_IT_IDLE);
  }
}
/*******************************************************************************
 Function:      //
 Description:   ////串口1发送中断服务函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART1_TX_IRQHandler(void)                                                   
{
  if(USART_GetITStatus(USART1,USART_IT_TC)!= RESET)//判断发送完成
  {
    if(Usart1.TxBusy != FALSE)//判断是否为发送忙状态，防止发送误判断
    {
      if(Usart1.TxLength != Usart1.TcLength)//判断 未发送完成
      {
        USART_SendData8(USART1,Usart1.TxBuffer[Usart1.TcLength]);//根据已发送字节发送下一个字节
        Usart1.TcLength++;     
      }
      else //已发送完成
      {
        USART_ITConfig(USART1,USART_IT_TC,DISABLE); //关闭发送中断
        Usart1.TxBusy = FALSE;//清空忙标志
        #ifdef USART1_HALF_DUPLEX                                      //如果是半双工则开启接收
        USART1_RX_ENABLE;
        #endif
      }
    }
    USART_ClearITPendingBit (USART1, USART_IT_TC);//清空相关标志
  }
  USART_ClearITPendingBit (USART1, USART_IT_TXE);//清空相关标志
}
/*******************************************************************************
 Function:      //
 Description:   //串口1发送函数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus USART1_TX(unsigned char *buff,unsigned short length)
{
  ErrorStatus err;  //定义返回值
  u16 i = 0;

  if(Usart1.TxBusy == FALSE)                                  //检测是否忙
  {
  #ifdef USART1_HALF_DUPLEX                                      //如果是半双工则关闭接收
    USART1_RX_DISABLE;
  #endif
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);                  //关闭发送中断
    
    if(length > USART1_TX_MAX)//如果超过缓冲区则只能按照最大缓冲发送
      Usart1.TxLength = USART1_TX_MAX;
    else
      Usart1.TxLength = length;//保存发送长度
    for(i=0;i<Usart1.TxLength;i++)
      Usart1.TxBuffer[i] = buff[i];
    Usart1.TcLength = 0;          //已发送的长度清零
    Usart1.TxBusy = TRUE;      //标志忙
    
    USART_ITConfig(USART1,USART_IT_TC,ENABLE);                  //打开发送中断
    USART_SendData8 (USART1,Usart1.TxBuffer[0]);
    Usart1.TcLength++;
  }
  else
    err = ERROR;                                                //表示发送错误
  return err; 
}
//void USART1_TX(void)
//{
//  Usart1.TcLength = 0;                                 //已发送的长度清零
//  Usart1.TxBusy = TRUE;                                //标志忙
//  USART_ITConfig(USART1,USART_IT_TC,ENABLE);            //打开发送中断
//  USART_SendData8(USART1,Usart1.TxBuffer[0]);          //发送首字节
//  Usart1.TcLength++;
//}
/*******************************************************************************
 Function:      //
 Description:   //串口1接收函数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
unsigned short USART1_RX(unsigned char *buff)
{
  unsigned short R_Len,i;
  if(Usart1.RxPend != FALSE)
  {
    for(i=0;i<Usart1.RxLength;i++)
      buff[i] = Usart1.RxBuffer[i];
    Usart1.RxPend = FALSE;
    R_Len = Usart1.RxLength;
    
    memset(Usart1.RxBuffer,'\0',Usart1.RxLength);//清接收缓冲区
  }
  else
    R_Len = 0;
  return R_Len;
}
/*******************************************************************************
 Function:      //
 Description:   //串口1清空函数
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void USART1_Free(void)
{
  Usart1.TcLength = 0;                                //清空串口1发送长度
  Usart1.RxLength = 0;                             //清空串口1接收长度
  Usart1.TxBusy = FALSE;                              //清空串口1发送忙标志  
  Usart1.RxBusy = FALSE;                           //清空串口1接收忙
  Usart1.RxPend = FALSE;                           //清空串口1挂起
}
/*******************************************************************************
 Function:      //
 Description:   //串口2接收中断服务函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART2_RX_IRQHandler(void)                                                   
{
  if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)//USART_IT_RXNE：接收中断  
  {
    if(Usart2.RxPend == FALSE)//判断当前数据已被取走
    {
      if(Usart2.RxBusy == FALSE)//判断为首次接包
      {
        Usart2.RxBusy = TRUE;//标志接收忙
        Usart2.RxLength = 0;//接收清零
        USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);            //允许总线空闲中断
      }
      Usart2.RxBuffer[Usart2.RxLength] = USART_ReceiveData8 (USART2);//接收数据
      Usart2.RxLength++;
      if(Usart2.RxLength == USART2_RX_MAX)//接收数据超过缓冲区则串口提前挂起
      {
        Usart2.RxBusy = FALSE;//清空接收忙
        Usart2.RxPend = TRUE;//标志串口挂起
      }
    }
    else
    {
      USART_ReceiveData8(USART2);//接收数据,防止数据溢出一直进中断
    }
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
  else if(USART_GetITStatus(USART2,USART_IT_IDLE)!= RESET)//检测总线空闲
  {
    if(Usart2.RxPend == FALSE)//判断当前数据已被取走
    {
      Usart2.RxBusy = FALSE;//清空接收忙
      Usart2.RxPend = TRUE;//标志串口挂起
      USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);            //禁止总线空闲中断
    }
    USART_ClearITPendingBit (USART2, USART_IT_IDLE);
  }
  else if(USART_GetITStatus(USART2,USART_IT_OR)!= RESET)//USART_IT_OR：溢出中断  
  {
    USART_ReceiveData8 (USART2);//接收数据
    USART_ClearITPendingBit(USART2, USART_IT_OR);
  }
  
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART2_TX_IRQHandler(void)                                                   //串口2发送中断服务函数
{
  if(USART_GetITStatus(USART2,USART_IT_TC)!= RESET)//判断发送完成
  {
    if(Usart2.TxBusy != FALSE)//判断是否为发送忙状态，防止发送误判断
    {
      if(Usart2.TxLength != Usart2.TcLength)//判断 未发送完成
      {
        USART_SendData8 (USART2,Usart2.TxBuffer[Usart2.TcLength]);//根据已发送字节发送下一个字节
        Usart2.TcLength++;     
      }
      else //已发送完成
      {
        USART_ITConfig(USART2,USART_IT_TC,DISABLE); //关闭发送中断
        Usart2.TxBusy = FALSE;//清空忙标志
        #ifdef Usart2_Half_Duplex                                      //如果是半双工则开启接收
        Usart2_RX_ENABLE;
        #endif
      }
    }
    USART_ClearITPendingBit (USART2, USART_IT_TC);//清空相关标志
  }

  USART_ClearITPendingBit (USART2, USART_IT_TXE);//清空相关标志
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
//ErrorStatus USART2_TX(unsigned char *buff,unsigned short length)
//{
//  ErrorStatus err;  //定义返回值
//  u16 i = 0;
//  
//  Usart2.TxBusy = FALSE;
//
//  if(Usart2.TxBusy == FALSE)                                  //检测是否忙
//  {
//  #ifdef Usart2_Half_Duplex                                      //如果是半双工则关闭接收
//    Usart2_RX_DISABLE;
//  #endif
//    USART_ITConfig(USART2,USART_IT_TC,ENABLE);                  //打开发送中断
//    if(length > USART2_TX_MAX)//如果超过缓冲区则只能按照最大缓冲发送
//      Usart2.TxLength = USART2_TX_MAX;
//    else
//      Usart2.TxLength = length;//保存发送长度
//    for(i=0;i<Usart2.TxLength;i++)
//      Usart2.TxBuffer[i] = buff[i];
//    Usart2.TcLength = 0;          //已发送的长度清零
//    Usart2.TxBusy = TRUE;      //标志忙
//    USART_SendData8(USART2,Usart2.TxBuffer[0]);
//    Usart2.TcLength++;
//  }
//  else
//    err = ERROR;                                                //表示发送错误
//  return err; 
//}
void USART2_TX(void)
{
  Usart2.TcLength = 0;                                 //已发送的长度清零
  Usart2.TxBusy = TRUE;                                //标志忙
  USART_ITConfig(USART2,USART_IT_TC,ENABLE);            //打开发送中断
  USART_SendData8(USART2,Usart2.TxBuffer[0]);          //发送首字节
  Usart2.TcLength++;
}
/*******************************************************************************
 Function:      //
 Description:   //查询发送
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
//void USART2_TX_IQ(unsigned char *buff,unsigned short length)
//{
//  unsigned char i = 0;
//  unsigned short timeout = 0xFFFF;
//  
//  while(i < length)
//  {
//    USART_SendData8(USART2,*buff++);
//    while((USART_GetFlagStatus(USART2,USART_FLAG_TC))==RESET && (timeout != 0))
//    {timeout--;}
//    i++;
//  }
//}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
uint16_t USART2_RX(uint8_t *buff)
{
  uint16_t R_Len = 0;
  if(Usart2.RxPend != FALSE)
  {
    memcpy(buff,Usart2.RxBuffer,Usart2.RxLength);
    Usart2.RxPend = FALSE;
    R_Len = Usart2.RxLength;
  }
  else
    R_Len = 0;
  return R_Len;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
void USART2_Free(void)
{
  USART_ITConfig(USART2,USART_IT_TC,DISABLE); //关闭发送中断
  memset(Usart2.TxBuffer,0,USART2_TX_MAX);
  Usart2.TxLength = 0;                                //清空串口2发送长度
  Usart2.TcLength = 0;                                //清空串口2发送长度
  Usart2.TxBusy = FALSE;                              //清空串口2发送忙标志 
  memset(Usart2.RxBuffer,0,USART2_RX_MAX);
  Usart2.RxLength = 0;                             //清空串口2接收长度 
  Usart2.RxBusy = FALSE;                           //清空串口2接收忙
  Usart2.RxPend = FALSE;                           //清空串口2挂起  
}
/*******************************************************************************
 Function:      //
 Description:   //串口3中断服务函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART3_RX_IRQHandler(void)                                                   
{    
  if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)//USART_IT_RXNE：接收中断  
  {   
    if(Usart3.RxPend == FALSE)//判断当前数据已被取走
    {
      if(Usart3.RxBusy == FALSE)//判断为首次接包
      {
        Usart3.RxBusy = TRUE;//标志接收忙
        Usart3.RxLength = 0;//接收清零
        USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);            //允许总线空闲中断
      }
      Usart3.RxBuffer[Usart3.RxLength] = USART_ReceiveData8(USART3);//接收数据
      Usart3.RxLength++;
      if(Usart3.RxLength == USART3_RX_MAX)//接收数据超过缓冲区则串口提前挂起
      {
        Usart3.RxBusy = FALSE;//清空接收忙
        Usart3.RxPend = TRUE;//标志串口挂起
      }
    }
    USART_ClearITPendingBit (USART3, USART_IT_RXNE);
  }
  else if(USART_GetITStatus(USART3,USART_IT_IDLE) != RESET)//检测总线空闲
  {
    if(Usart3.RxPend == FALSE)//判断当前数据已被取走
    {
      Usart3.RxBusy = FALSE;//清空接收忙
      Usart3.RxPend = TRUE;//标志串口挂起
      USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);            //禁止总线空闲中断
    }
    USART_ClearITPendingBit (USART3, USART_IT_IDLE);
  }
}
/*******************************************************************************
 Function:      //
 Description:   //串口3发送中断服务函数
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART3_TX_IRQHandler(void)                                                   
{
  if(USART_GetITStatus(USART3,USART_IT_TC)!= RESET)//判断发送完成
  {
    if(Usart3.TxBusy != FALSE)//判断是否为发送忙状态，防止发送误判断
    {
      if(Usart3.TxLength != Usart3.TcLength)//判断 未发送完成
      {
        USART_SendData8 (USART3,Usart3.TxBuffer[Usart3.TcLength]);//根据已发送字节发送下一个字节
        Usart3.TcLength++;     
      }
      else //已发送完成
      {
        USART_ITConfig(USART3,USART_IT_TC,DISABLE); //关闭发送中断
        Usart3.TxBusy = FALSE;//清空忙标志
        #ifdef Usart3_Half_Duplex                                      //如果是半双工则开启接收
        Usart3_RX_ENABLE;
        #endif
      }
    }
    USART_ClearITPendingBit (USART3, USART_IT_TC);//清空相关标志
  }
  USART_ClearITPendingBit (USART3, USART_IT_TXE);//清空相关标志
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus USART3_TX(uint8_t *buff,uint16_t length)
{
  ErrorStatus err;  //定义返回值
 
  Usart3.TxBusy = FALSE;
  
  if(Usart3.TxBusy == FALSE)                                  //检测是否忙
  {
  #ifdef Usart3_Half_Duplex                                      //如果是半双工则关闭接收
    Usart3_RX_DISABLE;
  #endif
    USART_ITConfig(USART3,USART_IT_TC,ENABLE);                //允许串口3发送中断。  
    if(length > USART3_TX_MAX)//如果超过缓冲区则只能按照最大缓冲发送
      Usart3.TxLength = USART3_TX_MAX;
    else
      Usart3.TxLength = length;//保存发送长度
    memcpy(Usart3.TxBuffer,buff,Usart3.TxLength);
    Usart3.TcLength = 0;          //已发送的长度清零
    Usart3.TxBusy = TRUE;      //标志忙
    USART_SendData8(USART3,Usart3.TxBuffer[0]);
    Usart3.TcLength++;
  }
  else
    err = ERROR;                                                //表示发送错误
  return err;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
uint16_t USART3_RX(uint8_t *buff)
{
  uint16_t R_Len = 0;
  if(Usart3.RxPend != FALSE)
  {
    memcpy(buff,Usart3.RxBuffer,Usart3.RxLength);
    Usart3.RxPend = FALSE;
    R_Len = Usart3.RxLength;
  }
  else
    R_Len = 0;
  return R_Len;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void USART3_Free(void)
{
  USART_ITConfig(USART3,USART_IT_TC,DISABLE); //关闭发送中断
  memset(Usart3.TxBuffer,0,USART3_TX_MAX);
  Usart3.TxLength = 0;                                //清空串口2发送长度
  Usart3.TcLength = 0;                                //清空串口2发送长度
  Usart3.TxBusy = FALSE;                              //清空串口2发送忙标志 
  memset(Usart3.RxBuffer,0,USART3_RX_MAX);
  Usart3.RxLength = 0;                             //清空串口2接收长度 
  Usart3.RxBusy = FALSE;                           //清空串口2接收忙
  Usart3.RxPend = FALSE;                           //清空串口2挂起
}
/*************************************END**************************************/

