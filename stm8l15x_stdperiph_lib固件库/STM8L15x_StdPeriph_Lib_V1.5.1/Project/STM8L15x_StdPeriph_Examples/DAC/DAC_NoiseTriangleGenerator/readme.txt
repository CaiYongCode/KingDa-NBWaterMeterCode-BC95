/** @page DAC_NoiseTriangleGenerator Use DAC Noise and Triangle Generator feature

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    DAC/DAC_NoiseTriangleGenerator/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the DAC Noise and Triangle Generation Example.
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
  to generate, automatically, Noise and Triangle waveform.
  By Default, DAC channel1 is generating a Triangle waveform   and DAC channel2
  is generating a white Noise waveform with the maximum amplitude.
  When the user presses the LEFT button,the Triangle waveform Amplitude is decreasing.
  When the user presses the RIGHT button,the Noise waveform Amplitude is decreasing.
  

  @par Directory contents

  - DAC/DAC_Noise&TriangleGenerator/main.c            Main file
  - DAC/DAC_Noise&TriangleGenerator/stm8l15x_conf.h   Library Configuration file
  - DAC/DAC_Noise&TriangleGenerator/stm8l15x_it.c     Interrupt routines source
  - DAC/DAC_Noise&TriangleGenerator/stm8l15x_it.h     Interrupt routines declaration

  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL
    evaluation boards and can be easily tailored to any other development board.
    
  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.
     - LEFT and RIGHT Joystick push-buttons.
     - Make sure that jumper JP3 is removed.

  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Connect an oscilloscope to DAC_Channel1 (PF.0) and DAC_Channel_2 (PF.1).
  - Press Joystick LEFT Button to change the DAC channel 1 Triangle waveform amplitude.
  - Press Joystick RIGHT Button to change the  DAC channel 2 Noise waveform amplitude.
  
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
