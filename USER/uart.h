/*********************************************************************************************************
//概述：
//作者：随风飘跃    时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
//#define Uart1_Half_Duplex           //串口1半双工
#define Uart1_Full_Duplex           //串口1全双工

//#define Uart2_Half_Duplex           //串口2半双工
#define Uart2_Full_Duplex           //串口2全双工

//#define Uart3_Half_Duplex           //串口3半双工
#define Uart3_Full_Duplex           //串口3全双工

#define Uart1_RX_ENABLE           USART1->CR2 |= 0X04;
#define Uart1_RX_DISABLE          USART1->CR2 &= 0XFB;

#define Uart2_RX_ENABLE           USART2->CR2 |= 0X04;
#define Uart2_RX_DISABLE          USART2->CR2 &= 0XFB;

#define Uart3_RX_ENABLE           USART3->CR2 |= 0X04;
#define Uart3_RX_DISABLE          USART3->CR2 &= 0XFB;

#define UART1_SBUF_NUM            64//发送缓冲区大小宏定义
#define UART1_RBUF_NUM            64//接收缓冲区大小宏定义

#define UART2_SBUF_NUM            200//发送缓冲区大小宏定义
#define UART2_RBUF_NUM            256//接收缓冲区大小宏定义

#define UART3_SBUF_NUM            64//发送缓冲区大小宏定义
#define UART3_RBUF_NUM            64//接收缓冲区大小宏定义
/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
struct Str_Uart2_Data                                                           //用于串口的寄存器的结构体
{
  unsigned char R_Buffer[UART2_RBUF_NUM];                                     //定义接收缓冲
  unsigned char S_Buffer[UART2_SBUF_NUM];                                     //发送缓冲区
  bool Send_Busy;                                                              //发送忙标志
  bool Receive_Busy;                                                           //接收忙标志
  unsigned short Send_Length;                                                 //发送数据长度
  unsigned short Sent_Length;                                                 //已发送的数据长度
  unsigned short Receive_Length;                                              //接收数据长度
  bool Receive_Pend;                                                           //串口接收挂起标志
};

struct Str_Uart3_Data                                                           //用于串口的寄存器的结构体
{
  unsigned char R_Buffer[UART3_RBUF_NUM];                                     //定义接收缓冲
  unsigned char S_Buffer[UART3_SBUF_NUM];                                     //发送缓冲区
  bool Send_Busy;                                                              //发送忙标志
  bool Receive_Busy;                                                           //接收忙标志
  unsigned short Send_Length;                                                 //发送数据长度
  unsigned short Sent_Length;                                                 //已发送的数据长度
  unsigned short Receive_Length;                                              //接收数据长度
  bool Receive_Pend;                                                           //串口接收挂起标志
};
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/
extern struct Str_Uart2_Data Uart2;
extern struct Str_Uart3_Data Uart3;
/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
ErrorStatus Uart2_Send(unsigned char *Send_Data,unsigned short Send_Lenght);
unsigned short Uart2_Receive(unsigned char *R_buff);
void USART2_IRQHandler(void);
void USART2_TX_IRQHandler(void);

ErrorStatus Uart3_Send(unsigned char *Send_Data,unsigned short Send_Lenght);
unsigned short Uart3_Receive(unsigned char *R_buff);
void USART3_IRQHandler(void);
void USART3_TX_IRQHandler(void);
/********************************************************************************************************/
#endif

/******************************************END********************************************************/
