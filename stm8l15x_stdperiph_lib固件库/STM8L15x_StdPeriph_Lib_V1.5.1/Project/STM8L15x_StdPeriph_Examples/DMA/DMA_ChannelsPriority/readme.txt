/** @page DMA_ChannelsPriority Use DMA to transfer data with different channels priorities

  @verbatim
  ******************** (C)COPYRIGHT 2011 STMicroelectronics *******************
  * @file    DMA/DMA_ChannelsPriority/readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Description of the DMA Channels priority example.
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

  This example provides a short description of how to use the DMA peripheral and 
  change the channels priority. 
  Changing the channels priority has an impact on the result. All transfer size 
  is 8bit and length is 1.
  The channels are configured to perform these transfers:
  
  - DMA channel 0 : Transfer A : from RAM buffer2 to TIM3 registers
  - DMA channel 1 : Transfer B : from RAM buffer1 to TIM2 registers
  - DMA channel 2 : Transfer C : from TIM1 registers to RAM buffer1
  - DMA channel 3 : Transfer D : from TIM4 registers to RAM buffer2
  
  Before starting any transfer, the RAM buffers and timers registers are 
  initialized as follow:
  - RAM Buffer1 : 0x00
  - TIM1 ARRL : 0x11   
  - TIM2 ARRL : 0x22   
  - TIM3 ARRL : 0x33   
  - TIM4 ARR : 0x44 
  - RAM Buffer2 : 0x55
  
  After each specific configuration of the priorities, the RAM buffers and timers 
  registers content change.
  
  To select which configuration to run, uncomment one of the following "defines" 
  in main.c
  
  \#define PRIORITIES_CONFIG_HW
  \#define PRIORITIES_CONFIG_SW_1
  \#define PRIORITIES_CONFIG_SW_2
  
  Then read the value of RAM Buffer1, TIM1 ARRL, TIM2 ARRL, TIM3 ARRL, TIM4 ARR, RAM Buffer2.
  
  @b Note 1  : if  PRIORITIES_CONFIG_HW is defined, the expected result is :
   
  - RAM Buffer1 = 0x11
  - TIM1 ARRL = 0x11
  - TIM2 ARRL = 0x00
  - TIM3 ARRL = 0x55
  - TIM4 ARR = 0x44
  - RAM Buffer2 = 0x44
  
  @b Note 2  : if  PRIORITIES_CONFIG_SW_1 is defined, the expected result is : 
  
  - RAM Buffer1 = 0x11 
  - TIM1 ARRL = 0x11
  - TIM2 ARRL = 0x11
  - TIM3 ARRL = 0x44 
  - TIM4 ARR = 0x44
  - RAM Buffer2 = 0x44
  
  @b Note 3  : if  PRIORITIES_CONFIG_SW_2 is defined, the expected result is : 
  
  - RAM Buffer1 = 0x11 
  - TIM1 ARRL = 0x11
  - TIM2 ARRL = 0x00
  - TIM3 ARRL = 0x55 
  - TIM4 ARR = 0x44
  - RAM Buffer2 = 0x44
    
  @par Directory contents

  - DMA/DMA_ChannelsPriority/main.c            Main file containing the "main" function
  - DMA/DMA_ChannelsPriority/stm8l15x_conf.h   Library Configuration file
  - DMA/DMA_ChannelsPriority/stm8l15x_it.c     Interrupt routines source
  - DMA/DMA_ChannelsPriority/stm8l15x_it.h     Interrupt routines declaration


  @par Hardware and Software environment

    - This example runs on STM8L15x High-Density, Medium-Density Plus and Medium-Density
       Devices.
  
  - This example has been tested with STMicroelectronics STM8L1528-EVAL 
    (STM8L15x High-Density devices) and STM8L1526-EVAL (STM8L15x Medium-Density 
    devices) evaluation boards and can be easily tailored to any other
    development board. 

  - STM8L1526-EVAL & STM8L1528-EVAL Set-up
  - Make sure that the LCD glass daughter board is mounted in IO position.
      For more details please refer to the evaluation board user manual.


  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\STM8L15x_StdPeriph_Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Add "TIM1RegValue", "TIM2RegValue", "TIM3RegValue", "TIM4RegValue", 
    "RAMBuffer1Value" and "RAMBuffer2Value" variables in watch to display 
     their content.

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
