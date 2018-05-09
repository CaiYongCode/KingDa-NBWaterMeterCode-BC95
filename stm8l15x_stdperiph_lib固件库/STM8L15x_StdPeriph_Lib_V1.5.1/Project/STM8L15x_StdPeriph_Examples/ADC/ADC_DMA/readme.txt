/** @page ADC_DMA Use ADC to convert continuously Channel 3 and Channel 24 in scan mode using DMA
  
  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    ADC/ADC_DMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the ADC DMA Example.
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

  This example provides a short description of how to use the ADC peripheral
  to convert two ADC Channels input voltage using DMA.
  The ADC channel 3 and channel 24 converted voltage values are displayed on LCD.

  In the STM8L1528-EVAL board, ADC Channel 3 is connected to RV3 Adjuster and ADC 
  Channel 24 is connected to BNC connector CN2.
  In the STM8L1526-EVAL board, ADC Channel 3 is connected to RV2 Adjuster and ADC 
  Channel 24 is connected to BNC connector CN15.   

  Turning RV adjuster provides a voltage which can vary from 0 Volt to 3.3 Volt.
  The BNC connector may be connected to a DC Power supply voltage to provide
  a voltage from 0 Volt to 3.3 Volt.
  
  @par Directory contents

  - ADC/ADC_DMA/main.c             Main file containing the "main" function
  - ADC/ADC_DMA/stm8l15x_conf.h    Library Configuration file
  - ADC/ADC_DMA/stm8l15x_it.c      Interrupt routines source
  - ADC/ADC_DMA/stm8l15x_it.h      Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8L15x High-Density, Medium-Density Plus and 
  Medium-Density Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density)
    evaluation boards and can be easily tailored to any other development board.

  - STM8L1528-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
     For more details please refer to the evaluation board user manual.
     - RV3 adjuster
     - BNC connector CN2
     - Dot matrix LCD
    
  - STM8L1526-EVAL Set-up
     - Make sure that the LCD glass daughter board is mounted in IO position.
     For more details please refer to the evaluation board user manual.
     - RV2 adjuster
     - BNC connector CN15
     - Dot matrix LCD
     - Before Running the example make sure that jumper JP10 is in BNC position.
  
  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Turn RV Adjuster to provide a varing voltage (from 0 Volt to 3.3 Volt). The 
    ADC Channel 3 converted value is displayed on LCD.
  - Connect a Power supply varing voltage (from 0 Volt to 3.3 Volt) to the BNC 
    connector. The ADC Channel 24 converted value is displayed on LCD.
  
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
