/**
  ******************************************************************************
  * @file    stm8_eval_i2c_tsensor.h
  * @author  MCD Application Team
  * @version V2.1.2
  * @date    19-May-2011
  * @brief   This file contains all the functions prototypes for the 
  *          stm8_eval_i2c_tsensor firmware driver.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8_EVAL_I2C_TSENSOR_H
#define __STM8_EVAL_I2C_TSENSOR_H

/* Includes ------------------------------------------------------------------*/
#include "stm8_eval.h"


/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM8_EVAL
  * @{
  */ 

/** @addtogroup Common
  * @{
  */
  
/** @addtogroup STM8_EVAL_I2C_TSENSOR
  * @{
  */  

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
  * @brief  Block Size
  */
#define LM75_REG_TEMP        0x00  /* Temperature Register of LM75 */
#define LM75_REG_CONF        0x01  /* Configuration Register of LM75 */
#define LM75_REG_THYS        0x02  /* Temperature Register of LM75 */
#define LM75_REG_TOS         0x03  /* Over-temp Shutdown threshold Register of LM75 */
#define I2C_TIMEOUT         (uint32_t)0x3FFFF /*!< I2C Time out */
#define LM75_ADDR           0x90   /*!< LM75 address */
#define LM75_I2C_SPEED      100000 /*!< I2C Speed */

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


void LM75_DeInit(void);
void LM75_Init(void);
ErrorStatus LM75_GetStatus(void);
uint16_t LM75_ReadTemp(void);
uint16_t LM75_ReadReg(uint8_t RegName);
void LM75_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t LM75_ReadConfReg(void);
void LM75_WriteConfReg(uint8_t RegValue);
void LM75_ShutDown(FunctionalState NewState);  

#endif /* __STM8_EVAL_I2C_TSENSOR_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
