/** @page AES_EncryptDecrypt  Use AES to encrypt then to decrypt data

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    AES/AES_EncryptDecrypt/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the AES encryption decryption example.
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

  This example provides a short description of how to configure the AES hardware 
  accelerator to encrypt then to decrypt text and to check that decrypted text 
  corresponds to the original text.
  This example is a basic example using polling on flag, neither interrupt 
  nor DMA capability are used.
  
  @par Directory contents

  - AES/AES_EncryptDecrypt/main.c                   Main file
  - AES/AES_EncryptDecrypt/stm8l15x_conf.h          Library Configuration file
  - AES/AES_EncryptDecrypt/stm8l15x_it.c            Interrupt routines source
  - AES/AES_EncryptDecrypt/stm8l15x_it.h            Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density Devices with built-in AES peripheral.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL evaluation
    board and can be easily tailored to any other development board.

  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - LED1 and LED3


  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - If green led LED1 is ON, text is successfully encrypted then decrypted.
  - If red led LED3 is ON, an error occurs while encrypting or decrypting.
      
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