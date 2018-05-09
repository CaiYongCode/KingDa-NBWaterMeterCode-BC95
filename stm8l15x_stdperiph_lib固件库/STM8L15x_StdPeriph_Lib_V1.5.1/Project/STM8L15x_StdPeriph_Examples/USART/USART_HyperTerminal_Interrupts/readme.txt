/** @page USART_HyperTerminal_Interrupts Use the USART interrupts to communicate with the HyperTerminal

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    USART/USART_HyperTerminal_Interrupts/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the USART HyperTherminal interrupts Example.
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

  This example provides a description of how to use the USART interrupts to 
  communicate with the HyperTerminal.
  The USART sends a predefined buffer to the HyperTerminal and keep waiting 
  data to be entered by user and toggling infinitely LD1..LD4, each byte 
  received is sent back to the HyperTerminal. 
  The communication is managed by Transmit and Receive interrupts. 

  USART is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits (Word Length = 7 data bit + 1 parity bit  
    - One Stop Bit
    - Odd parity
    - Receive and transmit enabled
    - USART Clock disabled
  @note When the parity is enabled, the computed parity is inserted at the MSB
          position of the transmitted data.

              
  @par Directory contents

  - USART/USART_HyperTerminal_Interrupts/main.c            Main file containing the "main" function
  - USART/USART_HyperTerminal_Interrupts/stm8l15x_conf.h   Library Configuration file
  - USART/USART_HyperTerminal_Interrupts/stm8l15x_it.c     Interrupt routines source
  - USART/USART_HyperTerminal_Interrupts/stm8l15x_it.h     Interrupt routines declaration


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
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
       CN7 and PC serial port.
    - Make sure that JP5 jumper is in RS232 position
    - Make sure that JP11 jumper is in RS232 position
    - Make sure that JP12 jumper is in RS232 position
    
  - STM8L1526-EVAL Set-up  
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN1 and PC serial port.
    - Make sure that JP5 jumper is in RS232 position

         
  - HyperTerminal configuration:
     - Word Length = 7 Bits
     - One Stop Bit
     - Odd parity
     - BaudRate = 115200 baud


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
