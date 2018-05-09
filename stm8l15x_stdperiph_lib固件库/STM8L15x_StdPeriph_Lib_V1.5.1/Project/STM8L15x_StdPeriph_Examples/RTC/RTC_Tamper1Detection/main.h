/**
  ******************************************************************************
  * @file    RTC/RTC_Tamper1Detection/main.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Header for main.c
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

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8_eval.h"
#include "stm8_eval_lcd.h"
#include "stdio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define EnterSafeCode() disableInterrupts()
#define ExitSafeCode()  enableInterrupts()
#define ASCII_NUM_0         ((uint8_t)48)
#define SHOW_POINT1          ((uint8_t)0)
#define SHOW_POINT2          ((uint8_t)9)
#define CHARPOS             ((uint8_t)13)

/* Exported functions ------------------------------------------------------- */
void Calendar_Init(void);
void Tamper_Init(void);
void EvalBoard_Init(void);
void Time_Show(uint8_t Line,uint8_t pos);
void Time_SaveCurrentTime(uint8_t SavedTimeId);
void Time_Record(void);
void Tamper_DelayShow(uint8_t DelayId );
void SavedTime_Show(uint8_t Line, uint8_t SavedTimeId);
void Delay(__IO uint32_t nCount);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
