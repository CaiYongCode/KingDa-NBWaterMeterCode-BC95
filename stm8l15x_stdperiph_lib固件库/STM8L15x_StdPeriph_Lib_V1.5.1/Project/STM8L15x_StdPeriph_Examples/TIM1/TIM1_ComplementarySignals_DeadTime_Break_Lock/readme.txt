/** @page TIM1_ComplementarySignals_DeadTime_Break_Lock Generating three complementary PWM signals with dead time insertion, break capability and lock option using TIM1

  @verbatim
  ******************** (C) COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM1/TIM1_ComplementarySignals_DeadTime_Break_Lock/readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the TIM1 complementary signals with dead time, break and lock Example.
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

  This example shows how to configure the TIM1 peripheral to generate three
  complementary signals, to insert a defined dead time value, to use the
  break feature and to lock the desired parameters.

  TIM1CLK is set to 2 MHz, the TIM1 Prescaler is equal to 0 so the TIM1 counter
  clock used is 2 MHz.
  TIM1 frequency is defined as follow:
  TIM1 channels frequency = TIM1 counter clock / (TIM1_PERIOD + 1) = 30.52 Hz.

  The Three Duty cycles are computed as the following description:

  TIM1 Channel1 duty cycle = CCR1_VAL / (TIM1_PERIOD + 1) = 50%
  TIM1 Channel1N duty cycle = (TIM1_PERIOD - CCR1_VAL) / (TIM1PERIOD + 1) = 50%

  TIM1 Channel2 duty cycle = CCR2_VAL / (TIM1_PERIOD + 1) = 25%
  TIM1 Channel2N duty cycle = (TIM1_PERIOD - CCR2_VAL) / (TIM1PERIOD + 1) = 75%

  TIM1 Channel3 duty cycle = CCR3_VAL / TIM1_PERIOD = 12.5%
  TIM1 Channel3N duty cycle = (TIM1_PERIOD - CCR3_VAL) / (TIM1PERIOD + 1) = 87.5%

  The break Polarity is defined at low level so applying a low level on PD6
 sets the non-inverted channels and inverted channels in idle state: high level.

  A dead time of 58.5 µs is inserted between each two complementary channels:
  dead time = DEADTIME / TIM1CLK = 117 / 2 MHz = 58.5 µs.

  The selected lock level is level 1 so once programmed channels idle state,
  break enable and polarity bits can no longer be written.

  The TIM1 waveform can be displayed using an oscilloscope.

  @par Directory contents

  - TIM1_ComplementarySignals_DeadTime_Break_Lock/main.c                   Main file containing the "main" function
  - TIM1_ComplementarySignals_DeadTime_Break_Lock/stm8l15x_conf.h          Library Configuration file
  - TIM1_ComplementarySignals_DeadTime_Break_Lock/stm8l15x_it.c            Interrupt routines source
  - TIM1_ComplementarySignals_DeadTime_Break_Lock/stm8l15x_it.h            Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and Medium-Density 
    Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density
    devices) evaluation boards and can be easily tailored to any other
    development board.

  - STM8L1528-EVAL and STM8L1526-EVAL Set-up
    - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.
    - Connect TIM1 channels pins to an oscilloscope as follows:
     - TIM1 Channel 1   pin (PD2)  
     - TIM1 Channel 1N  pin (PD7)  
     - TIM1 Channel 2   pin (PD4)  
     - TIM1 Channel 2N  pin (PE1)  
     - TIM1 Channel 3   pin (PD5)  
     - TIM1 Channel 3N  pin (PE2)  
    - Make sure that the MicroSD card is disconnected before running 
        the example (in case of using STM8L1526-EVAL).


  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
    - Connect TIM1 channels pins to an oscilloscope
    - You can apply a low level on pin PD6 to set channels in idle state.
    
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
