/** @page TIM4_TimeBase  Use the TIM4 peripheral to generate 1 ms time base using TIM4 update interrupt

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM4/TIM4_TimeBase/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the TIM4 Time Base Example.
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

  This example provides a short description of how to use the TIM4 peripheral 
  to generate time base equal to 1 ms. In this example a "Delay" function is 
  implemented based on the TIM4 time base.
  The four LEDs LD1..LD4 toggle with a timing defined by the Delay function.

  The TIM4CLK frequency is 16MHz, the Prescaler is 128 so the TIM4 counter 
  clock is 125 KHz.
  The TIM4 is running at TIM4 frequency = TIM4 counter clock / (TIM4_PERIOD + 1)   
                                        = 125000 / 125 = 1 KHz.
  So the TIM4 generates an Update Interrupt each 1 / 1000 = 1 ms.


  @par Directory contents

  - TIM4/TIM4_TimeBase/main.c             Main file containing the "main" function
  - TIM4/TIM4_TimeBase/stm8l15x_conf.h    Library Configuration file
  - TIM4/TIM4_TimeBase/stm8l15x_it.c      Interrupt routines source
  - TIM4/TIM4_TimeBase/stm8l15x_it.h      Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density, Medium-Density Plus, Medium-Density
    and Low-Density Devices.

  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density and
    Low-Density devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1526-EVAL and STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
     - Four leds LD1..LD4


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
