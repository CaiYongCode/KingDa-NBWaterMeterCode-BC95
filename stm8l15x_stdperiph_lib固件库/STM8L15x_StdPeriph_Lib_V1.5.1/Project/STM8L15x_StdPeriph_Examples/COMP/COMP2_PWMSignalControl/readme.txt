/** @page COMP2_PWMSignalControl  Use Comparator 2 to control PWM signals of TIM1
 * 

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    COMP/COMP2_PWMSignalControl/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the COMP2 PWM signal control Example.
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

  This example shows how to configure COMP2 peripheral to hold on safe state
  TIM1 inverted and non-inverted channels as soon as COMP2 output is set at high
  level.

  - COMP2 is configured as follow:
     - Inverting input is internally connected to DAC1 output
     - Non Inverting input is connected to PE5
     - Output is internally connected to TIM1 break

  - DAC1 is configured in 8-bit right alignment. DAC1 output = VREF * DOR / 256 
                                                              = 3.3 * 116 / 256 
                                                              = 1.5 V.

  - TIM1CLK is set to 2 MHz, the TIM1 Prescaler is equal to 0 so the TIM1 counter
    clock used is 2 MHz.
    TIM1 frequency is defined as follow:
    TIM1 channels frequency = TIM1 counter clock / (TIM1_PERIOD + 1) = 30.52 Hz.

    The break Polarity is defined at high level so applying a voltage higher 
    than 1.5 V (DAC1 output = inverting input   on PE5 (non inverting input   sets
    the non-inverted channels and inverted channels in idle state: high level.

    A dead time of 58.5 µs is inserted between each two complementary channels:
    dead time = DEADTIME / TIM1CLK = 117 / 2 MHz = 58.5 µs.

    The selected lock level is level 1 so once programmed channels idle state, 
    break enable and polarity bits can no longer be written.

  - External voltage should be connected to PE5.

  - Connect an oscilloscope to TIM1 channels to display waveforms. 

  @par Directory contents

  - COMP\COMP2_PWMSignalControl\main.c                      Main file containing the "main" function
  - COMP\COMP2_PWMSignalControl\stm8l15x_conf.h             Library Configuration file
  - COMP\COMP2_PWMSignalControl\stm8l15x_it.c               Interrupt routines source
  - COMP\COMP2_PWMSignalControl\stm8l15x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and 
      Medium-Density Devices.

  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density 
    devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL & STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
       For more details please refer to the evaluation board user manual.

  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Connect the external voltage to PE5
  - Connect TIM1 channels to an oscilloscope

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
