/** @page EXTI_IOControl Use GPIO and EXTI to detect interrupt on pushbuttons.

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    EXTI/EXTI_IOControl/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the EXTI IO Control Example.
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

  This example provides a short description of how to use the EXTI and GPIO 
  peripherals.
  When user presses a button, a LED will toggle and a message, indicating which
  button is pressed, is displayed on LCD.


  @par Directory contents

  - EXTI/EXTI_IOControl/main.c            Main file containing the "main" function
  - EXTI/EXTI_IOControl/stm8l15x_conf.h   Library Configuration file
  - EXTI/EXTI_IOControl/stm8l15x_it.c     Interrupt routines source
  - EXTI/EXTI_IOControl/stm8l15x_it.h     Interrupt routines declaration

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
     - Five leds LD1, LD2, LD3, LD4 and LD5 (bi-color led  
     - Key and Joystick buttons.
     - Dot matrix LCD
  
  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
     - Five leds LD1, LD2, LD3, LD4 and LD5 (bi-color led  
     - Key and Joystick buttons.
     - Dot matrix LCD
     - Make sure that the JP7 jumper is in key position.
    
    
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example  
   - press KEY button, the bi-color led LD5 is on (green)and leds LD1 .. LD4 off
   - press joystick right button, led LD1 is on, LD5 is red and all other leds 
     are off
   - press joystick left button, led LD2 is on, LD5 is red and all other leds 
     are off
   - press joystick up button, led LD3 is on, LD5 is red and all other leds 
     are off
   - press joystick down button, led LD4 is on, LD5 is red and all other leds 
     are off
   - presses joystick select button, the bi-color led LD5 is green and leds LD1 
     .. LD4 on

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
