/** @page TIM1_PWMOutput Use the TIM1 peripheral to generate three signals with different frequencies

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM1/TIM1_PWMOutput/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the TIM1 PWM Output Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

  @par Example description

  This example shows how to configure the TIM1 peripheral to generate three
  signals with three different frequencies.

  TIM1CLK = SYSCLK = 2 MHz
  TIM1 counter clock = TIM1CLK / Prescaler = 2MHz / 2 = 1 MHz

  The TIM1 CCR1 register value is equal to 32768: 
  CC1 update rate = TIM1 counter clock / CCR1Val = 30.51 Hz,
  so the TIM1 Channel 1 generates a periodic signal with a frequency equal to
  15.25 Hz.

  The TIM1 CCR2 register is equal to 16384:
  CC2 update rate = TIM1 counter clock / CCR2Val = 61.03 Hz
  so the TIM1 channel 2 generates a periodic signal with a frequency equal to 
  30.51 Hz.

  The TIM1 CCR3 register is equal to 8192:
  CC3 update rate = TIM1 counter clock / CCR3Val = 123.01 Hz
  so the TIM1 channel 3 generates a periodic signal with a frequency equal to 
  61.5 Hz.

  The TIM1 waveform can be visualized using an oscilloscope. 


  @par Directory contents

  - TIM1/TIM1_PWMOutput/main.c            Main file containing the "main" function
  - TIM1/TIM1_PWMOutput/stm8l15x_conf.h   Library Configuration file
  - TIM1/TIM1_PWMOutput/stm8l15x_it.c     Interrupt routines source 
  - TIM1/TIM1_PWMOutput/stm8l15x_it.h     Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and Medium-Density
     Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density 
    devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL and STM8L1526-EVAL Set-up
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - Connect TIM1 pins to an oscilloscope:
       - TIM1 Channel 1 pin (PD.2)  
       - TIM1 Channel 2 pin (PD.4)  
       - TIM1 Channel 3 pin (PD.5)  
  
  
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Note that LED5 is toggling with two different colors (red and green)  
  - Connect the TIM1 channels to an oscilloscope to view the signals
  
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
