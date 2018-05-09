/** @page TIM1_DMABurstMode Use DMA to transfer data in Burst mode from RAM buffer to TIM1

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM1/TIM1_DMABurstMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the TIM1 DMA burst mode Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim


  @par Firmware description

  This application provides a short description of how to use the DMA peripheral 
  to transfer data in Burst mode from RAM Buffer to TIM1.
  TIM1 channel 1 is configured in PWM output mode, DMA channel 2 is configured 
  to transfer data from RAM memory to TIM1 registers (PSCRH, PSCRL, ARRH, ARRL,
  RCR, CCR1H, CCR1L  .
  The goal of this example is to update simultaneously, on an external event
  provided from Key Button, the frequency and duty cycle TIM1 channel1.
  When starting the application, read the values of TIM1 registers: 
   PSCRH, PSCRL, ARRH, ARRL, RCR, CCR1H, CCR1L.

  After the 1st key press, and any odd key press, TIM1 registers values will be 
  as follow:
    - PSCRH = 0xFF
    - PSCRL = 0xEE
    - ARRH = 0xDD
    - ARRL = 0xCC
    - RCR = 0xBB
    - CCR1H = 0xAA
    - CCR1L = 0x99
  
  After the 2nd key press, and any even key press, TIM1 registers values will be 
  as follow: 
    - PSCRH = 0x77
    - PSCRL = 0x66
    - ARRH = 0x55
    - ARRL = 0x44
    - RCR = 0x33
    - CCR1H = 0x22
    - CCR1L = 0x11


  @par Directory contents

  - TIM1/TIM1_DMABurstMode/main.c             Main file containing the "main" function
  - TIM1/TIM1_DMABurstMode/stm8l15x_conf.h    Library Configuration file
  - TIM1/TIM1_DMABurstMode/stm8l15x_it.c      Interrupt routines source
  - TIM1/TIM1_DMABurstMode/stm8l15x_it.h      Interrupt routines declaration


 @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and Medium-Density
    Devices.

  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density 
    devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL Set-up
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - KEY push-buttons.
  
  - STM8L1526-EVAL Set-up
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - KEY push-buttons.
    - Make sure that jumper JP7 is in key position.
  
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example

 @note
  - Low-Density devices are STM8L15x microcontrollers where the Flash memory 
    density ranges between 4 and 8 Kbytes.
  - Medium-Density devices are STM8L15x microcontrollers where the 
    Flash memory density ranges between 16 and 32 Kbytes.
  - Medium density Plus devices are STM8L151R6, STM8L152R6 microcontrollers 
    where the Flash memory density is fixed and equal to 32 Kbytes and with 
    wider range of peripheral and features than the medium density devices. 
  - High-Density devices are STM8L15x microcontrollers where the 
    Flash memory density is 64 Kbytes and with the same peripheral set than 
    Medium Density Plus devices.
 * <h3><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h3>
 */