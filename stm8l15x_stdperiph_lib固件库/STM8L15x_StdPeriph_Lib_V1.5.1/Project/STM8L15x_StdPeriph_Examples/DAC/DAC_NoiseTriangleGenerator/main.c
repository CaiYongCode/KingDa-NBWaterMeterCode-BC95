/**
  ******************************************************************************
  * @file    DAC/DAC_NoiseTriangleGenerator/main.c
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

/** @addtogroup DAC_NoiseTriangleGenerator
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DAC_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* DAC configuration -------------------------------------------*/
  DAC_Config();
  
  /* Init Eval Board used Buttons*/
  STM_EVAL_PBInit(BUTTON_RIGHT, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_LEFT, BUTTON_MODE_EXTI);

  /* Enable Interrupts */
  enableInterrupts();

  /* Infinite loop */
  while(1)
  {
    /* Enable Software Trigger for Both DAC channels*/
    DAC_DualSoftwareTriggerCmd(ENABLE);
  }
}

/**
  * @brief  Configure DAC peripheral
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{
  /* Enable the Clock of DAC */
  CLK_PeripheralClockConfig(CLK_Peripheral_DAC, ENABLE);
  
  DAC_DeInit();

  /* Init DAC channel 1 and DAC channel 2 outputs */
  DAC_Init(DAC_Channel_1, DAC_Trigger_Software, DAC_OutputBuffer_Enable);
  DAC_Init(DAC_Channel_2, DAC_Trigger_Software, DAC_OutputBuffer_Enable);

  /* DAC channel 1 Triangle wave generator enabled */
  DAC_WaveGenerationCmd(DAC_Channel_1, DAC_Wave_Triangle, ENABLE);

  /* DAC channel 1 Noise  wave generator enabled */
  DAC_WaveGenerationCmd(DAC_Channel_2, DAC_Wave_Noise, ENABLE);

  /* Select DAC channel 1 Triangle wave generator amplitude  */
  DAC_SetTriangleWaveAmplitude(DAC_Channel_1, DAC_TriangleAmplitude_4095);

  /* Select DAC channel 2 Mask  */
  DAC_SetNoiseWaveLFSR(DAC_Channel_2, DAC_LFSRUnmask_Bits11_0);

  /* Enable DAC channel 1 and 2 outputs  */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  DAC_Cmd(DAC_Channel_2, ENABLE);

  DAC_SetDualChannelData(DAC_Align_12b_R, 0, 0);
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
