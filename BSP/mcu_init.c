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
#include "Globaldata.h"
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
void MCU_Config(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  TIM4_Config();
  USART2_Configuration();
  USART3_Configuration();
  ITC_Config();
  Pulse_Acquire_Config();
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
//  GPIO_Init(GPIOA, GPIO_Pin_All,GPIO_LOW_POWER_MODE); //GPIO端口低功耗处理
//  GPIO_Init(GPIOB, GPIO_Pin_All,GPIO_LOW_POWER_MODE);
//  GPIO_Init(GPIOC, GPIO_Pin_All,GPIO_LOW_POWER_MODE);
//  GPIO_Init(GPIOD, GPIO_Pin_All,GPIO_LOW_POWER_MODE);
//  GPIO_Init(GPIOE, GPIO_Pin_All,GPIO_LOW_POWER_MODE);
//  GPIO_Init(GPIOF, GPIO_Pin_All,GPIO_LOW_POWER_MODE); 
  
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
void TIM4_Config(void)
{ 
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4 , ENABLE);              //使能定时器4时钟
  TIM4_TimeBaseInit(TIM4_Prescaler_128 , 125);    //设置定时器4为128分频，向上计数，计数值为125即为1毫秒的计数值
  TIM4_ITConfig(TIM4_IT_Update , ENABLE);         //使能向上计数溢出中断
  TIM4_ARRPreloadConfig(ENABLE);                  //使能定时器4自动重载功能    
  TIM4_Cmd(ENABLE);                               //启动定时器4开始计数
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
void ITC_Config(void)                                                          //中断控制  0最低 3最高  
{
    ITC_SetSoftwarePriority(TIM4_UPD_OVF_TRG_IRQn, ITC_PriorityLevel_3);        //定时器4溢出优先级

    ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQn, ITC_PriorityLevel_2);  //串口2优先级
    ITC_SetSoftwarePriority(TIM2_CC_USART2_RX_IRQn, ITC_PriorityLevel_2);              //串口2优先级
    ITC_SetSoftwarePriority(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQn, ITC_PriorityLevel_1);  //串口3优先级
    ITC_SetSoftwarePriority(TIM3_CC_USART3_RX_IRQn, ITC_PriorityLevel_1);              //串口3优先级
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
void ADC_CH1_Config ( void )
{
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);   //开启ADC时钟
  ADC_Init (ADC1,ADC_ConversionMode_Continuous, 
                                          ADC_Resolution_12Bit, ADC_Prescaler_1 );         //断续模式 12位 1分频
  ADC_ChannelCmd(ADC1,ADC_Channel_1,ENABLE );         //通道选择1

  ADC_SamplingTimeConfig (ADC1,ADC_Group_FastChannels,ADC_SamplingTime_4Cycles);
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,DISABLE);   //关闭ADC时钟 
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
void ADC_CHV_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);   //开启ADC时钟
  ADC_Init (ADC1,ADC_ConversionMode_Continuous, 
                                          ADC_Resolution_8Bit, ADC_Prescaler_1 );         //断续模式 8位 1分频
  ADC_VrefintCmd (ENABLE);                                  //启动内部参考电压
  ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE );         //通道选择内部电压

  ADC_SamplingTimeConfig (ADC1,ADC_Group_FastChannels,ADC_SamplingTime_4Cycles);
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,DISABLE);   //关闭ADC时钟
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

void Read_Voltage(void)
{
  unsigned short value = 0;
  float vdd = 0;
  
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);   //开启ADC时钟
  ADC_Init (ADC1,ADC_ConversionMode_Continuous, 
                                          ADC_Resolution_8Bit, ADC_Prescaler_1 );         //断续模式 8位 1分频
  ADC_VrefintCmd (ENABLE);                                  //启动内部参考电压
  ADC_ChannelCmd(ADC1,ADC_Channel_Vrefint,ENABLE );         //通道选择内部电压

  ADC_SamplingTimeConfig (ADC1,ADC_Group_FastChannels,ADC_SamplingTime_4Cycles);

  ADC_Cmd (ADC1, ENABLE);                                       //开启ADC外围
  ADC_SoftwareStartConv (ADC1);                                 //ADC开始转换
  while(RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));        //检测ADC是否转换结束
  ADC_ClearFlag (ADC1,ADC_FLAG_EOC );                           //清除转换结束标志
  value=ADC_GetConversionValue(ADC1);                      //获取转换值
  vdd=1.224/value*256;                                    //获得VDD电压，单位V
  ADC_Cmd(ADC1, DISABLE);                                       //关闭ADC外围
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,DISABLE);       //关闭ADC时钟
  
  BAT_Vol = (unsigned short)(vdd*100);
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
