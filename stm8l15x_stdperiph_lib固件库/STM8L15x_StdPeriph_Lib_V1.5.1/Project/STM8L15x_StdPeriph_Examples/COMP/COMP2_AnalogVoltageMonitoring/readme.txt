/** @page COMP2_AnalogVoltageMonitoring  Use ADC1 and COMP2 to monitor analog voltage.

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    COMP/COMP2_AnalogVoltageMonitoring/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the COMP Analog voltage monitoring Example.
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

  In some applications, it is recommended to power-on ADC1 only if it is required 
  since it can jeopardize battery life time if left powered-on continuously. 
  In this example, COMP2 is used to monitor the analog voltage while the MCU 
  is in halt mode and to wake-up the system if a predefined threshold is crossed.
  When the analog voltage crosses the threshold, the COMP2 is powered-off and
  ADC1 is powered-on to perform continuous conversion.

  MCU is switching between two modes: 
    - If analog voltage is above the internal reference voltage (VREFINT), 
      ADC1 is powered-on and continuous conversion is performed: the MCU 
      is in run mode and LD1 is ON.
    - If analog voltage is under VREFINT, ADC1 is powered-off and COMP2 is 
      powered-on, the MCU enters halt mode and LD2 is ON.

  COMP2 is configured as follow:
    - Inverting input is VREFINT: this is the selected threshold
    - Non Inverting input is connected to PD0
    - Edge detection configuration is rising edge


  @par Directory contents

  - COMP\COMP2_AnalogVoltageMonitoring\main.c           Main file containing the "main" function
  - COMP\COMP2_AnalogVoltageMonitoring\stm8l15x_conf.h  Library Configuration file
  - COMP\COMP2_AnalogVoltageMonitoring\stm8l15x_it.c    Interrupt routines source
  - COMP\COMP2_AnalogVoltageMonitoring\stm8l15x_it.h    Interrupt routines declaration


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
     - Connect external voltage to PD0

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - Connect external voltage to PD0
  
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
