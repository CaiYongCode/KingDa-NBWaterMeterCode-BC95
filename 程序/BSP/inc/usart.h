/*******************************************************************************
Copyright: 
File name: usart.h
Description: 串口相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
#ifndef __USART_H__
#define __USART_H__
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "include.h"
/*******************************************************************************
宏定义区
*******************************************************************************/
#define USART1_HALF_DUPLEX           //串口1半双工
//#define USART1_FULL_DUPLEX            //串口1全双工

//#define USART2_HALF_DUPLEX           //串口2半双工
#define USART2_FULL_DUPLEX           //串口2全双工

//#define USART3_HALF_DUPLEX           //串口3半双工
#define USART3_FULL_DUPLEX           //串口3全双工

#define USART1_RX_ENABLE           USART1->CR2 |= 0X04;
#define USART1_RX_DISABLE          USART1->CR2 &= 0XFB;

#define USART2_RX_ENABLE           USART2->CR2 |= 0X04;
#define USART2_RX_DISABLE          USART2->CR2 &= 0XFB;

#define USART3_RX_ENABLE           USART3->CR2 |= 0X04;
#define USART3_RX_DISABLE          USART3->CR2 &= 0XFB;

#define USART1_TX_MAX            128//发送缓冲区大小宏定义
#define USART1_RX_MAX            256//接收缓冲区大小宏定义

#define USART2_TX_MAX            1055//发送缓冲区大小宏定义
#define USART2_RX_MAX            256//接收缓冲区大小宏定义

#define USART3_TX_MAX            256//发送缓冲区大小宏定义
#define USART3_RX_MAX            256//接收缓冲区大小宏定义
/*******************************************************************************
数据类型定义
*******************************************************************************/
typedef struct USART1_struct                            //串口1结构体
{
  unsigned char RxBuffer[USART1_RX_MAX];               //定义接收缓冲
  bool RxPend;                                          //串口接收挂起标志
  bool RxBusy;                                          //接收忙标志
  unsigned short RxLength;                            //接收数据长度
  
  unsigned char TxBuffer[USART1_TX_MAX];               //发送缓冲区
  bool TxBusy;                                          //发送忙标志
  unsigned short TxLength;                            //发送数据长度
  unsigned short TcLength;                            //已发送的数据长度  
}USART1_TypeDef;

typedef struct USART2_struct                            //用串口2结构体
{
  unsigned char RxBuffer[USART2_RX_MAX];               //定义接收缓冲
  bool RxPend;                                          //串口接收挂起标志
  bool RxBusy;                                          //接收忙标志
  unsigned short RxLength;                            //接收数据长度
  
  unsigned char TxBuffer[USART2_TX_MAX];               //发送缓冲区
  bool TxBusy;                                          //发送忙标志
  unsigned short TxLength;                            //发送数据长度
  unsigned short TcLength;                            //已发送的数据长度
}USART2_TypeDef;

typedef struct USART3_struct                            //串口3结构体
{
  unsigned char RxBuffer[USART3_RX_MAX];               //定义接收缓冲
  bool RxPend;                                          //串口接收挂起标志
  bool RxBusy;                                          //接收忙标志
  unsigned short RxLength;                            //接收数据长度
  
  unsigned char TxBuffer[USART3_TX_MAX];               //发送缓冲区
  bool TxBusy;                                          //发送忙标志
  unsigned short TxLength;                            //发送数据长度
  unsigned short TcLength;                            //已发送的数据长度                                                 
}USART3_TypeDef;
/*******************************************************************************
外部变量声明区
*******************************************************************************/
extern USART1_TypeDef  Usart1;
extern USART2_TypeDef  Usart2;
extern USART3_TypeDef  Usart3;
/*******************************************************************************
函数声明区
*******************************************************************************/
void USART1_Config(u32 BaudRate);
void USART2_Config(u32 BaudRate);
void USART3_Config(u32 BaudRate);

void USART1_RX_IRQHandler(void);                                                   
void USART1_TX_IRQHandler(void);                                                   
ErrorStatus USART1_TX(uint8_t *buff,uint16_t length);
//void USART1_TX(void);
uint16_t USART1_RX(uint8_t *buff);
void USART1_Free(void);

void USART2_RX_IRQHandler(void);                                                   
void USART2_TX_IRQHandler(void);                                                   
//ErrorStatus USART2_TX(unsigned char *buff,unsigned short length);
void USART2_TX(void);
//void USART2_TX_IQ(unsigned char *buff,unsigned short length);
uint16_t USART2_RX(uint8_t *buff);
void USART2_Free(void);

void USART3_RX_IRQHandler(void);                                                   
void USART3_TX_IRQHandler(void);                                                   
ErrorStatus USART3_TX(uint8_t *buff,uint16_t length);
uint16_t USART3_RX(uint8_t *buff);
void USART3_Free(void);
/******************************************************************************/
#endif
/*************************************END**************************************/
