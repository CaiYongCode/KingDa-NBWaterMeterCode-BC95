/** @page COMP_AnalogWatchdog  Use COMP1 and COMP2 in window mode to make an analog watchdog.

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    COMP/COMP_AnalogWatchdog/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the COMP Analog Watchdog Example.
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

  This example shows how to make an analog watchdog using the COMPs peripherals
  in window mode:
   - The upper threshold is set to VREFINT = 1.22V
   - The lower threshold is set to VREFINT / 4 = 1.22V = 0.305V
   - PD1 is configured as COMP1 and COMP2 non inverting input (Connect external voltage to PD1)  

  If the input voltage is above the higher threshold, LD3 and LD1 are turned On.
  If the input voltage is under the lower threshold, LD2 and LD4 are turned On.
  If the input voltage is within the thresholds, the LD1, LD2, LD3 and LD4 are Off 
  and MCU is in halt mode. MCU wakes-up from halt if input voltage crosses the 
  high threshold or the low threshold.

  @par Directory contents

  - COMP\COMP_AnalogWatchdog\main.c            Main file containing the "main" function
  - COMP\COMP_AnalogWatchdog\stm8l15x_conf.h   Library Configuration file
  - COMP\COMP_AnalogWatchdog\stm8l15x_it.c     Interrupt routines source
  - COMP\COMP_AnalogWatchdog\stm8l15x_it.h     Interrupt routines declaration


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
     - Connect external voltage to PD1

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - Connect external voltage to PD1
     
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
