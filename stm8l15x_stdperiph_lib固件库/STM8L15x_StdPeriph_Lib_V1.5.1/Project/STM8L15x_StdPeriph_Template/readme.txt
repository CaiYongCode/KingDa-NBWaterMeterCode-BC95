/**
  @page exampletemplate Project Example Template
  
  @verbatim
  ******************** (C) COPYRIGHT 2011 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   This sub-directory contains all the user-modifiable files 
  *          needed to create a new project linked with the STM8L15x 
  *          Standard Peripheral Library.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Project Example Template Description 

This example is used as a template that can be used as reference to build any new 
firmware development for all STM8L15x product devices using the STM8L15x 
Standard Peripherals Library.


@par Directory contents 

This folder contains standard template projects for EWSTM8, STVD with Cosmic, 
STVD with raisonance and RIDE toolchains that compile the needed STM8S/A Standard
Peripheral's drivers plus all the user-modifiable files that are necessary to 
create a new project. 

  - Project/STM8L15x_StdPeriph_Template/stm8l15x_conf.h    Library Configuration file

  - Project/STM8L15x_StdPeriph_Template/stm8l15x.c:     Source file containing the interrupt handlers (the 
                                                        function bodies are empty in this template).

  - Project/STM8L15x_StdPeriph_Template/stm8l15x.h      Header file including all interrupt handlers prototypes.

  - Project/Template/main.c          Main program
          
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
