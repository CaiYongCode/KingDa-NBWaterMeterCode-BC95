/**
  ******************************************************************************
  * @file    RTC/RTC_ChronoSubSecond/main.h
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
#define MAXSAVETIME ((uint8_t) 9)
#define EnterSafeCode() disableInterrupts()
#define ExitSafeCode()  enableInterrupts()
#define ASCII_NUM_0         ((uint8_t)48)
#define SHOW_POINT          ((uint8_t)2)
#define DEFAULTDISPLAY      "Chrono Running "
#define CHRONOATZERO        "  00:00:00:000 "
#define RESETDISPLAY        "  SEL to Run   "
#define PAUSELED            LED1  
#define RUNLED              LED2
#define RECORDLED           LED3

/* Exported functions ------------------------------------------------------- */


void Calendar_Init(void);
void Tamper_Init(void);
void EvalBoard_Init(void);

void Time_Show(uint8_t Line);
void Time_SaveCurrentTime(uint8_t SavedTimeId);
void Time_Pause(void);
void Time_Record(void);
void Time_ResetMenu(void);
void Time_Reset(void);

void SavedTime_Show(uint8_t Line, uint8_t SavedTimeId);
void SavedTime_Parsing(void);
void SavedTime_Erase(void);

void Restore_LastDisplay(void);
JOYState_TypeDef ReadJoystick(void);
void Delay(__IO uint32_t nCount);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
