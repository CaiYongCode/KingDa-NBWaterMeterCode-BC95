/**
  ******************************************************************************
  * @file    EXTI/EXTI_IOControl/main.c
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

/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/** @addtogroup EXTI_IOControl
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define NO_BUTTON 0x06

/* Private variables ---------------------------------------------------------*/
__IO uint8_t PressedButton = 0x07;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

  /* Initialize LEDs mounted on STM8L152X-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);

  /* Initialize push-buttons mounted on STM8L152X-EVAL board */
  STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_RIGHT, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_LEFT, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_UP, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_DOWN, BUTTON_MODE_EXTI);
  STM_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);

  /* Initialize LCD*/
  STM8_EVAL_LCD_Init();

  /* Clear LCD*/
  LCD_Clear();

  /* Enable general interrupts for push button reading */
  enableInterrupts();

  LCD_SetCursorPos(LCD_LINE1, 0);
  LCD_Print(" STM8L152X-EVAL ");

  LCD_SetCursorPos(LCD_LINE2, 0);
  LCD_Print(" IO   Control   ");

  while (1)
  {
    switch (PressedButton)
    {
      case BUTTON_KEY:
      {
        /* LD1..LD4 are off */
        STM_EVAL_LEDOff(LED1);
        STM_EVAL_LEDOff(LED2);
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        /* LD5 is green */
        STM_EVAL_LEDOn(LED5);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   KEY  ");
        PressedButton = NO_BUTTON;
        break;
      }
      case BUTTON_RIGHT:
      {
        /* LD2, LD3 and LD4 are off */
        STM_EVAL_LEDOff(LED2);
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        /* LD5 is red */
        STM_EVAL_LEDOff(LED5);
        /* LD1 is On  */
        STM_EVAL_LEDOn(LED1);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   RIGHT");
        PressedButton = NO_BUTTON;
        break;
      }
      case BUTTON_LEFT:
      {
        /* LD1, LD3 and LD4 are off */
        STM_EVAL_LEDOff(LED1);
        STM_EVAL_LEDOff(LED3);
        STM_EVAL_LEDOff(LED4);
        /* LD5 is red */
        STM_EVAL_LEDOff(LED5);
        /* LD2 is On */
        STM_EVAL_LEDOn(LED2);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   LEFT ");
        PressedButton = NO_BUTTON;
        break;
      }
      case BUTTON_UP:
      {
        /* LD1, LD2 and LD4 are off */
        STM_EVAL_LEDOff(LED1);
        STM_EVAL_LEDOff(LED2);
        STM_EVAL_LEDOff(LED4);
        /* LD5 is red */
        STM_EVAL_LEDOff(LED5);
        /* LD3 is On */
        STM_EVAL_LEDOn(LED3);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   UP   ");
        PressedButton = NO_BUTTON;
        break;
      }
      case BUTTON_DOWN:
      {
        /* LD1, LD2 and LD3 are off */
        STM_EVAL_LEDOff(LED1);
        STM_EVAL_LEDOff(LED2);
        STM_EVAL_LEDOff(LED3);
        /* LD5 is red */
        STM_EVAL_LEDOff(LED5);
        /* LD4 is On */
        STM_EVAL_LEDOn(LED4);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   DOWN ");
        PressedButton = NO_BUTTON;
        break;
      }
      case BUTTON_SEL:
      {
        /* LD1..LD4 are on */
        STM_EVAL_LEDOn(LED1);
        STM_EVAL_LEDOn(LED2);
        STM_EVAL_LEDOn(LED3);
        STM_EVAL_LEDOn(LED4);
        /* LD5 is green */
        STM_EVAL_LEDOn(LED5);
        LCD_SetCursorPos(LCD_LINE2, 0);
        LCD_Print("Button:   SEL  ");
        PressedButton = NO_BUTTON;
        break;
      }
      default:
      {
        break;
      }
    }
  }
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

/**
  * @}
  */

/**
  * @}
  */

#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
