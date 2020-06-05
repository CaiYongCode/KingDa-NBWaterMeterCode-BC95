/*********************************************************************************
Copyright: 
File name: rs485.h
Description: 串口相关函数、变量
Author: 清秋一滴水
Version: 
Date: 
History:       
*********************************************************************************/
#ifndef __FRAM_H__
#define __FRAM_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
/*铁电寄存器*/
#define WRSR     0x01		//write status register写状态寄存器
#define WRITE    0x02		//write memory data写数据
#define READ     0x03		//read memory data读数据
#define WRDI     0x04		// write disable禁止写操作
#define RDSR     0x05		//read status register 读状态寄存器
#define WREN     0x06		//set write enable latch允许
/*铁电CS、WP、HOLD*/
#define FRAM_PWR_Set()      GPIO_SetBits(GPIOB,GPIO_Pin_3);
#define FRAM_PWR_Rst()      GPIO_ResetBits(GPIOB,GPIO_Pin_3);

#define  cs_reset        GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define  cs_set  	 GPIO_SetBits(GPIOB, GPIO_Pin_4)
/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/
/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
/*内部调用*/
static void delay10us(void);
static void SPI_init(void);
void fram_init(void);
static void fram_off(void);
static void SPI_write_byte(unsigned char byte);
static unsigned char SPI_read_byte(void);
static void FM_WriteEnable(void);
static void FM_WriteDisable(void);

/*外部调用*/
void FM_WriteByte(unsigned int addr, unsigned char data);
unsigned char FM_ReadByte(unsigned int addr);
void FM_Write(unsigned long addr, unsigned char *pheader, unsigned int length);
void FM_Read(unsigned long addr, unsigned char *pheader, unsigned int length);
/********************************************************************************************************/
#endif
/******************************************END***********************************************************/