/*******************************************************************************
Copyright: 
File name: 24xx128.c
Description: 外置EEPROM相关函数、变量
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "24xx128.h"
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
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_Power_On(void)
{
  GPIO_Init(I2C_PWR_PORT, I2C_PWR_Pin , I2C_PWR_Mode);    //电源控制引脚
  GPIO_Init(I2C_SCL_PORT, I2C_SCL_Pin , I2C_SCL_Mode);    //I2C 引脚
  GPIO_Init(I2C_SDA_PORT, I2C_SDA_Pin , I2C_SDA_Mode);    //I2C 引脚
  I2C_PWR_SET;
  delay5ms();
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_Power_Off(void)
{
  GPIO_Init(I2C_PWR_PORT, I2C_PWR_Pin , GPIO_Mode_Out_PP_Low_Slow);    //电源控制引脚
  GPIO_Init(I2C_SCL_PORT, I2C_SCL_Pin , GPIO_Mode_Out_PP_Low_Slow);    //I2C 引脚
  GPIO_Init(I2C_SDA_PORT, I2C_SDA_Pin , GPIO_Mode_Out_PP_Low_Slow);    //I2C 引脚
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_Start(void)			//起始信号
{
  I2C_SDA_OutMode;
  I2C_SDA_SET;
  I2C_SCL_SET;
  delay5us();
  I2C_SDA_RESET;
  delay5us();
  I2C_SCL_RESET;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_Stop(void)			 //停止信号
{
  I2C_SDA_OutMode;
  I2C_SDA_RESET;
  I2C_SCL_SET;
  delay5us();
  I2C_SDA_SET;
  delay5us();
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_ACK(void)			 //应答
{
  I2C_SCL_RESET;
  I2C_SDA_OutMode;
  I2C_SDA_RESET;
  delay5us();
  I2C_SCL_SET;
  delay5us();
  I2C_SCL_RESET;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_NoACK(void)			 //无应答
{
  I2C_SCL_RESET;
  I2C_SDA_OutMode;
  delay5us();
  I2C_SDA_SET;
  delay5us();
  I2C_SCL_SET;
  delay5us();
  I2C_SCL_RESET;
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
unsigned char I2C_Wait_Ack(void)    //等待应答
{  
  unsigned short ucErrTime=0;  
  I2C_SDA_InMode;
  I2C_SDA_SET;
  delay5us();
  I2C_SCL_SET;
  delay5us();  
  while(I2C_SDA) 
  {  
    ucErrTime++;  
    if(ucErrTime>250)  
    {  
      I2C_Stop();  
      return 1;  
    }  
  }  
  I2C_SCL_RESET;//时钟输出0        
  return 0;    
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void I2C_Send_Byte(unsigned char txd)  
{                          
  unsigned char t;     
  I2C_SDA_OutMode;        
  I2C_SCL_RESET;//拉低时钟开始数据传输  
  for(t=0;t<8;t++)  
  {                
       
    if((txd&0x80)>>7)  
      I2C_SDA_SET;  
    else  
      I2C_SDA_RESET;  
    txd<<=1;      
    delay5us();  
    I2C_SCL_SET;  
    delay5us(); 
    I2C_SCL_RESET;    
    delay5us();
  }      
  I2C_ACK();
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
unsigned char I2C_Read_Byte(unsigned char ack)  
{  
  unsigned char i,receive=0;  
  I2C_SDA_InMode;
  I2C_SDA_SET; 
  for(i=0;i<8;i++ )  
  {  
    I2C_SCL_RESET;   
    delay5us(); 
    I2C_SCL_SET;  
    receive<<=1;  
    if(I2C_SDA)
      receive++;     
    delay5us();  
  }                      
  if (!ack)  
    I2C_NoACK();//发送nACK  
  else  
    I2C_ACK(); //发送ACK     
  return receive;  
}  
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void _24XX128_WriteBytes(unsigned int Address,unsigned char *Data,unsigned int num)		  //按地址写入一字节数据
{
	unsigned int min_num;
	unsigned char addh,addl,j;
	unsigned int i;
	min_num=64-(Address%64);
	if(min_num>num)
		min_num=num;
	if(min_num!=64)
	{
		addh=(Address>>8)&0x00ff;
		addl=Address&0x00ff;
		I2C_Start();							      //起始位
		I2C_Send_Byte(0xa0);				   //写一字节命令
		I2C_Send_Byte(addh);				   //写一字节地址
		I2C_Send_Byte(addl);				   //写一字节地址
		for(j=0;j<min_num;j++)
		{
			I2C_Send_Byte(Data[j]);					   //写一字节数据
		}
		I2C_Stop();							   //结束位	
		Address+=min_num;	
		delay5ms();
		num-=min_num;
	}
	else
		min_num=0;
	if((num/64)!=0)
	{
		for(i=0;i<(num/64);i++)
		{
			addh=(Address>>8)&0x00ff;
			addl=Address&0x00ff;
			I2C_Start();							   //起始位
			I2C_Send_Byte(0xa0);				   //写一字节命令
			I2C_Send_Byte(addh);				   //写一字节地址
			I2C_Send_Byte(addl);				   //写一字节地址
			for(j=0;j<64;j++)
			{
				I2C_Send_Byte(Data[i*64+j+min_num]);					   //写一字节数据
			}
			I2C_Stop();							   //结束位	
			Address+=64;	
			delay5ms();				
		}
	}
	if((num%64)!=0)
	{
		addh=(Address>>8)&0x00ff;
		addl=Address&0x00ff;
		I2C_Start();							   //起始位
		I2C_Send_Byte(0xa0);				   //写一字节命令
		I2C_Send_Byte(addh);				   //写一字节地址
		I2C_Send_Byte(addl);				   //写一字节地址
		for(j=0;j<(num%64);j++)
		{
			I2C_Send_Byte(Data[num-(num%64)+j+min_num]);					   //写一字节数据
		}
		I2C_Stop();							   //结束位	
	//	Address+=64;	
		delay5ms();	
	}		
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void _24XX128_ReadBytes(unsigned int Address,unsigned char *Data,unsigned int num)					   //按地址读出一字节数据
{
	unsigned char addh,addl;
	unsigned int i;
	addh=(Address>>8)&0x00ff;
	addl=Address&0x00ff;									   
	I2C_Start();									  //起始位 
	I2C_Send_Byte(0xa0);						  //写一字节命令
	I2C_Send_Byte(addh);						  //写一字节地址
	I2C_Send_Byte(addl);						  //写一字节地址
	I2C_Start();									  //起始位
//	Order|=0x01;									  //将命令转为读命令
	I2C_Send_Byte(0xa1);						  //写读命令
	for(i=0;i<num;i++)
	{
		if(i<(num-1))
			Data[i]=I2C_Read_Byte(1);						  //读取一个几节（发送效验）
		else
			Data[i]=I2C_Read_Byte(0);						  //读取最后一个字节（不发送效验）
	}
	I2C_Stop();									  //结束位
//	return Data;									  //返回读取值
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void delay5us(void)   
{
  unsigned char i = 0;
  for(i=0;i<50;i++);
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
void delay5ms(void)   
{
  unsigned int i = 0;
  for(i=0;i<50000;i++);
  for(i=0;i<50000;i++);
}
/*******************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*******************************************************************************/
//END
