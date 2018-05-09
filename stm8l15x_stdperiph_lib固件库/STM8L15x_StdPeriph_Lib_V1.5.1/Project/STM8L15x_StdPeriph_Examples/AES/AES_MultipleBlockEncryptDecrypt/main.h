/**
  ******************************************************************************
  * @file    AES/AES_MultipleBlockEncryptDecrypt/main.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Main program body
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
#ifndef __MAIN_H
#define __MAIN_H

#include "stm8l15x.h"
#include "stm8_eval.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AES_DINR_ADDRESS            (uint16_t)0x53D2
#define AES_DOUTR_ADDRESS           (uint16_t)0x53D3

/* Private macro -------------------------------------------------------------*/
#define countof(a)        (sizeof(a) / sizeof(*(a)))
#define PLAINTEXT_SIZE    (uint8_t)(countof(PlainText)-1)

/* Private variables ---------------------------------------------------------*/
/* Data to be encrypted: data length must be multiple of 16 bytes and lower than 112 bytes */
NEAR uint8_t PlainText[] = "Four 8-bit product lines combine architecture with ST’s EnergyLite™ technology to do more work with less energy.";
NEAR uint8_t  CypherText[PLAINTEXT_SIZE + 1] = {0};
NEAR uint8_t  ComputedPlainText[PLAINTEXT_SIZE + 1] = {0};
NEAR uint8_t  SrcBuffer[PLAINTEXT_SIZE * 2 + 2] = {0};
/* encryption key used to encrypt PlainText */
uint8_t EncryptionKey[16] = "ultra low-power";

/* Private function prototypes -----------------------------------------------*/
ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
