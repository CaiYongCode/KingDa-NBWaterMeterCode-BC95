/** @page USART_IrDA Use the USART in a basic IrDA communication receive/transmit mode.

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    USART/USART_IrDA/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the USART IrDA Example.
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

  The example provides two IrDA program: transmitter / receiver and requires two
  boards to be able to run the full demonstration:
   - one board will act as IrDA transmitter
   - one board will act as IrDA receiver

  On the Transmitter board: Five pins, configured in input floating mode, are 
  used to select the byte to be sent at each pin state change
  The byte can be:
   - 0x00 if no key pressed
   - 0x01 if Joystick Sel pressed
   - 0x02 if Joystick Down pressed
   - 0x03 if Joystick Left pressed
   - 0x04 if Joystick Right pressed
   - 0x05 if Joystick Up pressed

   On the Receiver board: Four leds are used to show which byte is received. 
  - LED4 toggle when 0x05 is received (Joystick Up pressed in Transmitter board)  
  - LED3 toggle when 0x02 is received (Joystick Down pressed in Transmitter board)  
  - LED2 toggle when 0x03 is received (Joystick Left pressed in Transmitter board)  
  - LED1 toggle when 0x04 is received (Joystick Right pressed in Transmitter board)  
  - LED1 to LED4 toggle when 0x01 is received (Joystick Sel pressed in Transmitter board)         

  USART configured as follow:
   - BaudRate = 9600 baud  
   - Word Length = 8 Bits
   - One Stop Bit
   - No parity
   - Receive and transmit enabled

  
  @par Directory contents

  - USART/USART_IrDA/main.c                   Main file containing the "main" function
  - USART/USART_IrDA/stm8l15x_conf.h          Library Configuration file
  - USART/USART_IrDA/stm8l15x_it.c            Interrupt routines source
  - USART/USART_IrDA/stm8l15x_it.h            Interrupt routines declaration


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
     - IrDA transceiver (U6) is used, make sure that JP5 jumper is in IrDA position.
     - LED1..4
     - Joystick

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
     - IrDA transceiver (U2) is used, make sure that JP5 jumper is in IrDA position.
     - LED1..4
     - Joystick
 
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - In main.c file select if the board will act as
    - transmitter (USART_IrDA_TRANSMIT define enabled)  
    - or receiver (USART_IrDA_RECEIVE define enabled ) 
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
