/** @page DAC_SignalsGeneration Use DAC with DMA to generate square, triangular, sinusoidal and sincard signals

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    DAC/DAC_SignalsGeneration/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the DAC signals generation Example.
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

  This example provides a short description of how to use the DAC peripheral
  to generate several signal using DMA memory to peripheral mode.
  By Default, DMA transfers continuously to the DAC, the Triangular Table waveform.
  When the user presses the LEFT button, DMA transfers the selected waveform to DAC.
  Four waveforms are available: Triangular waveform, Square waveform, Sinc waveform
  and Sine waveform.
  When the user press the RIGHT button, DMA transfer frequency is increased, the
  frequency of the selected waveform is multiplied by 2.
  Five different frequencies are available.
  

  @par Directory contents

  - DAC/DAC_SignalsGeneration/main.c              Main file
  - DAC/DAC_SignalsGeneration/main.h              Main file declaration
  - DAC/DAC_SignalsGeneration/stm8l15x_conf.h     Library Configuration file
  - DAC/DAC_SignalsGeneration/stm8l15x_it.c       Interrupt routines source
  - DAC/DAC_SignalsGeneration/stm8l15x_it.h       Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and Medium-Density 
    Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density
    devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
     - LEFT and RIGHT Joystick push-buttons.
     - BNC connector CN15 (DAC_OUT)  
     - Make sure that jumper JP10 is in BNC position.
  
  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - LEFT and RIGHT Joystick push-buttons.
     - BNC connector CN2 (DAC_OUT)  
     - Make sure that jumper JP3 is removed.
  
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Connect an oscilloscope to BNC connector. 
  - Press Joystick LEFT Button to change the waveform.
  - Press Joystick RIGHT Button to change the waveform frequency.

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
