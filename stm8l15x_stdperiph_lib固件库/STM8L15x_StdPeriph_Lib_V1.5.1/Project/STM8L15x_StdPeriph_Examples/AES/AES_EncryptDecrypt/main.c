/**
  ******************************************************************************
  * @file    AES/AES_EncryptDecrypt/main.c
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

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8_eval.h"

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup AES_EncryptDecrypt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Original data to be encrypted */
uint8_t PlainText[16] = "STM32L and STM8L";

/* encryption key used to encrypt PlainText */
uint8_t EncryptionKey[16] = "ultra-low power.";

uint8_t  CypherText[16] = {0};
uint8_t  ComputedPlainText[16] = {0};

/* Private function prototypes -----------------------------------------------*/
ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  uint8_t arrayindex = 0;
  ErrorStatus cryptostatus = ERROR;

  /* Enable AES clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_AES, ENABLE);

  /* Initialize LEDs mounted on STM8L1528-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED3);

  /* Select the encryption mode */
  AES_OperationModeConfig(AES_Operation_Encryp);

  /* Enable the AES peripheral */
  AES_Cmd(ENABLE);

  /* write 32 times in the DINR register with encryption key and plain text */
  while (arrayindex < 16)
  {
    /* writing MSB first */
    AES_WriteSubKey(EncryptionKey[arrayindex]);
    AES_WriteSubData(PlainText[arrayindex]);
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Wait for CCF flag to be set */
  while (AES_GetFlagStatus(AES_FLAG_CCF) == RESET)
  {}

  /* Clear CCF flag */
  AES_ClearFlag(AES_FLAG_CCF);

  /* Init arrayindex */
  arrayindex = 0;

  /* read 16 times the DOUTR register to get the cipher text */
  while (arrayindex < 16)
  {
    /* Reading MSB first */
    CypherText[arrayindex] = AES_ReadSubData();
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Disable the AES peripheral to change the operation mode */
  AES_Cmd(DISABLE);

  /* Select the key derivation and decryption mode */
  AES_OperationModeConfig(AES_Operation_KeyDerivAndDecryp);

  /* Re-enable the AES peripheral */
  AES_Cmd(ENABLE);

  /* Init arrayindex */
  arrayindex = 0;

  /* write 32 times in the DINR register with encryption key and cypher text */
  while (arrayindex < 16)
  {
    /* writing MSB first */
    AES_WriteSubKey(EncryptionKey[arrayindex]);
    AES_WriteSubData(CypherText[arrayindex]);
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Wait for CCF flag to be set */
  while (AES_GetFlagStatus(AES_FLAG_CCF) == RESET)
  {}

  /* Clear CCF flag */
  AES_ClearFlag(AES_FLAG_CCF);

  /* Init arrayindex */
  arrayindex = 0;

  /* read 16 times the DOUTR register to get the computed plain text */
  while (arrayindex < 16)
  {
    /* Reading MSB first */
    ComputedPlainText[arrayindex] = AES_ReadSubData();
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Check if decrypted cypher text match the original plain text */
  cryptostatus = Buffercmp(PlainText, ComputedPlainText, 16);

  if (cryptostatus == SUCCESS)
  {
    /* Turn on LD1 */
    STM_EVAL_LEDOn(LED1);
  }
  else
  {
    /* Turn on LD3 */
    STM_EVAL_LEDOn(LED3);
  }
  /* Infinite loop */
  while (1)
  {}
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval
 * - SUCCESS: pBuffer1 identical to pBuffer2
 * - ERROR: pBuffer1 differs from pBuffer2
  */
ErrorStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return ERROR;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return SUCCESS;
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/