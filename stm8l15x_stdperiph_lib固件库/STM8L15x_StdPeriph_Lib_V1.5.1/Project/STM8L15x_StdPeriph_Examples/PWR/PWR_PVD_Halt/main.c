/**
  ******************************************************************************
  * @file    PWR/PWR_PVD_Halt/main.c
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
#include "stm8_eval_lcd.h"
#include "timing_delay.h"

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/**
  * @addtogroup PWR_PVD_Halt
  * @{
  */

/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void PVD_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  /* System Clock is HSI/1 */
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

  /* Init TIM2 to generate 1 ms time base update interrupt */
  TimingDelay_Init();

   /* PVD configuration -------------------------------------------*/
  PVD_Config(); 

  /* Enable Interrupts */
  enableInterrupts();

  /* 1s delay to ensure proper LCD Init*/
  Delay(1000);

  /* Init the Eval board LCD */
  STM8_EVAL_LCD_Init();

  /* Clear LCD */
  LCD_Clear();

  LCD_SetCursorPos(LCD_LINE1, 0);
  LCD_Print("MCU : Run  Mode");

  LCD_SetCursorPos(LCD_LINE2, 0);
  LCD_Print(" Turn VDD ADJ  ");

  /* Disable TIM2 update interrupt */
  TIM2_ITConfig(TIM2_IT_Update, DISABLE);

  /* Infinite loop */
  while (1)
  {}
}

/**
  * @brief  Configure PVD
  * @param  None
  * @retval None
  */
static void PVD_Config(void)
{
  /* select PVD threshold*/
  PWR_PVDLevelConfig(PWR_PVDLevel_2V85);

  /*Enable PVD  : optional (PVD is by default enabled)*/
  PWR_PVDCmd(ENABLE);

  /*Enable PVD Interrupt*/
  PWR_PVDITConfig(ENABLE);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
    LCD_SetCursorPos(LCD_LINE1, 0);
    LCD_Print("      ERR       ");
    LCD_SetCursorPos(LCD_LINE2, 0);
    LCD_Print("     ASSERT     ");
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
