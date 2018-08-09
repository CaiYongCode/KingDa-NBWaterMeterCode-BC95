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
NEAR struct Str_Uart2_Data Uart2;
//NEAR struct Str_Uart3_Data Uart3;
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
void USART2_IRQHandler(void)                                                   //串口2中断服务函数
{
  if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)//USART_IT_RXNE：接收中断  
  {
    if(Uart2.Receive_Pend == FALSE)//判断当前数据已被取走
    {
      if(Uart2.Receive_Busy == FALSE)//判断为首次接包
      {
        Uart2.Receive_Busy = TRUE;//标志接收忙
        Uart2.Receive_Length = 0;//接收清零
        USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);            //允许总线空闲中断
      }
      Uart2.R_Buffer[Uart2.Receive_Length] = USART_ReceiveData8 (USART2);//接收数据
      Uart2.Receive_Length++;
      if(Uart2.Receive_Length == UART2_RBUF_NUM)//接收数据超过缓冲区则串口提前挂起
      {
        Uart2.Receive_Busy = FALSE;//清空接收忙
        Uart2.Receive_Pend = TRUE;//标志串口挂起
      }
    }
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
  else if(USART_GetITStatus(USART2,USART_IT_IDLE)!= RESET)//检测总线空闲
  {
    if(Uart2.Receive_Pend == FALSE)//判断当前数据已被取走
    {
      Uart2.Receive_Busy = FALSE;//清空接收忙
      Uart2.Receive_Pend = TRUE;//标志串口挂起
      USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);            //禁止总线空闲中断
    }
    USART_ClearITPendingBit (USART2, USART_IT_IDLE);
  }
