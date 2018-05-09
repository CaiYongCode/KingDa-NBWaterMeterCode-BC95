/** @page RTC_ChronoSubSecond Use RTC as a chronometer

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    RTC/RTC_ChronoSubSecond/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the RTC Chronomter Example.
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

  This example provides a short description of how to use the RTC peripheral’s
  calendar feature: sub seconds, seconds, minutes, hours to simulate a precise 
  chronometer with 9 record times possibilities, and Start/Pause/Resume actions.

  For this example an interactive human interface is developed using
  STM8L1528-EVAL’s LCD and Joystick to allow user to use Chronometer with real 
  time display.

  After startup, a default 00:00:00:000 chronometer counter is displayed on the 
  LCD, it corresponds to [Hours]:[minutes]:[seconds]:[milliseconds].
  User can manipulate the chronometer features using the Tamper, Key and 
  Joystick navigation buttons:
    - press Joystick SEL button to Start/Pause/Resume the chronometer counter
    - press Key button to store the current chrono Time and Rank, 9 records can 
      be performed.
    - press Joystick DOWN button to enter to the Recorded Times menu, where you 
      can navigate using the Joystick RIGHT/LEFT buttons.
    - press Joystick UP button to exit from the Recorded Times menu.
    - press Tamper button during 2sec to enter to the reset menu where you can 
      select using RIGHT/LEFT buttons to clear the counter and/or the recorded times.
      
    @note During Pause, Pressing on Tamper Button does not have any effect.

  @par Directory contents

  - RTC/RTC_ChronoSubSecond/main.c                   Main file
  - RTC/RTC_ChronoSubSecond/main.h                   Main file declaration
  - RTC/RTC_ChronoSubSecond/stm8l15x_conf.h          Library Configuration file
  - RTC/RTC_ChronoSubSecond/stm8l15x_it.c            Interrupt routines source
  - RTC/RTC_ChronoSubSecond/stm8l15x_it.h            Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    evaluation board and can be easily tailored to any other development board.
    
  
  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - Joystick, Tamper and Key buttons
     - LED1..4
     - Dot matrix LCD
     - External 32.768kHz LSE clock (X1)  
     - Make sure that SB9 (Solder Bridge) is in position 2-3.
            
      
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
