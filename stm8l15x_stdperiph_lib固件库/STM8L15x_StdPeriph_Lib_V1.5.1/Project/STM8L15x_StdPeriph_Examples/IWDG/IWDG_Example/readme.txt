/** @page IWDG_Example IWDG counter reload and simulation of IWDG reset

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    IWDG/IWDG_Example/readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the IWDG example.
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

 This example shows how to update at regular period the IWDG reload counter and 
 how to simulate a software fault generating an MCU IWDG reset on expiry of a 
 programmed time period.

 The IWDG timeout is set to 214 ms (the timeout may varies due to LSI frequency 
 dispersion).

 First, the TIM2 timer is configured to measure the LSI frequency as the 
 LSI is internally connected to it, in order to adjust the IWDG clock.
 The IWDG reload counter is configured to obtain 214ms according to the 
 measured LSI frequency.

 The IWDG reload counter is refreshed in the main program infinite loop to prevent
 an IWDG reset.

 The Key button is used to generate an interrupt that will simulate a software 
 failure by pressing it.
 In the ISR, a trap instruction is executed generating a TRAP interrupt containing
 an infinite loop and preventing to return to main program (the IWDG reload counter 
 is no more refreshed).
 As a result, when the IWDG counter reaches 00h, the IWDG reset occurs.
 If the IWDG reset is generated, after the system resumes from reset, LED1 turns on.

 If the Key button is not pressed, the IWDG counter is indefinitely refreshed
 in the main program infinite loop, and there is no IWDG reset.
  

  @par Directory contents

  - IWDG/IWDG_Example/main.c             Main file containing the "main" function
  - IWDG/IWDG_Example/stm8l15x_conf.h    Library Configuration file
  - IWDG/IWDG_Example/stm8l15x_it.c      Interrupt routines source 
  - IWDG/IWDG_Example/stm8l15x_it.h      Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus, Medium-Density
    and Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density and
    Low-Density devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - leds LD1, LD2 and Key push button are used.

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - leds LD1, LD2 and Key push button are used.
     - Make sure that JP7 is in key position.


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
