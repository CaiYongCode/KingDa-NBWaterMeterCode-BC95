/** @page I2C_DataExchange I2C1 Master and Slave data exchange   

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    I2C/I2C_TwoBoards/I2C_DataExchange/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the I2C Data Exchange Example.
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

  This is a typical example of how to use the I2C software library to ensure the
  steps of an I2C communication between slave and master.

   This is a two phase example that requires two boards(Master an Slave)  
   - Phase 1:
   In master board I2C peripheral is configured in Master Transmitter with Interrupt,
   where in Slave board I2C peripheral is configured in Slave Receiver with Interrupt.
   The master will send Data to Slave according to the defined buffer size.
   
   - Phase 2: 
   In master board I2C peripheral is configured in Master Receiver with Polling,
   where in Slave board I2C peripheral is configured in Slave Transmitter with 
   Interrupt. 
   Once the master has initiated the communication (Start condition), the slave
   will send back the previously received data to the master
   
   At the end of the data transfer, a data consistency check will be performed 
   in master side and in case of mismatch between sent and received data, LED4 
   will toggle infinitely. Otherwise LED1 will toggle. 

  Communication error are handled in Slave side, their occurrence will be signaled
  by puting On LED2.
  
  The "main.h" file allows different possibilities of configuration of this example:
  - Addressing mode : 7-bit or 10-bit
  - Safe procedure for master receiver
  - I2C speed: Fast mode or Standard mode
  - Buffer size also can be configured
  and though by choosing the desired configuration within main.h file.


  @par Directory contents

  - I2C/I2C_TwoBoards/I2C_DataExchange/X/main.c              Main file
  - I2C/I2C_TwoBoards/I2C_DataExchange/X/stm8l15x_conf.h     Library Configuration file
  - I2C/I2C_TwoBoards/I2C_DataExchange/X/stm8l15x_it.c       Interrupt routines source
  - I2C/I2C_TwoBoards/I2C_DataExchange/X/stm8l15x_it.h       Interrupt routines declaration
  - I2C/I2C_TwoBoards/I2C_DataExchange/X/interrupt.s         (to use only with IAR) 
  
  where X stands for Master or Slave directories.


  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density, Medium-Density Plus and 
    Medium-Density Devices.

  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density 
    devices) evaluation boards and can be easily tailored to any other
    development board.
  
  - STM8L1526-EVAL Set-up 
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - Make sure that Jumper JP7 is set in position 1-2 (I2C position).
    - Connect I2C1 Master SCL pin (PC.01) to I2C1 Slave SCL (PC.01)  
    - Connect I2C1 Master SDA pin (PC.00) to I2C1 Slave SDA (PC.00) 
    - Connect the two-boards grounds together

  - STM8L1528-EVAL Set-up 
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - Connect I2C1 Master SCL pin (PC.01) to I2C1 Slave SCL (PC.01)  
    - Connect I2C1 Master SDA pin (PC.00) to I2C1 Slave SDA (PC.00) 
    - Connect the two-boards grounds together
  
  - Other platform Set-up
    - Connect I2C1 Master SCL pin (PC.01) to I2C1 Slave SCL (PC.01)  
    - Connect I2C1 Master SDA pin (PC.00) to I2C1 Slave SDA (PC.00) 
    - Check that a pull-up resistor (4.7K) is connected on one I2C SDA pin
    - Check that a pull-up resistor (4.7K) is connected on one I2C SCL pin
    - Connect the two-boards grounds together
    @note The pull-up resitors are already implemented on the STM8L1528-EVAL and 
         STM8L1526-EVAL evaluation boards. 
    
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
