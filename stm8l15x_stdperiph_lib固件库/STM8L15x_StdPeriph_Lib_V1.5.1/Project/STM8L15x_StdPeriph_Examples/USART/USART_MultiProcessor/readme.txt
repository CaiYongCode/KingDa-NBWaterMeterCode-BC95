/** @page USART_MultiProcessor Use the USART in multi-processor mode

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    USART/USART_MultiProcessor/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the USART multi-processor Example.
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

  This example provides a description of how to use the USART in multi-processor mode.
  The USART Master and USART Slave addresses are set to 0x1 and 0x2, 
  respectively.
   
  - In the Master board (define USART_MASTER in main.h  , USART Master 
    continuously sends the 0x33 character to second board (USART Slave  . 
  - In the Slave board, four LEDs are toggled while the USART receives 0x33.
  - In the Slave board when KEY pushbutton is pressed, an interrupt is generated
    and in the EXTI Interrupt service routine, the USART enters mute mode and 
    remains in this mode (no LEDs toggling   
  - In the Master board when KEY pushbutton is pressed, an interrupt is 
    generated and in the EXTI Interrupt service routine, USART Master sends the 
    address mark character (0x102) to wake up USART Slave. 
  - In the Slave board the USART slave receives the wake up and the LEDs restart 
    toggling. 

  USART Master and Slave configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 9 Bits
  - One Stop Bit
  - No parity
  - Receive and transmit enabled

              
   @par Directory contents

  - USART\USART_MultiProcessor\main.c            Main file containing the "main" function
  - USART\USART_MultiProcessor\main.h            Main functions prototype
  - USART\USART_MultiProcessor\stm8l15x_conf.h   Library Configuration file
  - USART\USART_MultiProcessor\stm8l15x_it.c     Interrupt routines source
  - USART\USART_MultiProcessor\stm8l15x_it.h     Interrupt routines declaration


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
     - To run this example it is necessary to use two STM8L1528-EVAL boards: 
       one to run the USART Master and another to run the USART Salve. 
       Connect USART2_Tx(PH.05) and USART2_Rx(PH.04) on the first board to 
       respectively USART2_Rx(PH.04) and USART2_Tx(PH.05) on the second board 
       (or connect a null-modem female/female RS232 cable between the two 
       boards: CN7 connector on each board).
       - Make sure that JP5 jumper is in RS232 position.
       - Make sure that JP11 jumper is in RS232 position if a null-modem 
             female/female RS232 cable is used to connect the two boards
             otherwise make sure that JP11 is not in RS232 position.
       - Make sure that the two boards are connected to the same ground.
       - Four leds LD1, LD2, LD3 and LD4

  - STM8L1526-EVAL Set-up 
     - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
     - Make sure that Jumper JP7 is set in KEY position. 
     - To run this example it is necessary to use two STM8L1526-EVAL boards: one
       to run the USART1 Master and another to run the USART1 Salve. 
       Connect USART1_Tx(PC.03   and USART1_Rx(PC.02) on the first board to 
       respectively USART1_Rx(PC.02) and USART1_Tx(PC.03) on the second board (
       or connect a null-modem female/female RS232 cable between the two boards: 
       CN1 connector on each board).
       - Make sure that JP5 jumper is in RS232 position.
       - Make sure that the two boards are connected to the same ground.
     - Four leds LD1, LD2, LD3 and LD4

   
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
