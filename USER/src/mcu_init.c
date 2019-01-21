/*********************************************************************************
//概述：
//作者：随风飘跃     时间：       地点：
//CPU型号：         系统主频：
//版本号：V0.0        
*********************************************************************************/
/*********************************************************************************
文件包含区
*********************************************************************************/
#include "include.h"
/*********************************************************************************
常量定义区
*********************************************************************************/

/*********************************************************************************
公共变量定义区
*********************************************************************************/
/*********************************************************************************
外部变量声明区
*********************************************************************************/
/*********************************************************************************
私有变量定义区
*********************************************************************************/ 
/*********************************************************************************
测试变量定义区
*********************************************************************************/
/*********************************************************************************
内部函数定义区
*********************************************************************************/
/*********************************************************************************
功能代码定义区
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void MCU_Config(void)
//{
//  RCC_Configuration();
//  GPIO_Configuration();
//  TIM4_Config();
//  USART2_Configuration();
//  USART3_Configuration();
//  ITC_Config();
//  Pulse_Acquire_Config();
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void MCU_DeInit(void)
{ 
  USART_DeInit(USART2);                                         //清除USART2寄存器
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2, DISABLE);    //关闭USART2时钟
  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_Low_Slow);    //USART2 TXD
  
  USART_DeInit(USART3);                                         //清除USART3寄存器
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, DISABLE);    //关闭USART3时钟
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_Low_Slow);    //USART3 TXD
  
  GPIO_Init(GPIOA, GPIO_Pin_4,  GPIO_Mode_Out_PP_Low_Slow);         // 热敏电阻
  GPIO_Init(GPIOA, GPIO_Pin_5,  GPIO_Mode_Out_PP_Low_Slow);         // 热敏电阻ADC检测端
  
  GPIO_Init(GPIOE,GPIO_Pin_1,GPIO_Mode_Out_PP_Low_Slow);       //BC95 复位脚
  GPIO_Init(GPIOE,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Slow);        //BC95 VBAT

  
  MeterParameter.DeviceStatus = SLEEP;
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void RCC_Configuration(void)                                                   //时钟初始化
{
//  CLK_DeInit(); 
//  CLK_HSICmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);                                         //16M速度

//  CLK_ClockSecuritySystemEnable();//
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //


*********************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_Init(GPIOA, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow); //GPIO端口推挽输出低
  GPIO_Init(GPIOB, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOC, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOD, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOE, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOF, GPIO_Pin_All,GPIO_Mode_Out_PP_Low_Slow);
  
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void TIM4_Config(void)
//{ 
//  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4 , ENABLE);              //使能定时器4时钟
//  TIM4_TimeBaseInit(TIM4_Prescaler_128 , 125);    //设置定时器4为128分频，向上计数，计数值为125即为1毫秒的计数值
//  TIM4_ITConfig(TIM4_IT_Update , ENABLE);         //使能向上计数溢出中断
//  TIM4_ARRPreloadConfig(ENABLE);                  //使能定时器4自动重载功能    
//  TIM4_Cmd(ENABLE);                               //启动定时器4开始计数
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void USART2_Configuration ( void )
{  
  CLK_PeripheralClockConfig(CLK_Peripheral_USART2, ENABLE);
  USART_DeInit(USART2);
  GPIO_Init(GPIOE, GPIO_Pin_3 , GPIO_Mode_In_PU_No_IT);
  GPIO_Init(GPIOE, GPIO_Pin_4 , GPIO_Mode_Out_PP_High_Fast);
  USART_Init(USART2,
             9600,
             USART_WordLength_8b,
             USART_StopBits_1,
             USART_Parity_No,
             USART_Mode_TxRx);    
  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);//允许接收完成中断
  USART_Cmd(USART2,ENABLE);
  
  ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn, ITC_PriorityLevel_2);  //串口2优先级
  ITC_SetSoftwarePriority(TIM2_CC_USART2_RX_IRQn, ITC_PriorityLevel_2);              //串口2优先级
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void USART3_Configuration ( void )
{
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);
  USART_DeInit(USART3);
  GPIO_Init(GPIOE, GPIO_Pin_7 , GPIO_Mode_In_PU_No_IT);
  GPIO_Init(GPIOE, GPIO_Pin_6 , GPIO_Mode_Out_PP_High_Fast);
  USART_Init(USART3,
             9600,
             USART_WordLength_8b,
             USART_StopBits_1,
             USART_Parity_No,
             USART_Mode_TxRx);    
  USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);//允许接收完成中断
  USART_Cmd(USART3,ENABLE);
  
  ITC_SetSoftwarePriority(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn, ITC_PriorityLevel_2);  //串口3优先级
  ITC_SetSoftwarePriority(TIM3_CC_USART3_RX_IRQn, ITC_PriorityLevel_3);              //串口3优先级
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:	    	//
 Others:        //
*********************************************************************************/
//void ITC_Config(void)                                                          //中断控制  0最低 3最高  
//{
//    ITC_SetSoftwarePriority(TIM4_UPD_OVF_TRG_IRQn, ITC_PriorityLevel_3);        //定时器4溢出优先级
//
//    ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn, ITC_PriorityLevel_2);  //串口2优先级
//    ITC_SetSoftwarePriority(TIM2_CC_USART2_RX_IRQn, ITC_PriorityLevel_2);              //串口2优先级
//    ITC_SetSoftwarePriority(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn, ITC_PriorityLevel_1);  //串口3优先级
//    ITC_SetSoftwarePriority(TIM3_CC_USART3_RX_IRQn, ITC_PriorityLevel_1);              //串口3优先级
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void Read_Voltage(void)
{
  unsigned short value = 0;
  float vdd = 0;
  
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);   //开启ADC时钟
  ADC_Init (ADC1,ADC_ConversionMode_Continuous, 
                                          ADC_Resolution_12Bit, ADC_Prescaler_1 );         //断续模式 12位 1分频
  
  ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_384Cycles);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  ADC_VrefintCmd(ENABLE);                                 //启动内部参考电压
  ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE );         //通道选择内部电压
  

  ADC_SoftwareStartConv (ADC1);                                 //ADC开始转换
  while(RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));        //检测ADC是否转换结束
  ADC_ClearFlag (ADC1,ADC_FLAG_EOC );    
  
  value=ADC_GetConversionValue(ADC1);                      //获取转换值
  vdd=1.224*4096/value;                                    //获得VDD电压，单位V
  ADC_Cmd(ADC1, DISABLE);                                       //关闭ADC外围
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,DISABLE);       //关闭ADC时钟
  
  MeterParameter.Voltage = (unsigned short)(vdd*100);
}
/*********************************************************************************
 Function:      //
 Description:   //测量电压
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//void ADC_Config(void)
//{
//  /* Enable ADC1 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
///* Initialize and configure ADC1 */
//  ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_1);
//  ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_24Cycles);
//  ADC_SamplingTimeConfig(ADC1, ADC_Group_FastChannels, ADC_SamplingTime_24Cycles);
//
//  /* Enable ADC1 */
//  ADC_Cmd(ADC1, ENABLE);
//  ADC_VrefintCmd(ENABLE);
//
//  /* Enable ADC1 Channels 3 */
//  ADC_ChannelCmd(ADC1, ADC_Channel_3, ENABLE); /* connected to Potentiometer RV */
//  /* Enable ADC1 Channels 24 */
//  ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE); /* connected to ADC_Channel_Vrefint */
//
//}
//void DMA_Config(void)
//{
//   /* Enable DMA1 clock */
//  CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
//  /* Connect ADC to DMA channel 0 */
// SYSCFG_REMAPDMAChannelConfig(REMAP_DMA1Channel_ADC1ToChannel0);//ADC通道要remap
////BUFFER_SIZE
//  DMA_Init(DMA1_Channel0, 
//           ADC1_SAMPLE_BUFFER_ADDRESS,
//           ADC1_DR_ADDRESS,
//           ADC1_SAMPLE_BUFFER_SIZE,
//           DMA_DIR_PeripheralToMemory,
//           DMA_Mode_Circular,
//           DMA_MemoryIncMode_Inc,
//           DMA_Priority_High,
//           DMA_MemoryDataSize_HalfWord);
//  /* DMA Channel0 enable */
//  DMA_Cmd(DMA1_Channel0, ENABLE);
//  /* Enable DMA1 channel0 Transfer complete interrupt */
//  DMA_ITConfig(DMA1_Channel0, DMA_ITx_TC, ENABLE);   
//  /* DMA enable */
//  DMA_GlobalCmd(ENABLE);
//  ADC_DMACmd(ADC1, ENABLE); 
//}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
