/**
  ******************************************************************************
  * @file    AES/AES_KeyDerivation/main.c
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

/** @addtogroup AES_KeyDerivation
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t EncryptionKey[16] = "ultra-low power.";
uint8_t DecryptionKey[16];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  uint8_t arrayindex = 0;

  /* Enable AES clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_AES, ENABLE);

  /* Initialize LEDs mounted on STM8L1528-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED3);

  /* Select the key derivation mode */
  AES_OperationModeConfig(AES_Operation_KeyDeriv);

  /* Enable the AES peripheral */
  AES_Cmd(ENABLE);

  /* write 16 times in the DINR register with encryption key */
  while (arrayindex < 16)
  {
    /* writing MSB first */
    AES_WriteSubKey(EncryptionKey[arrayindex]);
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Wait for CCF flag to be set */
  while (AES_GetFlagStatus(AES_FLAG_CCF) == RESET);

  /* Clear CCF flag */
  AES_ClearFlag(AES_FLAG_CCF);

  /* Init arrayindex */
  arrayindex = 0;

  /* read 16 times the DOUTR register to get the decryption key */
  while (arrayindex < 16)
  {
    /* Reading MSB first */
    DecryptionKey[arrayindex] = AES_ReadSubData();
    /* Increment arrayindex */
    arrayindex++;
  }

  /* Check errors flags */
  if ((AES_GetFlagStatus(AES_FLAG_RDERR) != RESET) || (AES_GetFlagStatus(AES_FLAG_WRERR) != RESET))
  {
    /* Turn on LD3 */
    STM_EVAL_LEDOn(LED3);
  }
  else
  {
    /* Turn on LD1 */
    STM_EVAL_LEDOn(LED1);
  }

  /* Infinite loop */
  while (1)
  {}
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
