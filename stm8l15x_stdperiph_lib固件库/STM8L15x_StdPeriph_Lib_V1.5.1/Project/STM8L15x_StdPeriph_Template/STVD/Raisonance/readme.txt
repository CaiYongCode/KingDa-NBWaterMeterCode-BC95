/** @page project_r Template project for ST Visual Develop (STVD) toolchain with Raisonance compiler

  @verbatim
  ******************* (C) COPYRIGHT 2011 STMicroelectronics ********************
  * @file    readme.txt
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   This sub-directory contains all the user-modifiable files needed to
  *          create a new project linked with the STM8L15x Standard Peripherals 
  *          Library and working with STVD and Raisonance software toolchain.
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
 
  This folder contains a standard STVD template workspace with three projects related 
  respectively to Low density Medium density and High density devices.
  Each project includes all the user-modifiable files that are necessary to
  create a new project.
  This project template can be used by mean of minor updates in the library 
  files to run the STM8L15x_StdPeriph_Examples, or custom user applications.   

        
  @par Directories contents

  - STM8L15x_StdPeriph_Template\\STVD\\Raisonance
     - project.stw              Workspace file
     - stm8l1526-eval-ld.stp    Project file for Low density STM8L15x devices
     - stm8l1526-eval.stp       Project file for Medium density STM8L15x devices
     - stm8l1528-eval.stp       Project file for High density STM8L15x devices

  @par How to use it ?

  - Open the STVD workspace
  - Set active the project related to the used product: Project -> Set Active Project, 
  and choose the desired project 
  - Select your debug instrument: Debug instrument -> Target Settings, select the 
  target you want to use for debug session (Swim Stice or Swim Rlink)
  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  
  @b Tip: If it is your first time using STVD, you have to confirm the default 
  toolset and path information that will be used when building your application, 
  to do so:
    - Select Tools -> Options
    - In the Options window click on the Toolset tab
    - Select your toolset from the Toolset list box.
    If the path is incorrect you can type the correct path in the Root Path 
    field, or use the browse button to locate it.
    - In the subpath fields, type the correct subpath if necessary 

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