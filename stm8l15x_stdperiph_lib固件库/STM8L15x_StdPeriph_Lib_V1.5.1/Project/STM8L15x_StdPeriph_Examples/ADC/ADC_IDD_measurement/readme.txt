/** @page ADC_IDD_Measurement Use ADC to measure live IDD current in Run mode

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    ADC/ADC_IDD_Measurement/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the ADC IDD measurement Example.
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

  This example provides a short description of how to use the ADC peripheral
  to measure IDD in Run and Halt modes by using the IDD measurement circuit 
  available on the STM8L152x-EVAL board.
  When running the example, the IDD measurement menu is displayed.

  To navigate the IDD measurement menu, perform the following actions:
      - RIGHT: Navigates to the next submenu items on the right.
      - LEFT: Navigates to the next submenu items on the left.
      - SEL: Enters submenu.
      - UP: Exits from a submenu.
  Once an IDD Measurement submenu is selected by pressing the Joystick SEL
  push-button the IDD value is continuously displayed on LCD, until the joystick 
  UP push-button is pressed.
  If the joystick UP push-button has been pressed, the MCU exits the IDD Mode 
  submenu and goes back to the IDD measurement menu.

  The STM8L1528-EVAL board is provided with an IDD measurement circuit, more
  details can be provided in STM8L1528-EVAL user manual.
  The STM8L1526-EVAL board is provided with an IDD measurement circuit, more
  details can be provided in STM8L1526-EVAL user manual.

  @par Directory contents

  - ADC/ADC_IDD_Measurement/main.c                   Main file
  - ADC/ADC_IDD_Measurement/stm8l15x_conf.h          Library Configuration file
  - ADC/ADC_IDD_Measurement/stm8l15x_it.c            Interrupt routines source
  - ADC/ADC_IDD_Measurement/stm8l15x_it.h            Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus, Medium-Density
    and Low-Density Devices..
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density and
    Low-Density devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL Set-up
     - LCD display
     - Before Running the example make sure that:
         - Jumper JP4 is in IDD position (1-2  .
         - Jumpers JP11 and JP12 are in IDD position.
     - Make sure that the LCD glass daughter board is mounted in IO position.
     For more details please refer to the evaluation board user manual.
    
  - STM8L1526-EVAL Set-up
     - LCD display
     - Before Running the example make sure that jumper JP11 is in IDD position (1-2  .
     - Make sure that the LCD glass daughter board is mounted in IO position.
     For more details please refer to the evaluation board user manual.
  



  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Add the required file:
    - timing_delay.c      (under Utilities/Misc)
  - Rebuild all files and load your image into target memory
  - Run the example
  - The IDD Measurement menu is displayed.

 
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
