/** @page TIM1_PWMInput Use the TIM1 peripheral to measure the frequency and duty cycle of an external signal

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    TIM1/TIM1_PWMInput/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the TIM1 PWM Input Example.
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

  This example shows how to configure the TIM1 peripheral to measure 
  the frequency and the duty cycle of an external signal.
  TIM1CLK is set to 16 MHz, the TIM1 Prescaler is equal to 1 so the minimum 
  frequency value to measure is 245 Hz.
  The TIM1 Channel 1 is configured in PWM Input Mode: the external signal is 
  connected to TIM1 Channel1.
  To measure the frequency we use the TIM1 CC1 interrupt request, and the 
  frequency of the external signal is computed in the TIM1_CAP_IRQHandler
  routine.
  The frequency and the duty cycle of the external signal are stored in 
  SignalFrequency and SignalDutyCycle variables:
  SignalFrequency = TIM1CLK / TIM1_CCR1 in Hz,
  SignalDutyCycle = (TIM1_CCR2 * 100) / (TIM1_CCR1) in %.

  @par Directory contents

  - TIM1/TIM1_PWMInput/main.c              Main file containing the "main" function
  - TIM1/TIM1_PWMInput/stm8l15x_conf.h     Library Configuration file
  - TIM1/TIM1_PWMInput/stm8l15x_it.c       Interrupt routines source
  - TIM1/TIM1_PWMInput/stm8l15x_it.h       Interrupt routines declaration


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
     - Connect the external signal to measure to TIM1 CH1 pin (PD.2  


  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
   - Connect the external signal to measure to the TIM1 Channel1 pin (PD.2  
   - Add "SignalFrequency" and "SignalDutyCycle" variables in watch to display 
     the frequency and duty cycle of the external signal.
     (declared in TIM1/TIM1_PWMInput/stm8l15x_it.c  
  
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
