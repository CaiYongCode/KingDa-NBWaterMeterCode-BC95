/*********************************************************************************************************
//概述：
//作者：随风飘跃    时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************************************/

#ifndef __24XX128_H__
#define __24XX128_H__
/*********************************************************************************************************
文件包含区
*********************************************************************************************************/
#include "include.h"
/*********************************************************************************************************
宏定义区
*********************************************************************************************************/
#define I2C_PWR_PORT        GPIOC                                 //eeprom 电源使能 高电平开 低电平关
#define I2C_PWR_Pin         GPIO_Pin_7
#define I2C_PWR_Mode        GPIO_Mode_Out_PP_Low_Slow
#define I2C_PWR_SET         GPIO_SetBits(I2C_PWR_PORT,I2C_PWR_Pin) 
#define I2C_PWR_RESET       GPIO_ResetBits(I2C_PWR_PORT,I2C_PWR_Pin)    

#define I2C_SCL_PORT        GPIOC                                 //eeprom SCL
#define I2C_SCL_Pin         GPIO_Pin_1
#define I2C_SCL_Mode        GPIO_Mode_Out_OD_Low_Slow
#define I2C_SCL_SET         GPIO_SetBits(I2C_SCL_PORT,I2C_SCL_Pin) 
#define I2C_SCL_RESET       GPIO_ResetBits(I2C_SCL_PORT,I2C_SCL_Pin)    

#define I2C_SDA_PORT        GPIOC                                 //eeprom SDA
#define I2C_SDA_Pin         GPIO_Pin_0
#define I2C_SDA_Mode        GPIO_Mode_Out_OD_Low_Slow
#define I2C_SDA_SET         GPIO_SetBits(I2C_SDA_PORT,I2C_SDA_Pin) 
#define I2C_SDA_RESET       GPIO_ResetBits(I2C_SDA_PORT,I2C_SDA_Pin)   
#define I2C_SDA             GPIO_ReadInputDataBit (I2C_SDA_PORT,I2C_SDA_Pin) 
#define I2C_SDA_InMode      I2C_SDA_PORT->DDR &= ~I2C_SDA_Pin
#define I2C_SDA_OutMode     I2C_SDA_PORT->DDR |= I2C_SDA_Pin
/*********************************************************************************************************
数据类型定义
*********************************************************************************************************/
/*********************************************************************************************************
外部变量声明区
*********************************************************************************************************/
/*********************************************************************************************************
函数声明区
*********************************************************************************************************/
void delay5us(void);
void delay5ms(void);
void I2C_Start(void);			//起始信号
void I2C_Stop(void);			 //停止信号
void I2C_ACK(void);      //ACK信号
void I2C_NoACK(void);    //无应答
unsigned char I2C_Wait_Ack(void);
void I2C_Power_On(void);
void I2C_Power_Off(void);
void I2C_Send_Byte(unsigned char txd);
unsigned char I2C_Read_Byte(unsigned char ack);
void _24XX128_ReadBytes(unsigned int Address,unsigned char *Data,unsigned int num);		       //按地址读出数据
void _24XX128_WriteBytes(unsigned int Address,unsigned char *Data,unsigned int num);		       //按地址写入数据
/********************************************************************************************************/
#endif

/******************************************END********************************************************/
