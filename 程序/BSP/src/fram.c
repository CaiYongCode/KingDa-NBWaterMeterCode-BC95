/*****************************************************************************************************
Copyright: 
File name: fram.c  
Description: fram
Author: 一点水
Version: 
Date: 
History:       
*****************************************************************************************************/
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "fram.h"
/*********************************************************************************
常量定义区
*********************************************************************************/
/*********************************************************************************
公共变量定义区
*********************************************************************************/
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
/**************************************************************************************************
 * @fn      delay10us
 *
 * @brief   fram通讯是小延时
 *
 * @param   void
 *
 * @return  void
 *
 **************************************************************************************************/
static void delay10us(void)
{
  unsigned char a;
  for(a=16;a>0;a--);
}
/**************************************************************************************************
 * @fn      SPI_init
 *
 * @brief   SPI1接口初始化
 *
 * @param   void
 *
 * @return  void
 *
 **************************************************************************************************/
static void SPI_init(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_SPI1 , ENABLE);                 
    SPI_DeInit(SPI1);	
    SPI_Init(SPI1,
             SPI_FirstBit_MSB,
             SPI_BaudRatePrescaler_4,
             SPI_Mode_Master,
             SPI_CPOL_Low,
             SPI_CPHA_1Edge,
             SPI_Direction_2Lines_FullDuplex,
             SPI_NSS_Soft,
             (uint8_t)0x07);	      	
    SPI_Cmd(SPI1, ENABLE);	 
}

/**************************************************************************************************
 * @fn      fram_init
 *
 * @brief   fram初始化
 *
 * @param   void 开启电源、初始化spi
 *
 * @return  void
 *
 **************************************************************************************************/
void fram_init(void)
{
  FRAM_PWR_Set();
  SPI_init();//初始化SPI1
  GPIO_Init(GPIOB,GPIO_Pin_7,GPIO_Mode_In_PU_No_IT);
}

/**************************************************************************************************
 * @fn      fram__off
 *
 * @brief   fram关闭
 *
 * @param   void
 *
 * @return  void
 *
 **************************************************************************************************/
static void fram_off(void)
{
  FRAM_PWR_Rst();
  SPI_DeInit(SPI1);//注销SPI2
  GPIO_Init(GPIOB,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_Out_PP_Low_Slow);
}

/**************************************************************************************************
 * @fn      SPI_write_byte(unsigned char byte)
 *
 * @brief   SPI写一个字节
 *
 * @param   unsigned char byte
 *
 * @return  void
 *
 **************************************************************************************************/
static void SPI_write_byte(unsigned char byte)
{
  while((SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE))==RESET);     //等待发送完成      
	SPI_SendData(SPI1, byte);
  while ((SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE))==RESET) ; 
        SPI_ReceiveData(SPI1);  /*读取因上面发送数据产生的无效数据*/ 
}


/**************************************************************************************************
 * @fn      SPI_write_byte(unsigned char byte)
 *
 * @brief   SPI读一个字节
 *
 * @param   void
 *
 * @return  unsigned char byte;
 *
 **************************************************************************************************/
static unsigned char SPI_read_byte(void)
{
  unsigned char byte;
  while (SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET) ; 
    SPI_SendData(SPI1,0xFF);  /*  发送一个无效字节，以产生接收时钟*/ 
  while((SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE))==RESET);     //等待接收完成
    byte=SPI_ReceiveData(SPI1) ;
    //SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);  //SPIF(SPSTAT.7)标志通过软件向其写入“1”清0      
  return (byte);		
}

/**************************************************************************************************
 * @fn      FM_WriteEnable
 *
 * @brief   写使能
 *
 * @param   void
 *
 * @return  void
 *
 **************************************************************************************************/
static void FM_WriteEnable(void) //写使能 可写入
{      
  cs_set;
  delay10us();
  cs_reset;
  delay10us();
  SPI_write_byte(WREN);
  cs_set;	
}

/**************************************************************************************************
 * @fn      FM_WriteDisable
 *
 * @brief   写失能
 *
 * @param   void
 *
 * @return  void
 *
 **************************************************************************************************/
static void FM_WriteDisable(void)//不可写入
{     
  cs_reset;
  SPI_write_byte(WRDI);
  cs_set;	
}

/**************************************************************************************************
 * @fn      FM_WriteByte(unsigned int addr, unsigned char dat)
 *
 * @brief   在指定地址写入1byte的数据
 *
 * @param   unsigned int addr, unsigned char data
 *
 * @return  void
 *
 **************************************************************************************************/
void FM_WriteByte(unsigned int addr, unsigned char data)
{
  fram_init();
//  disableInterrupts();
  FM_WriteEnable();
  cs_reset;
  SPI_write_byte(WRITE);
  SPI_write_byte((addr & 0xFF00) >> 8);
  SPI_write_byte(addr & 0x00FF);  
  SPI_write_byte(data);
  cs_set;
  FM_WriteDisable();
//  enableInterrupts(); 
  fram_off();
}

/**************************************************************************************************
 * @fn      FM_ReadByte(unsigned int addr)
 *
 * @brief   从指定地址读出1byte的数据
 *
 * @param   void
 *
 * @return  unsigned char temp;
 *
 **************************************************************************************************/
unsigned char FM_ReadByte(unsigned int addr)
{
  //fram_init();
  unsigned char temp;
  cs_set;
  delay10us();
  cs_reset;
  delay10us();
  SPI_write_byte(READ);
  SPI_write_byte((addr & 0xFF00) >> 8);
  SPI_write_byte(addr & 0x00FF);
      temp = SPI_read_byte();   
  cs_set;
  //fram_off();
  return(temp);
}

/**************************************************************************************************
 * @fn      FM_Write(unsigned long addr, unsigned char *pheader, unsigned int length)
 *
 * @brief   在指定地址开始写入length byte的数据
 *
 * @param   unsigned long addr, unsigned char *pheader, unsigned int length
 *
 * @return  void
 *
 **************************************************************************************************/
void FM_Write(unsigned long addr, unsigned char *pheader, unsigned int length)
{    
  unsigned char i;
  fram_init();
//  disableInterrupts();
  FM_WriteEnable();
  delay10us();
  cs_reset;
  delay10us();
  SPI_write_byte(WRITE);
  SPI_write_byte((addr & 0xFF00) >> 8);
  SPI_write_byte(addr & 0x00FF);

  for(i = 0;i < length;i ++)  
  {
    SPI_write_byte(pheader[i]);
  }	
  cs_set;	
  delay10us();
  FM_WriteDisable();
  delay10us();
//  enableInterrupts(); 
  fram_off();
}

/**************************************************************************************************
 * @fn      FM_Read(unsigned long addr, unsigned char *pheader, unsigned int length)
 *
 * @brief   在指定地址开始读出length byte的数据
 *
 * @param   unsigned long addr, unsigned char *pheader, unsigned int length
 *
 * @return  void
 *
 **************************************************************************************************/
void FM_Read(unsigned long addr, unsigned char *pheader, unsigned int length)
{
  unsigned int i;
  fram_init();
  
  for(i = 0;i < length;i ++)
  {
    pheader[i] = FM_ReadByte(addr+i);
  }
  
  fram_off();	  
}
