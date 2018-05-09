/** @page I2C_TSENSOR Communication between I2C and STLM75 Temperature sensor

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    I2C/I2C_TSENSOR/readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the I2C Temperature sensor Example.
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

  This example provides a description of how to use the I2C to communicate with 
  an STLM75 (or a compatible device   I2C temperature sensor that is mounted on
  the STM8L1528-EVAL and STM8L1526-EVAL boards and used to get instantaneous
  external temperature.
 
  The measured temperature is displayed on LCD dot matrix and the MCU enter in 
  active halt mode, after each 10s the RTC generates an interrupt to wake up the 
  MCU from halt mode. 


  @par Directory contents

  - I2C/I2C_TSENSOR/main.c            Main file containing the "main" function
  - I2C/I2C_TSENSOR/stm8l15x_conf.h   Library Configuration file
  - I2C/I2C_TSENSOR/stm8l15x_it.c     Interrupt routines source
  - I2C/I2C_TSENSOR/stm8l15x_it.h     Interrupt routines declaration
  - I2C/I2C_TSENSOR/interrupt.s       (to use only with IAR  


  @par Hardware and software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus, Medium-Density
    and Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density and
    Low-Density devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL Set-up 
    - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
    - STLM75 temperature sensor is already mounted on STM8L1528-EVAL.

  - STM8L1526-EVAL Set-up
    - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
    - STLM75 temperature sensor is already mounted on STM8L1526-EVAL.
    - Make sure that Jumper JP7 is set in position 1-2 (I2C position  .

  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Add the required file:
    - stm8_eval_i2c_tsensor.c   (under Utilities/STM8_EVAL/Common)
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
