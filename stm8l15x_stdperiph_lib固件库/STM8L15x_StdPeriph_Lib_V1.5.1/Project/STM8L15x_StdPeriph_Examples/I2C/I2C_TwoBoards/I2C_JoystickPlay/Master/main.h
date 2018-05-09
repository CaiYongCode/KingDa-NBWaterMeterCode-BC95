/**
  ******************************************************************************
  * @file    I2C/I2C_TwoBoards/I2C_JoystickPlay/Master/main.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* definition of fast or default standard mode (bus speed up to 400 or 100 kHz) */
#define FAST_I2C_MODE

#ifdef FAST_I2C_MODE
#define I2C_SPEED 300000
#define TIM4_PERIOD 124
#else
#define I2C_SPEED 100000
#define TIM4_PERIOD 62
#endif


/* definition of 10-bit or default 7-bit slave address */
/* #define TEN_BITS_ADDRESS */

#ifdef TEN_BITS_ADDRESS
#define SLAVE_ADDRESS  0x330
#else
#define SLAVE_ADDRESS  0x30
#endif

#define BUFFERSIZE  255

/* Timer Delay */
#define TIM_DELAY 50

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;


#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/