/**
  ******************************************************************************
  * @file    COMP/COMP1_Halt/main.c
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
#include "timing_delay.h"

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup COMP1_Halt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void CLK_Config(void);
static void COMP_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
   /* CLK configuration -------------------------------------------*/
  CLK_Config(); 
  
  /* Init TIM2 to generate 1 ms time base update interrupt */
  TimingDelay_Init();

  /* Key button configuration */
  STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Initialize Leds mounted on STM8L152X-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

   /* COMP configuration -------------------------------------------*/
  COMP_Config(); 

  /* Enable Interrupts */
  enableInterrupts();

  /* Infinite loop */
  while (1)
  {
    /* Toggle LDE1..4 */
    STM_EVAL_LEDToggle(LED1);
    STM_EVAL_LEDToggle(LED2);
    STM_EVAL_LEDToggle(LED3);
    STM_EVAL_LEDToggle(LED4);

    /* Insert delay */
    Delay(50);
  }
}

/**
  * @brief  Configure peripheral clock 
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
  /* Enable COMP clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_COMP, ENABLE);
}

/**
  * @brief  Configure Comparator peripheral 
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
  /* Connect internal reference voltage to COMP1 inverting input */
  COMP_VrefintToCOMP1Connect(ENABLE);
  /* close the analog switch number 14 */
  SYSCFG_RIAnalogSwitchConfig(RI_AnalogSwitch_14, ENABLE);
  /* close the analog switch number 1 */
  SYSCFG_RIAnalogSwitchConfig(RI_AnalogSwitch_1, ENABLE);
  /* close the I/O switch number 4 */
  SYSCFG_RIIOSwitchConfig(RI_IOSwitch_4, ENABLE);

  /* Enable COMP1 Interrupt */
  COMP_ITConfig(COMP_Selection_COMP1, ENABLE);
  /* Configure the event detection */
  COMP_EdgeConfig(COMP_Selection_COMP1, COMP_Edge_Rising);
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
