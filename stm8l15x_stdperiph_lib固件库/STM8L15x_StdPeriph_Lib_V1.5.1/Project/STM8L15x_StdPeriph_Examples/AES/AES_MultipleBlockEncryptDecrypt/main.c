/**
  ******************************************************************************
  * @file    AES/AES_MultipleBlockEncryptDecrypt/main.c
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
#include "main.h"

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup AES_MultipleBlockEncryptDecrypt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
  uint8_t index1 = 0, index2 = 0;
  ErrorStatus cryptostatus = ERROR;

  /* Initialize LEDs mounted on STM8L1528-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED3);


  /****************************************************************************/
  /*                           Encryption phase                               */
  /****************************************************************************/

  /* Prepare the buffer to be transferred by DMA: Alternating key and plain text */
  while (arrayindex < PLAINTEXT_SIZE * 2)
  {
    SrcBuffer[arrayindex] = EncryptionKey[index1];
    arrayindex++;
    SrcBuffer[arrayindex] = PlainText[index2];
    arrayindex++;
    index1++;
    index2++;
    if (index1 == 16) index1 = 0;
  }

  /* DMA configuration to transfer data to/from AES --------------------------*/
  /* Enable DMA1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
  /* DMA DeInit */
  DMA_GlobalDeInit();
  DMA_DeInit(DMA1_Channel0);
  DMA_DeInit(DMA1_Channel3);

  /* DMA1 channel 0 configuration
    Input phase: data transfer from memory "SrcBuffer" to AES_DINR register */
  DMA_Init(DMA1_Channel0, (uint16_t)SrcBuffer, AES_DINR_ADDRESS, PLAINTEXT_SIZE * 2,
           DMA_DIR_MemoryToPeripheral, DMA_Mode_Normal, DMA_MemoryIncMode_Inc,
           DMA_Priority_VeryHigh, DMA_MemoryDataSize_Byte);

  /* DMA1 channel 3 configuration
   Output phase: data transfer from AES_DOUTR register to memory "CypherText" */
  DMA_Init(DMA1_Channel3, (uint16_t)CypherText, AES_DOUTR_ADDRESS, PLAINTEXT_SIZE,
           DMA_DIR_PeripheralToMemory, DMA_Mode_Normal, DMA_MemoryIncMode_Inc,
           DMA_Priority_VeryHigh, DMA_MemoryDataSize_Byte);

  /* DMA1 Channel 0 and channel 3 enable */
  DMA_Cmd(DMA1_Channel0, ENABLE);
  DMA_Cmd(DMA1_Channel3, ENABLE);
  /* DMA1 global enable */
  DMA_GlobalCmd(ENABLE);

  /* AES configuration to encrypt data using DMA transfer --------------------*/
  /* Enable AES clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_AES, ENABLE);
  /* Select the encryption mode */
  AES_OperationModeConfig(AES_Operation_Encryp);
  /* Enable using DMA for data transfer */
  AES_DMAConfig(AES_DMATransfer_InOut, ENABLE);
  /* Enable the AES peripheral: the AES initiates the DMA request */
  AES_Cmd(ENABLE);

  /* Wait for transfer from AES_DOUTR to memory to be completed */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);

  /****************************************************************************/
  /*                             Decryption phase                             */
  /****************************************************************************/

  /* Prepare the buffer to be transferred by DMA: Alternating key and cypher text */
  arrayindex = 0;
  index1 = 0;
  index2 = 0;
  while (arrayindex < PLAINTEXT_SIZE * 2)
  {
    SrcBuffer[arrayindex] = EncryptionKey[index1];
    arrayindex++;
    SrcBuffer[arrayindex] = CypherText[index2];
    arrayindex++;
    index1++;
    index2++;
    if (index1 == 16) index1 = 0;
  }

  /* Disable the AES peripheral to change AES operation mode */
  AES_Cmd(DISABLE);
  /*  DeInit DMA1 channel 3 */
  DMA_DeInit(DMA1_Channel3);
  /* DMA1 global disable */
  DMA_GlobalCmd(DISABLE);

  /* DMA1 channel 0 is already configured in Encryption phase
    Input phase: data transfer from memory "SrcBuffer" to AES_DINR register */
  /* Reconfigure channel 0 counter to start a new transfer */
	DMA_Cmd(DMA1_Channel0, DISABLE);
  DMA_SetCurrDataCounter(DMA1_Channel0, PLAINTEXT_SIZE * 2);

  /* DMA1 channel 3 configuration
    Output phase: data transfer from AES_DOUTR register to memory "ComputedPlainText" */
  DMA_Init(DMA1_Channel3, (uint16_t)ComputedPlainText, AES_DOUTR_ADDRESS, PLAINTEXT_SIZE,
           DMA_DIR_PeripheralToMemory, DMA_Mode_Normal, DMA_MemoryIncMode_Inc,
           DMA_Priority_VeryHigh, DMA_MemoryDataSize_Byte);

  /* DMA1 Channel 0 and Channel 3 enable */
  DMA_Cmd(DMA1_Channel3, ENABLE);
  DMA_Cmd(DMA1_Channel0, ENABLE);
  /* DMA1 global enable */
  DMA_GlobalCmd(ENABLE);

  /********** AES configuration to decrypt data using DMA transfer  ***********/
  /* Select the key derivation and decryption mode */
  AES_OperationModeConfig(AES_Operation_KeyDerivAndDecryp);
  /* Enable the AES peripheral */
  AES_Cmd(ENABLE);

  /* wait for transfer from AES_DOUTR register to memory to be completed */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);

  /****************************************************************************/
  /*                          Checking buffers                                */
  /****************************************************************************/

  /* Check if decrypted cypher text is equal to original plain text */
  cryptostatus = Buffercmp(PlainText, ComputedPlainText, PLAINTEXT_SIZE);

  if (cryptostatus == SUCCESS)
  {
    /* Turn on green led LD1 */
    STM_EVAL_LEDOn(LED1);
  }
  else
  {
    /* Turn on red led LD3 */
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
