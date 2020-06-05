/*******************************************************************************
Copyright: 
File name: flash.c  
Description: flash操作
Author: 初学者cy
Version: 
Date: 
History:       
*******************************************************************************/
/*******************************************************************************
文件包含区
*******************************************************************************/
#include "flash.h"
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
 Description:   //读操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_Read(uint32_t address, uint8_t *buff, uint16_t length)
{
  ErrorStatus status;
  
  if(IS_FLASH_DATA_EEPROM_ADDRESS(address))     //EEPROM地址域
  {
    status = Flash_EepromMemoryRead(address, buff, length);
  }
  else if(IS_FLASH_PROGRAM_ADDRESS(address))    //FLASH地址域
  {
    status = Flash_ProgramMemoryRead(address, buff, length); 
  }
  
  return status;
}
/*******************************************************************************
 Function:      //
 Description:   //Program Memory 读操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_Write(uint32_t address, uint8_t *buff, uint16_t length)
{
  ErrorStatus status;
  
  if(IS_FLASH_DATA_EEPROM_ADDRESS(address))     //EEPROM地址域
  {
    status = Flash_EepromMemoryWrite(address, buff, length);
  }
  else if(IS_FLASH_PROGRAM_ADDRESS(address))   //FLASH地址域
  {
    status = Flash_ProgramMemoryWrite(address, buff, length); 
  }
  
  return status;
}
/*******************************************************************************
 Function:      //
 Description:   //Program Memory 读操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_ProgramMemoryRead(uint32_t address, uint8_t *buff, uint16_t length)
{
  uint16_t itemp = 0;

  do
  {FLASH_Unlock(FLASH_MemType_Program); }//开启FLASH编程
  while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET);
  
  while(itemp < length)
  {
    buff[itemp] = FLASH_ReadByte(address++); 
    itemp++;
  }
  FLASH_Lock(FLASH_MemType_Program);
  
  return SUCCESS;
}
/*******************************************************************************
 Function:      //
 Description:   //Program Memory 写操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_ProgramMemoryWrite(uint32_t address, uint8_t *buff, uint16_t length)
{
  unsigned short itemp = 0; 
  unsigned short timeout = 0;
  
 do
 {FLASH_Unlock(FLASH_MemType_Program); }//开启FLASH编程
 while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET); 
 
 while (itemp < length)
 {
   FLASH_ProgramByte(address, buff[itemp]);
   while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == RESET)  //等待编程完成
   {
    timeout++;
    if(timeout == 0xFFFF)
    {
      FLASH_Lock(FLASH_MemType_Program);
      return ERROR;
    }
   }
   itemp ++;
   address++;
 }
 FLASH_Lock(FLASH_MemType_Program);
 
 return SUCCESS;
}
/*******************************************************************************
 Function:      //
 Description:   //Eeprom Memory 读操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_EepromMemoryRead(uint32_t address, uint8_t *buff, uint16_t length)
{
  unsigned short itemp = 0; 

  do
  {FLASH_Unlock(FLASH_MemType_Data); }
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET);
  
  while(itemp < length)
  {
    buff[itemp] = FLASH_ReadByte(address++); 
    itemp++;
  }
  FLASH_Lock(FLASH_MemType_Data);
  
  return SUCCESS;
}
/*******************************************************************************
 Function:      //
 Description:   //Eeprom Memory 写操作
 Input:         //
 Output:        //
 Return:	//
 Others:        //
*******************************************************************************/
ErrorStatus Flash_EepromMemoryWrite(uint32_t address, uint8_t *buff, uint16_t length)
{
  unsigned short itemp = 0; 
  unsigned short timeout = 0;

 do
 {FLASH_Unlock(FLASH_MemType_Data); }//开启FLASH编程
 while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET); 
 
 
 while (itemp < length)
 {
   FLASH_ProgramByte(address, buff[itemp]);
   while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == RESET)  //等待编程完成
   {
    timeout++;
    if(timeout == 0xFFFF)
    {
      FLASH_Lock(FLASH_MemType_Data);
      return ERROR;
    }
   }
   itemp ++;
   address++;
 }
 FLASH_Lock(FLASH_MemType_Data);
 
 return SUCCESS;
}
/*************************************END**************************************/
