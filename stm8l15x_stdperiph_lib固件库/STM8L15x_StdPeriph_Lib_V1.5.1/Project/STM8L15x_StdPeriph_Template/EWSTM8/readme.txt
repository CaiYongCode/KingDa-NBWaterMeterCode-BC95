/** @page ewstm8 Template project for IAR Embedded Workbench for STM8 (EWSTM8)

  @verbatim
  ******************* (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   This sub-directory contains all the user-modifiable files needed to
  *          create a new project linked with the STM8L15x Standard Peripherals 
  *          Library and working with IAR Embedded Workbench for STM8 (EWSTM8)
  *          software toolchain.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  
  @par Description

  This folder contains a standard EWSTM8 template workspace with three projects 
  including all the user-modifiable files that are necessary to create a new project.
  These project templates can be used by mean of minor updates in the library files
  to run theSTM8L15x_StdPeriph_Examples, or custom user applications.  

  
  @par Directories contents

 - project .ewd/.eww/.ewp: A pre-configured project file with the provided library 
                           structure that produces an executable image with IAR 
                           Embedded Workbench.


  @par How to use it ?

 - Open the Project.eww workspace.
 - In the workspace toolbar select the project configuration:
     - stm8l1526-eval-ld: to configure the project for STM8L15x Low-density devices. 
     - stm8l1526-eval: to configure the project for STM8L15x Medium-density devices.
     - stm8l1528-eval: to configure the project for STM8L15x High-density devices.

     @note The needed define symbols for these configurations are already declared in the
           preprocessor section.

 - Rebuild all files: Project->Rebuild all
 - Load project image: Project->Debug
 - Run program: Debug->Go(F5)
  
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
