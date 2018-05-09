/** @page ADC_AnalogWatchdog Use ADC to indicate if the converted value exeeds the Analog watchdog thresholds or not.
  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    ADC/ADC_AnalogWatchdog/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the ADC Analog Watchdog example
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
  with Analog watchdog feature. 
  Three leds are used to indicate if the converted value exceeds the Analog
  watchdog thresholds or not.
  In the STM8L1528-EVAL board, ADC Channel 3 is connected to RV3 Adjuster. 
  Turning RV3 adjuster provides a voltage which can vary from 0 Volt to 3.3 Volt.
  In the STM8L1526-EVAL board, ADC Channel 3 is connected to RV2 Adjuster. 
  Turning RV2 adjuster provides a voltage which can vary from 0 Volt to 3.3 Volt.

  @par Directory contents

  - ADC/ADC_AnalogWatchdog/main.c                   Main file containing the "main" function
  - ADC/ADC_AnalogWatchdog/stm8l15x_conf.h          Library Configuration file
  - ADC/ADC_AnalogWatchdog/stm8l15x_it.c            Interrupt routines source
  - ADC/ADC_AnalogWatchdog/stm8l15x_it.h            Interrupt routines declaration


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
     - RV3 adjuster
     - Dot matrix LCD
     - LED1, LED3 and LED4
    
  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - RV2 adjuster
     - Dot matrix LCD
     - LED1, LED3 and LED4
        
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Turn RV Adjuster to provide a varing voltage (from 0 Volt to 3.3 Volt). The 
    ADC Channel 3 converted value is displayed on LCD.
  - LED1 is ON if the AWD Interrupt is occurring : the ADC Channel 3 voltage is not 
    between the high and low ADC Thresholds
  - LED4 is ON if the ADC Channel 3 voltage is higher than the high ADC Threshold voltage.
  - LED3 is ON if the ADC Channel 3 voltage is lower than the low ADC Threshold voltage.

  
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
