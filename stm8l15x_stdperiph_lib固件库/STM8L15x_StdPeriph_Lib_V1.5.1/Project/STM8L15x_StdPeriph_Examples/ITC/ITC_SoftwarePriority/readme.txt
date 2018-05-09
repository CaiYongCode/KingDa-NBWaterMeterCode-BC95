/** @page ITC_SoftwarePriority Changing software priority of two external interrupt lines

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    ITC/ITC_SoftwarePriority/readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the ITC Software priority Example.
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

  This example shows how to change the software priority of two external 
  interrupt lines to allow nested interrupt management.
  In this example, we set the Key IRQ software priority level to 1 and set the 
  joystick Down IRQ software priority level to 2.
  Thus joystick Down button IRQ software priority is higher than Key one and 
  pressing joystick Down button interrupts the execution of the Key Interrupt 
  Sub-Routine.
  If the Key IRQ and joystick Down IRQ had the same software priority, neither
  Key IRQ could interrupt joystick Down IRQ nor joystick Down could interrupt 
  Key IRQ.

  In STM8L1528-EVAL, Key button is connected to EXTI6 and joystick Down button
  is connected to EXTI1.
  In STM8L1526-EVAL, Key button is connected to EXTI1 and joystick Down button
  is connected to EXTI4.

  @par Directory contents

  - ITC/ITC_SoftwarePriority/main.c            Main file containing the "main" function
  - ITC/ITC_SoftwarePriority/stm8l15x_conf.h   Library Configuration file
  - ITC/ITC_SoftwarePriority/stm8l15x_it.c     Interrupt routines source
  - ITC/ITC_SoftwarePriority/stm8l15x_it.h     Interrupt routines declaration


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
     - Two leds LD2 and LD3
     - Key and Joystick Down buttons

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - Two leds LD2 and LD3
     - Key and Joystick Down buttons
     - Make sure that the JP7 jumper is in Key position.
  
  
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Leds LD2 and LD3 are ON
  - When the Joystick Down button is pressed, the LD2 toggles and LD3 is OFF
  - When the Key button is pressed, the LD3 toggles and LD2 is OFF
  - Play with the Key button and the Joystick Down in order to see which one
    has the highest priority:
    - press and maintain the Key button -> LD3 toggles, LD2 is OFF
    - Continue pressing the Key button and press the joystick Down button 
        -> LD2 toggles instead, LD3 is OFF (Joystick IRQ is higher priority  
     If you do the reverse, you can see that the joystick button ISR is not 
     interrupted when the Key button is pressed.

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