//  else if(USART_GetITStatus(USART2,USART_IT_TC)!= RESET)//判断发送完成
//  {
//    if(Uart2.Send_Busy != FALSE)//判断是否为发送忙状态，防止发送误判断
//    {
//      if(Uart2.Send_Length != Uart2.Sent_Length)//判断 未发送完成
//      {
//        USART_SendData8 (USART2,Uart2.S_Buffer[Uart2.Sent_Length]);//根据已发送字节发送下一个字节
//        Uart2.Sent_Length++;
//      
//      }
//      else //已发送完成
//      {
//        USART_ITConfig(USART2,USART_IT_TC,DISABLE); //关闭发送中断
//        Uart2.Send_Busy = FALSE;//清空忙标志
//        #ifdef Uart2_Half_Duplex                                      //如果是半双工则开启接收
//        Uart2_RX_ENABLE;
//        #endif
//      }
//    }
//    USART_ClearITPendingBit (USART2, USART_IT_TC);//清空相关标志
//  }
//  USART_ClearITPendingBit (USART2, USART_IT_TXE);//清空相关标志
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
void USART2_TX_IRQHandler(void)                                                   //串口2发送中断服务函数
{
  if(USART_GetITStatus(USART2,USART_IT_TC)!= RESET)//判断发送完成
  {
    if(Uart2.Send_Busy != FALSE)//判断是否为发送忙状态，防止发送误判断
    {
      if(Uart2.Send_Length != Uart2.Sent_Length)//判断 未发送完成
      {
        USART_SendData8 (USART2,Uart2.S_Buffer[Uart2.Sent_Length]);//根据已发送字节发送下一个字节
        Uart2.Sent_Length++;     
      }
      else //已发送完成
      {
        USART_ITConfig(USART2,USART_IT_TC,DISABLE); //关闭发送中断
        Uart2.Send_Busy = FALSE;//清空忙标志
        #ifdef Uart2_Half_Duplex                                      //如果是半双工则开启接收
        Uart2_RX_ENABLE;
        #endif
      }
    }
    USART_ClearITPendingBit (USART2, USART_IT_TC);//清空相关标志
  }
  USART_ClearITPendingBit (USART2, USART_IT_TXE);//清空相关标志
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
ErrorStatus Uart2_Send(unsigned char *Send_Data,unsigned short Send_Lenght)
{
  ErrorStatus err;  //定义返回值
  u16 i = 0;
  
  if(Uart2.Send_Length == Uart2.Sent_Length)//如果已发送完成，强制发送空闲
  {
    Uart2.Send_Busy = FALSE;
  }

  if(Uart2.Send_Busy == FALSE)                                  //检测是否忙
  {
  #ifdef Uart2_Half_Duplex                                      //如果是半双工则关闭接收
    Uart2_RX_DISABLE;
  #endif
    USART_ITConfig(USART2,USART_IT_TC,ENABLE);                  //打开发送中断
    if(Send_Lenght > UART2_SBUF_NUM)//如果超过缓冲区则只能按照最大缓冲发送
      Uart2.Send_Length = UART2_SBUF_NUM;
    else
      Uart2.Send_Length = Send_Lenght;//保存发送长度
    for(i=0;i<Send_Lenght;i++)
      Uart2.S_Buffer[i] = Send_Data[i];
    Uart2.Sent_Length = 0;          //已发送的长度清零
    Uart2.Send_Busy = TRUE;      //标志忙
    USART_SendData8 (USART2,Uart2.S_Buffer[0]);
    Uart2.Sent_Length++;
  }
  else
    err = ERROR;                                                //表示发送错误
  return err; 
}

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
unsigned short Uart2_Receive(unsigned char *R_buff)
{
  unsigned short R_Len,i;
  if(Uart2.Receive_Pend != FALSE)
  {
    for(i=0;i<Uart2.Receive_Length;i++)
      R_buff[i] = Uart2.R_Buffer[i];
    Uart2.Receive_Pend = FALSE;
    R_Len = Uart2.Receive_Length;
  }
  else
    R_Len = 0;
  return R_Len;
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
//void USART3_IRQHandler(void)                                                   //串口3中断服务函数
//{    
//  if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)//USART_IT_RXNE：接收中断  
//  {   
//    if(Uart3.Receive_Pend == FALSE)//判断当前数据已被取走
//    {
//      if(Uart3.Receive_Busy == FALSE)//判断为首次接包
//      {
//        Uart3.Receive_Busy = TRUE;//标志接收忙
//        Uart3.Receive_Length = 0;//接收清零
//        USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);            //允许总线空闲中断
//      }
//      Uart3.R_Buffer[Uart3.Receive_Length] = USART_ReceiveData8(USART3);//接收数据
//      Uart3.Receive_Length++;
//      if(Uart3.Receive_Length == UART3_RBUF_NUM)//接收数据超过缓冲区则串口提前挂起
//      {
//        Uart3.Receive_Busy = FALSE;//清空接收忙
//        Uart3.Receive_Pend = TRUE;//标志串口挂起
//      }
//    }
//    USART_ClearITPendingBit (USART3, USART_IT_RXNE);
//  }
//  else if(USART_GetITStatus(USART3,USART_IT_IDLE) != RESET)//检测总线空闲
//  {
//    if(Uart3.Receive_Pend == FALSE)//判断当前数据已被取走
//    {
//      Uart3.Receive_Busy = FALSE;//清空接收忙
//      Uart3.Receive_Pend = TRUE;//标志串口挂起
//      USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);            //禁止总线空闲中断
//    }
//    USART_ClearITPendingBit (USART3, USART_IT_IDLE);
//  }

//  else if(USART_GetITStatus(USART3,USART_IT_TC) == SET)//判断发送完成
//  {
//    if(Uart3.Send_Busy != FALSE)//判断是否为发送忙状态，防止发送误判断
//    {
//      if(Uart3.Send_Length != Uart3.Sent_Length)//判断 未发送完成
//      {
//        USART_SendData9 (USART3,Uart3.S_Buffer[Uart3.Sent_Length]);//根据已发送字节发送下一个字节
//        Uart3.Sent_Length++;
//      }
//      else //已发送完成
//      {
//        Uart3.Send_Busy = FALSE;//清空忙标志
//        #ifdef Uart3_Half_Duplex                                      //如果是半双工则开启接收
//        Uart3_RX_ENABLE;
//        #endif
//        USART_ITConfig(USART3,USART_IT_TC,DISABLE);                //禁止串口3发送中断。  
//      }
//    }
//    USART_ClearITPendingBit (USART3, USART_IT_TC);//清空相关标志
//  }
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void USART3_TX_IRQHandler(void)                                                   //串口3发送中断服务函数
//{
//  if(USART_GetITStatus(USART3,USART_IT_TC)!= RESET)//判断发送完成
//  {
//    if(Uart3.Send_Busy != FALSE)//判断是否为发送忙状态，防止发送误判断
//    {
//      if(Uart3.Send_Length != Uart3.Sent_Length)//判断 未发送完成
//      {
//        USART_SendData8 (USART3,Uart3.S_Buffer[Uart3.Sent_Length]);//根据已发送字节发送下一个字节
//        Uart3.Sent_Length++;     
//      }
//      else //已发送完成
//      {
//        USART_ITConfig(USART3,USART_IT_TC,DISABLE); //关闭发送中断
//        Uart3.Send_Busy = FALSE;//清空忙标志
//        #ifdef Uart3_Half_Duplex                                      //如果是半双工则开启接收
//        Uart3_RX_ENABLE;
//        #endif
//      }
//    }
//    USART_ClearITPendingBit (USART3, USART_IT_TC);//清空相关标志
//  }
//  USART_ClearITPendingBit (USART3, USART_IT_TXE);//清空相关标志
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
//ErrorStatus Uart3_Send(unsigned char *Send_Data,unsigned short Send_Lenght)
//{
//  ErrorStatus err;  //定义返回值
//  unsigned short i;
////  while(Uart3.Send_Busy != FALSE);
//   if(Uart3.Send_Length == Uart3.Sent_Length)//如果已发送完成，强制发送空闲
//  {
//    Uart3.Send_Busy = FALSE;
//  }
//  if(Uart3.Send_Busy == FALSE)                                  //检测是否忙
//  {
//  #ifdef Uart3_Half_Duplex                                      //如果是半双工则关闭接收
//    Uart3_RX_DISABLE;
//  #endif
//    USART_ITConfig(USART3,USART_IT_TC,ENABLE);                //允许串口3发送中断。  
//    if(Send_Lenght > UART3_SBUF_NUM)//如果超过缓冲区则只能按照最大缓冲发送
//      Uart3.Send_Length = UART3_SBUF_NUM;
//    else
//      Uart3.Send_Length = Send_Lenght;//保存发送长度
//    for(i=0;i<Send_Lenght;i++)
//      Uart3.S_Buffer[i] = Send_Data[i];
//    Uart3.Sent_Length = 0;          //已发送的长度清零
//    Uart3.Send_Busy = TRUE;      //标志忙
//    USART_SendData8(USART3,Uart3.S_Buffer[0]);
//    Uart3.Sent_Length++;
//  }
//  else
//    err = ERROR;                                                //表示发送错误
//  return err;
//}

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:		    //
 Others:        //
*********************************************************************************/
//unsigned short Uart3_Receive(unsigned char *R_buff)
//{
//  unsigned short R_Len,i;
//  if(Uart3.Receive_Pend != FALSE)
//  {
//    for(i=0;i<Uart3.Receive_Length;i++)
//      R_buff[i] = Uart3.R_Buffer[i];
//    Uart3.Receive_Pend = FALSE;
//    R_Len = Uart3.Receive_Length;
//  }
//  else
//    R_Len = 0;
//  return R_Len;
//}
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

