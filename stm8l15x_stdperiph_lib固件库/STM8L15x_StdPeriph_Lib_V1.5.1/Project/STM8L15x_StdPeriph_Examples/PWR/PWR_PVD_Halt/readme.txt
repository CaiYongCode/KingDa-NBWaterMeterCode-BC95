/** @page PWR_PVD_Halt Use PVD to monitor VDD power supply and put MCU in Halt mode when VDD < PVD level 

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    PWR/PWR_PVD_Halt/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the PWR_PVD_Halt Example.
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

  This example provides a short description of how to enter MCU in Halt mode and 
  exit through PVD interrupt. 

  For the purpose of this example the MCU VDD is connected to adjustable DC power
  supply (VDD ADJ on STM8L1526-EVAL and STM8L1528-EVAL) and the PVD level is set to 2.85V.

  Once the PVD is enabled, it starts monitoring VDD level:
   - When VDD level goes below 2.85V, the PVD interrupt is generated and in the
     corresponding ISR a message is displayed on the LCD then the MCU enters Halt mode.
   - When the VDD level goes above 2.85V, the PVD interrupt is generated which
     causes the MCU to exit from Halt mode.
     This behavior is repeated in an infinite loop.

  On STM8L1528-EVAL board, use the RV2 potentiometer to adjust VDD level.
  On STM8L1526-EVAL board, use the RV1 potentiometer to adjust VDD level.


  @par Directory contents

  - PWR/PWR_PVD_Halt/main.c                   Main file containing the "main" function
  - PWR/PWR_PVD_Halt/stm8l15x_conf.h          Library Configuration file
  - PWR/PWR_PVD_Halt/stm8l15x_it.c            Interrupt routines source
  - PWR/PWR_PVD_Halt/stm8l15x_it.h            Interrupt routines declaration


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
     - Use potentiometer RV2 to adjust VDD.
     - Make sure to set jumper JP14 in ADJ position (1-2) to connect the VDD
       to adjustable DC power supply
     - Dot matrix LCD

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - Use potentiometer RV1 to adjust VDD.
     - Make sure to set jumper JP1 in ADJ position (1-2) to connect the VDD
       to adjustable DC power supply
     - Dot matrix LCD

  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Add the required file:
    - timing_delay.c      (under Utilities\Misc)
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
