/**
  ******************************************************************************
  * @file    RTC/RTC_Calendar/main.h
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
/* Exported functions ------------------------------------------------------- */
void Calendar_Init(void);
void Time_Regulate(void);
void Time_Show(uint8_t Line);
void Date_Regulate(void);
void Date_Show(void);
void Alarm_Regulate(void);
uint16_t DayOfWeek(uint16_t nYear, uint16_t nMonth, uint16_t nDay);
uint16_t CountOfFeb29(uint16_t nYear);
bool IsLeapYear(uint16_t nYear);
uint8_t ReadDigit(uint8_t* ptr, uint8_t ColBegin, uint8_t ValueMax, uint8_t ValueMin) ;
void SetCursorPosition(uint8_t* ptr, uint8_t Line, uint8_t Offset);
void ToggleCursorPosition(uint8_t* ptr, uint8_t Line, uint8_t Offset);
JOYState_TypeDef ReadJoystick(void);
void LSE_StabTime(void);
void Delay(__IO uint32_t nCount);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
