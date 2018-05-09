/* STM8L152C.h */

/* Copyright (c) 2003-2013 STMicroelectronics */

#ifndef __STM8L152C__
#define __STM8L152C__

/* STM8L152C */

	/* Check MCU name */
	#ifdef MCU_NAME
		#define STM8L152C 1
		#if (MCU_NAME != STM8L152C)
		#error "wrong include file STM8L152C.h for chosen MCU!"
		#endif
	#endif

	#ifdef __CSMC__
		#define DEF_8BIT_REG_AT(NAME,ADDRESS) volatile unsigned char NAME @ADDRESS
		#define DEF_16BIT_REG_AT(NAME,ADDRESS) volatile unsigned int NAME @ADDRESS
	#endif

	#ifdef __RAISONANCE__
		#define DEF_8BIT_REG_AT(NAME,ADDRESS) at ADDRESS hreg NAME
		#define DEF_16BIT_REG_AT(NAME,ADDRESS) at ADDRESS hreg16 NAME
	#endif

/* Port A */
/*****************************************************************/

/* Port A data output latch register */
DEF_8BIT_REG_AT(PA_ODR,0x5000);

/* Port A input pin value register */
DEF_8BIT_REG_AT(PA_IDR,0x5001);

/* Port A data direction register */
DEF_8BIT_REG_AT(PA_DDR,0x5002);

/* Port A control register 1 */
DEF_8BIT_REG_AT(PA_CR1,0x5003);

/* Port A control register 2 */
DEF_8BIT_REG_AT(PA_CR2,0x5004);

/* Port B */
/*****************************************************************/

/* Port B data output latch register */
DEF_8BIT_REG_AT(PB_ODR,0x5005);

/* Port B input pin value register */
DEF_8BIT_REG_AT(PB_IDR,0x5006);

/* Port B data direction register */
DEF_8BIT_REG_AT(PB_DDR,0x5007);

/* Port B control register 1 */
DEF_8BIT_REG_AT(PB_CR1,0x5008);

/* Port B control register 2 */
DEF_8BIT_REG_AT(PB_CR2,0x5009);

/* Port C */
/*****************************************************************/

/* Port C data output latch register */
DEF_8BIT_REG_AT(PC_ODR,0x500a);

/* Port C input pin value register */
DEF_8BIT_REG_AT(PC_IDR,0x500b);

/* Port C data direction register */
DEF_8BIT_REG_AT(PC_DDR,0x500c);

/* Port C control register 1 */
DEF_8BIT_REG_AT(PC_CR1,0x500d);

/* Port C control register 2 */
DEF_8BIT_REG_AT(PC_CR2,0x500e);

/* Port D */
/*****************************************************************/

/* Port D data output latch register */
DEF_8BIT_REG_AT(PD_ODR,0x500f);

/* Port D input pin value register */
DEF_8BIT_REG_AT(PD_IDR,0x5010);

/* Port D data direction register */
DEF_8BIT_REG_AT(PD_DDR,0x5011);

/* Port D control register 1 */
DEF_8BIT_REG_AT(PD_CR1,0x5012);

/* Port D control register 2 */
DEF_8BIT_REG_AT(PD_CR2,0x5013);

/* Port E */
/*****************************************************************/

/* Port E data output latch register */
DEF_8BIT_REG_AT(PE_ODR,0x5014);

/* Port E input pin value register */
DEF_8BIT_REG_AT(PE_IDR,0x5015);

/* Port E data direction register */
DEF_8BIT_REG_AT(PE_DDR,0x5016);

/* Port E control register 1 */
DEF_8BIT_REG_AT(PE_CR1,0x5017);

/* Port E control register 2 */
DEF_8BIT_REG_AT(PE_CR2,0x5018);

/* Port F */
/*****************************************************************/

/* Port F data output latch register */
DEF_8BIT_REG_AT(PF_ODR,0x5019);

/* Port F input pin value register */
DEF_8BIT_REG_AT(PF_IDR,0x501a);

/* Port F data direction register */
DEF_8BIT_REG_AT(PF_DDR,0x501b);

/* Port F control register 1 */
DEF_8BIT_REG_AT(PF_CR1,0x501c);

/* Port F control register 2 */
DEF_8BIT_REG_AT(PF_CR2,0x501d);

/* Flash */
/*****************************************************************/

/* Flash control register 1 */
DEF_8BIT_REG_AT(FLASH_CR1,0x5050);

/* Flash control register 2 */
DEF_8BIT_REG_AT(FLASH_CR2,0x5051);

/* Flash Program memory unprotection register */
DEF_8BIT_REG_AT(FLASH_PUKR,0x5052);

/* Data EEPROM unprotection register */
DEF_8BIT_REG_AT(FLASH_DUKR,0x5053);

/* Flash in-application programming status register */
DEF_8BIT_REG_AT(FLASH_IAPSR,0x5054);

/* Direct memory access controller 1 (DMA1) */
/*****************************************************************/

/* DMA1 global configuration & status register */
DEF_8BIT_REG_AT(DMA1_GCSR,0x5070);

/* DMA1 global interrupt register 1 */
DEF_8BIT_REG_AT(DMA1_GIR1,0x5071);

/* DMA1 channel 0 configuration register */
DEF_8BIT_REG_AT(DMA1_C0CR,0x5075);

/* DMA1 channel 0 status & priority register */
DEF_8BIT_REG_AT(DMA1_C0SPR,0x5076);

/* DMA1 number of data to transfer register (channel 0) */
DEF_8BIT_REG_AT(DMA1_C0NDTR,0x5077);

/* DMA1 peripheral address register (channel 0) */
DEF_16BIT_REG_AT(DMA1_C0PAR,0x5078);
/* DMA peripheral address high register (channel 0) */
DEF_8BIT_REG_AT(DMA1_C0PARH,0x5078);
/* DMA peripheral address low register (channel 0) */
DEF_8BIT_REG_AT(DMA1_C0PARL,0x5079);

/* DMA1 memory 0 address register (channel 0) */
DEF_16BIT_REG_AT(DMA1_C0M0AR,0x507b);
/* DMA memory address high register (channel 0) */
DEF_8BIT_REG_AT(DMA1_C0M0ARH,0x507b);
/* DMA memory address low register (channel 0) */
DEF_8BIT_REG_AT(DMA1_C0M0ARL,0x507c);

/* DMA1 channel 1 configuration register */
DEF_8BIT_REG_AT(DMA1_C1CR,0x507f);

/* DMA1 channel 1 status & priority register */
DEF_8BIT_REG_AT(DMA1_C1SPR,0x5080);

/* DMA1 number of data to transfer register (channel 1) */
DEF_8BIT_REG_AT(DMA1_C1NDTR,0x5081);

/* DMA1 peripheral address register (channel 1) */
DEF_16BIT_REG_AT(DMA1_C1PAR,0x5082);
/* DMA peripheral address high register (channel 1) */
DEF_8BIT_REG_AT(DMA1_C1PARH,0x5082);
/* DMA peripheral address low register (channel 1) */
DEF_8BIT_REG_AT(DMA1_C1PARL,0x5083);

/* DMA1 memory 0 address register (channel 1) */
DEF_16BIT_REG_AT(DMA1_C1M0AR,0x5085);
/* DMA memory address high register (channel 1) */
DEF_8BIT_REG_AT(DMA1_C1M0ARH,0x5085);
/* DMA memory address low register (channel 1) */
DEF_8BIT_REG_AT(DMA1_C1M0ARL,0x5086);

/* DMA1 channel 2 configuration register */
DEF_8BIT_REG_AT(DMA1_C2CR,0x5089);

/* DMA1 channel 2 status & priority register */
DEF_8BIT_REG_AT(DMA1_C2SPR,0x508a);

/* DMA1 number of data to transfer register (channel 2) */
DEF_8BIT_REG_AT(DMA1_C2NDTR,0x508b);

/* DMA1 peripheral address register (channel 2) */
DEF_16BIT_REG_AT(DMA1_C2PAR,0x508c);
/* DMA peripheral address high register (channel 2) */
DEF_8BIT_REG_AT(DMA1_C2PARH,0x508c);
/* DMA peripheral address low register (channel 2) */
DEF_8BIT_REG_AT(DMA1_C2PARL,0x508d);

/* DMA1 memory 0 address register (channel 2) */
DEF_16BIT_REG_AT(DMA1_C2M0AR,0x508f);
/* DMA memory address high register (channel 2) */
DEF_8BIT_REG_AT(DMA1_C2M0ARH,0x508f);
/* DMA memory address low register (channel 2) */
DEF_8BIT_REG_AT(DMA1_C2M0ARL,0x5090);

/* DMA1 channel 3 configuration register */
DEF_8BIT_REG_AT(DMA1_C3CR,0x5093);

/* DMA1 channel 3 status & priority register */
DEF_8BIT_REG_AT(DMA1_C3SPR,0x5094);

/* DMA1 number of data to transfer register (channel 3) */
DEF_8BIT_REG_AT(DMA1_C3NDTR,0x5095);

/* DMA1 peripheral address register (channel 3) */
DEF_16BIT_REG_AT(DMA1_C3PAR_C3M1AR,0x5096);
/* DMA1 peripheral address high register (channel 3) */
DEF_8BIT_REG_AT(DMA1_C3PARH_C3M1ARH,0x5096);
/* DMA1 peripheral address low register (channel 3) */
DEF_8BIT_REG_AT(DMA1_C3PARL_C3M1ARL,0x5097);

/* DMA channel 3 memory 0 extended address register */
DEF_8BIT_REG_AT(DMA_C3M0EAR,0x5098);

/* DMA1 memory 0 address register (channel 3) */
DEF_16BIT_REG_AT(DMA1_C3M0AR,0x5099);
/* DMA memory address high register (channel 3) */
DEF_8BIT_REG_AT(DMA1_C3M0ARH,0x5099);
/* DMA memory address low register (channel 3) */
DEF_8BIT_REG_AT(DMA1_C3M0ARL,0x509a);

/* System configuration (SYSCFG) */
/*****************************************************************/

/* Remapping register 3 */
DEF_8BIT_REG_AT(SYSCFG_RMPCR3,0x509d);

/* Remapping register 1 */
DEF_8BIT_REG_AT(SYSCFG_RMPCR1,0x509e);

/* Remapping register 2 */
DEF_8BIT_REG_AT(SYSCFG_RMPCR2,0x509f);

/* External Interrupt Control Register (ITC) */
/*****************************************************************/

/* External interrupt control register 1 */
DEF_8BIT_REG_AT(EXTI_CR1,0x50a0);

/* External interrupt control register 2 */
DEF_8BIT_REG_AT(EXTI_CR2,0x50a1);

/* External interrupt control register 3 */
DEF_8BIT_REG_AT(EXTI_CR3,0x50a2);

/* External interrupt status register 1 */
DEF_8BIT_REG_AT(EXTI_SR1,0x50a3);

/* External interrupt status register 2 */
DEF_8BIT_REG_AT(EXTI_SR2,0x50a4);

/* External interrupt port select register 1 */
DEF_8BIT_REG_AT(EXTI_CONF1,0x50a5);

/* Wait For Event (WFE) */
/*****************************************************************/

/* WFE control register 1 */
DEF_8BIT_REG_AT(WFE_CR1,0x50a6);

/* WFE control register 2 */
DEF_8BIT_REG_AT(WFE_CR2,0x50a7);

/* WFE control register 3 */
DEF_8BIT_REG_AT(WFE_CR3,0x50a8);

/* WFE control register 4 */
DEF_8BIT_REG_AT(WFE_CR4,0x50a9);

/* External Interrupt Control Register (ITC) */
/*****************************************************************/

/* External interrupt control register 4 */
DEF_8BIT_REG_AT(EXTI_CR4,0x50aa);

/* External interrupt port select register 2 */
DEF_8BIT_REG_AT(EXTI_CONF2,0x50ab);

/* Reset (RST) */
/*****************************************************************/

/* Reset control register */
DEF_8BIT_REG_AT(RST_CR,0x50b0);

/* Reset status register */
DEF_8BIT_REG_AT(RST_SR,0x50b1);

/* Power control (PWR) */
/*****************************************************************/

/* Power control and status register 1 */
DEF_8BIT_REG_AT(PWR_CSR1,0x50b2);

/* Power control and status register 2 */
DEF_8BIT_REG_AT(PWR_CSR2,0x50b3);

/* Clock Control (CLK) */
/*****************************************************************/

/* System clock divider register */
DEF_8BIT_REG_AT(CLK_CKDIVR,0x50c0);

/* Clock RTC register */
DEF_8BIT_REG_AT(CLK_CRTCR,0x50c1);

/* Internal clock control register */
DEF_8BIT_REG_AT(CLK_ICKCR,0x50c2);

/* Peripheral clock gating register 1 */
DEF_8BIT_REG_AT(CLK_PCKENR1,0x50c3);

/* Peripheral clock gating register 2 */
DEF_8BIT_REG_AT(CLK_PCKENR2,0x50c4);

/* Configurable clock control register */
DEF_8BIT_REG_AT(CLK_CCOR,0x50c5);

/* External clock control register */
DEF_8BIT_REG_AT(CLK_ECKCR,0x50c6);

/* System clock status register */
DEF_8BIT_REG_AT(CLK_SCSR,0x50c7);

/* System clock switch register */
DEF_8BIT_REG_AT(CLK_SWR,0x50c8);

/* Clock switch control register */
DEF_8BIT_REG_AT(CLK_SWCR,0x50c9);

/* Clock security system register */
DEF_8BIT_REG_AT(CLK_CSSR,0x50ca);

/* Clock BEEP register */
DEF_8BIT_REG_AT(CLK_CBEEPR,0x50cb);

/* HSI calibration register */
DEF_8BIT_REG_AT(CLK_HSICALR,0x50cc);

/* HSI clock calibration trimming register */
DEF_8BIT_REG_AT(CLK_HSITRIMR,0x50cd);

/* HSI unlock register */
DEF_8BIT_REG_AT(CLK_HSIUNLCKR,0x50ce);

/* Main regulator control status register */
DEF_8BIT_REG_AT(CLK_REGCSR,0x50cf);

/* Peripheral clock gating register 3 */
DEF_8BIT_REG_AT(CLK_PCKENR3,0x50d0);

/* Window Watchdog (WWDG) */
/*****************************************************************/

/* WWDG Control Register */
DEF_8BIT_REG_AT(WWDG_CR,0x50d3);

/* WWDR Window Register */
DEF_8BIT_REG_AT(WWDG_WR,0x50d4);

/* Independent Watchdog (IWDG) */
/*****************************************************************/

/* IWDG Key Register */
DEF_8BIT_REG_AT(IWDG_KR,0x50e0);

/* IWDG Prescaler Register */
DEF_8BIT_REG_AT(IWDG_PR,0x50e1);

/* IWDG Reload Register */
DEF_8BIT_REG_AT(IWDG_RLR,0x50e2);

/* Beeper (BEEP) */
/*****************************************************************/

/* BEEP Control/Status Register 1 */
DEF_8BIT_REG_AT(BEEP_CSR1,0x50f0);

/* BEEP Control/Status Register 2 */
DEF_8BIT_REG_AT(BEEP_CSR2,0x50f3);

/* Real-time clock (RTC) */
/*****************************************************************/

/* Time Register 1 */
DEF_8BIT_REG_AT(RTC_TR1,0x5140);

/* Time Register 2 */
DEF_8BIT_REG_AT(RTC_TR2,0x5141);

/* Time Register 3 */
DEF_8BIT_REG_AT(RTC_TR3,0x5142);

/* Date Register 1 */
DEF_8BIT_REG_AT(RTC_DR1,0x5144);

/* Date Register 2 */
DEF_8BIT_REG_AT(RTC_DR2,0x5145);

/* Date Register 3 */
DEF_8BIT_REG_AT(RTC_DR3,0x5146);

/* Control Register 1 */
DEF_8BIT_REG_AT(RTC_CR1,0x5148);

/* Control Register 2 */
DEF_8BIT_REG_AT(RTC_CR2,0x5149);

/* Control Register 3 */
DEF_8BIT_REG_AT(RTC_CR3,0x514a);

/* Initialization and Status Register 1 */
DEF_8BIT_REG_AT(RTC_ISR1,0x514c);

/* Initialization and Status Register 2 */
DEF_8BIT_REG_AT(RTC_ISR2,0x514d);

/* Synchronous Prescaler Register */
DEF_16BIT_REG_AT(RTC_SPRER,0x5150);
/* Synchronous Prescaler Register High */
DEF_8BIT_REG_AT(RTC_SPRERH,0x5150);
/* Synchronous Prescaler Register Low */
DEF_8BIT_REG_AT(RTC_SPRERL,0x5151);

/* Asynchronous Prescaler Register */
DEF_8BIT_REG_AT(RTC_APRER,0x5152);

/* Wakeup Timer Register */
DEF_16BIT_REG_AT(RTC_WUTR,0x5154);
/* Wakeup Timer Register High */
DEF_8BIT_REG_AT(RTC_WUTRH,0x5154);
/* Wakeup Timer Register Low */
DEF_8BIT_REG_AT(RTC_WUTRL,0x5155);

/* Subsecond Register */
DEF_16BIT_REG_AT(RTC_SSR,0x5157);
/* Subsecond Register High */
DEF_8BIT_REG_AT(RTC_SSRH,0x5157);
/* Subsecond Register Low */
DEF_8BIT_REG_AT(RTC_SSRL,0x5158);

/* Write Protection Register */
DEF_8BIT_REG_AT(RTC_WPR,0x5159);

/* Shift Register */
DEF_16BIT_REG_AT(RTC_SHIFTR,0x515a);
/* Shift Register High */
DEF_8BIT_REG_AT(RTC_SHIFTRH,0x515a);
/* Shift Register Low */
DEF_8BIT_REG_AT(RTC_SHIFTRL,0x515b);

/* Alarm A Register 1 */
DEF_8BIT_REG_AT(RTC_ALRMAR1,0x515c);

/* Alarm A Register 2 */
DEF_8BIT_REG_AT(RTC_ALRMAR2,0x515d);

/* Alarm A Register 3 */
DEF_8BIT_REG_AT(RTC_ALRMAR3,0x515e);

/* Alarm A Register 4 */
DEF_8BIT_REG_AT(RTC_ALRMAR4,0x515f);

/* Alarm A subsecond Register */
DEF_16BIT_REG_AT(RTC_ALRMASSR,0x5164);
/* Shift Register High */
DEF_8BIT_REG_AT(RTC_ALRMASSRH,0x5164);
/* Shift Register Low */
DEF_8BIT_REG_AT(RTC_ALRMASSRL,0x5165);

/* Alarm A masking Register */
DEF_8BIT_REG_AT(RTC_ALRMASSMSKR,0x5166);

/* Calibration Register */
DEF_16BIT_REG_AT(RTC_CALR,0x516a);
/* Shift Register High */
DEF_8BIT_REG_AT(RTC_CALRH,0x516a);
/* Shift Register Low */
DEF_8BIT_REG_AT(RTC_CALRL,0x516b);

/* Tamper Control Register 1 */
DEF_8BIT_REG_AT(RTC_TCR1,0x516c);

/* Tamper Control Register 2 */
DEF_8BIT_REG_AT(RTC_TCR2,0x516d);

/* Clock Security System (LSE_CSS) */
/*****************************************************************/

/* CSS on LSE Control and Status Register */
DEF_8BIT_REG_AT(CSS_LSE_CSR,0x5190);

/* Serial Peripheral Interface 1 (SPI1) */
/*****************************************************************/

/* SPI1 Control Register 1 */
DEF_8BIT_REG_AT(SPI1_CR1,0x5200);

/* SPI1 Control Register 2 */
DEF_8BIT_REG_AT(SPI1_CR2,0x5201);

/* SPI1 Interrupt Control Register */
DEF_8BIT_REG_AT(SPI1_ICR,0x5202);

/* SPI1 Status Register */
DEF_8BIT_REG_AT(SPI1_SR,0x5203);

/* SPI1 Data Register */
DEF_8BIT_REG_AT(SPI1_DR,0x5204);

/* SPI1 CRC Polynomial Register */
DEF_8BIT_REG_AT(SPI1_CRCPR,0x5205);

/* SPI1 Rx CRC Register */
DEF_8BIT_REG_AT(SPI1_RXCRCR,0x5206);

/* SPI1 Tx CRC Register */
DEF_8BIT_REG_AT(SPI1_TXCRCR,0x5207);

/* I2C Bus Interface 1 (I2C1) */
/*****************************************************************/

/* I2C1 control register 1 */
DEF_8BIT_REG_AT(I2C1_CR1,0x5210);

/* I2C1 control register 2 */
DEF_8BIT_REG_AT(I2C1_CR2,0x5211);

/* I2C1 frequency register */
DEF_8BIT_REG_AT(I2C1_FREQR,0x5212);

/* I2C1 Own address register low */
DEF_8BIT_REG_AT(I2C1_OARL,0x5213);

/* I2C1 Own address register high */
DEF_8BIT_REG_AT(I2C1_OARH,0x5214);

/* I2C1 Own address register for dual mode */
DEF_8BIT_REG_AT(I2C1_OAR2,0x5215);

/* I2C1 data register */
DEF_8BIT_REG_AT(I2C1_DR,0x5216);

/* I2C1 status register 1 */
DEF_8BIT_REG_AT(I2C1_SR1,0x5217);

/* I2C1 status register 2 */
DEF_8BIT_REG_AT(I2C1_SR2,0x5218);

/* I2C1 status register 3 */
DEF_8BIT_REG_AT(I2C1_SR3,0x5219);

/* I2C1 interrupt control register */
DEF_8BIT_REG_AT(I2C1_ITR,0x521a);

/* I2C1 Clock control register low */
DEF_8BIT_REG_AT(I2C1_CCRL,0x521b);

/* I2C1 Clock control register high */
DEF_8BIT_REG_AT(I2C1_CCRH,0x521c);

/* I2C1 TRISE register */
DEF_8BIT_REG_AT(I2C1_TRISER,0x521d);

/* I2C1 packet error checking register */
DEF_8BIT_REG_AT(I2C1_PECR,0x521e);

/* Universal synch/asynch receiver transmitter 1 (USART1) */
/*****************************************************************/

/* USART1 Status Register */
DEF_8BIT_REG_AT(USART1_SR,0x5230);

/* USART1 Data Register */
DEF_8BIT_REG_AT(USART1_DR,0x5231);

/* USART1 Baud Rate Register 1 */
DEF_8BIT_REG_AT(USART1_BRR1,0x5232);

/* USART1 Baud Rate Register 2 */
DEF_8BIT_REG_AT(USART1_BRR2,0x5233);

/* USART1 Control Register 1 */
DEF_8BIT_REG_AT(USART1_CR1,0x5234);

/* USART1 Control Register 2 */
DEF_8BIT_REG_AT(USART1_CR2,0x5235);

/* USART1 Control Register 3 */
DEF_8BIT_REG_AT(USART1_CR3,0x5236);

/* USART1 Control Register 4 */
DEF_8BIT_REG_AT(USART1_CR4,0x5237);

/* USART1 Control Register 5 */
DEF_8BIT_REG_AT(USART1_CR5,0x5238);

/* USART1 Guard time Register */
DEF_8BIT_REG_AT(USART1_GTR,0x5239);

/* USART1 Prescaler Register */
DEF_8BIT_REG_AT(USART1_PSCR,0x523a);

/* 16-Bit Timer 2 (TIM2) */
/*****************************************************************/

/* TIM2 Control register 1 */
DEF_8BIT_REG_AT(TIM2_CR1,0x5250);

/* TIM2 Control register 2 */
DEF_8BIT_REG_AT(TIM2_CR2,0x5251);

/* TIM2 Slave Mode Control register */
DEF_8BIT_REG_AT(TIM2_SMCR,0x5252);

/* TIM2 External trigger register */
DEF_8BIT_REG_AT(TIM2_ETR,0x5253);

/* TIM2 DMA request enable register */
DEF_8BIT_REG_AT(TIM2_DER,0x5254);

/* TIM2 Interrupt enable register */
DEF_8BIT_REG_AT(TIM2_IER,0x5255);

/* TIM2 Status register 1 */
DEF_8BIT_REG_AT(TIM2_SR1,0x5256);

/* TIM2 Status register 2 */
DEF_8BIT_REG_AT(TIM2_SR2,0x5257);

/* TIM2 Event Generation register */
DEF_8BIT_REG_AT(TIM2_EGR,0x5258);

/* TIM2 Capture/Compare mode register 1 */
DEF_8BIT_REG_AT(TIM2_CCMR1,0x5259);

/* TIM2 Capture/Compare mode register 2 */
DEF_8BIT_REG_AT(TIM2_CCMR2,0x525a);

/* TIM2 Capture/Compare enable register 1 */
DEF_8BIT_REG_AT(TIM2_CCER1,0x525b);

/* TIM2 Counter */
DEF_16BIT_REG_AT(TIM2_CNTR,0x525c);
/* TIM2 Counter High */
DEF_8BIT_REG_AT(TIM2_CNTRH,0x525c);
/* TIM2 Counter Low */
DEF_8BIT_REG_AT(TIM2_CNTRL,0x525d);

/* TIM2 Prescaler register */
DEF_8BIT_REG_AT(TIM2_PSCR,0x525e);

/* TIM2 Auto-reload register */
DEF_16BIT_REG_AT(TIM2_ARR,0x525f);
/* TIM2 Auto-Reload Register High */
DEF_8BIT_REG_AT(TIM2_ARRH,0x525f);
/* TIM2 Auto-Reload Register Low */
DEF_8BIT_REG_AT(TIM2_ARRL,0x5260);

/* TIM2 Capture/Compare register 1 */
DEF_16BIT_REG_AT(TIM2_CCR1,0x5261);
/* TIM2 Capture/Compare Register 1 High */
DEF_8BIT_REG_AT(TIM2_CCR1H,0x5261);
/* TIM2 Capture/Compare Register 1 Low */
DEF_8BIT_REG_AT(TIM2_CCR1L,0x5262);

/* TIM2 Capture/Compare register 2 */
DEF_16BIT_REG_AT(TIM2_CCR2,0x5263);
/* TIM2 Capture/Compare Register 2 High */
DEF_8BIT_REG_AT(TIM2_CCR2H,0x5263);
/* TIM2 Capture/Compare Register 2 Low */
DEF_8BIT_REG_AT(TIM2_CCR2L,0x5264);

/* TIM2 Break register */
DEF_8BIT_REG_AT(TIM2_BKR,0x5265);

/* TIM2 Output idle state register */
DEF_8BIT_REG_AT(TIM2_OISR,0x5266);

/* 16-Bit Timer 3 (TIM3) */
/*****************************************************************/

/* TIM3 Control register 1 */
DEF_8BIT_REG_AT(TIM3_CR1,0x5280);

/* TIM3 Control register 2 */
DEF_8BIT_REG_AT(TIM3_CR2,0x5281);

/* TIM3 Slave Mode Control register */
DEF_8BIT_REG_AT(TIM3_SMCR,0x5282);

/* TIM3 External trigger register */
DEF_8BIT_REG_AT(TIM3_ETR,0x5283);

/* TIM3 DMA request enable register */
DEF_8BIT_REG_AT(TIM3_DER,0x5284);

/* TIM3 Interrupt enable register */
DEF_8BIT_REG_AT(TIM3_IER,0x5285);

/* TIM3 Status register 1 */
DEF_8BIT_REG_AT(TIM3_SR1,0x5286);

/* TIM3 Status register 2 */
DEF_8BIT_REG_AT(TIM3_SR2,0x5287);

/* TIM3 Event Generation register */
DEF_8BIT_REG_AT(TIM3_EGR,0x5288);

/* TIM3 Capture/Compare mode register 1 */
DEF_8BIT_REG_AT(TIM3_CCMR1,0x5289);

/* TIM3 Capture/Compare mode register 2 */
DEF_8BIT_REG_AT(TIM3_CCMR2,0x528a);

/* TIM3 Capture/Compare enable register 1 */
DEF_8BIT_REG_AT(TIM3_CCER1,0x528b);

/* TIM3 Counter */
DEF_16BIT_REG_AT(TIM3_CNTR,0x528c);
/* TIM3 Counter High */
DEF_8BIT_REG_AT(TIM3_CNTRH,0x528c);
/* TIM3 Counter Low */
DEF_8BIT_REG_AT(TIM3_CNTRL,0x528d);

/* TIM3 Prescaler register */
DEF_8BIT_REG_AT(TIM3_PSCR,0x528e);

/* TIM3 Auto-reload register */
DEF_16BIT_REG_AT(TIM3_ARR,0x528f);
/* TIM3 Auto-Reload Register High */
DEF_8BIT_REG_AT(TIM3_ARRH,0x528f);
/* TIM3 Auto-Reload Register Low */
DEF_8BIT_REG_AT(TIM3_ARRL,0x5290);

/* TIM3 Capture/Compare register 1 */
DEF_16BIT_REG_AT(TIM3_CCR1,0x5291);
/* TIM3 Capture/Compare Register 1 High */
DEF_8BIT_REG_AT(TIM3_CCR1H,0x5291);
/* TIM3 Capture/Compare Register 1 Low */
DEF_8BIT_REG_AT(TIM3_CCR1L,0x5292);

/* TIM3 Capture/Compare register 2 */
DEF_16BIT_REG_AT(TIM3_CCR2,0x5293);
/* TIM3 Capture/Compare Register 2 High */
DEF_8BIT_REG_AT(TIM3_CCR2H,0x5293);
/* TIM3 Capture/Compare Register 2 Low */
DEF_8BIT_REG_AT(TIM3_CCR2L,0x5294);

/* TIM3 Break register */
DEF_8BIT_REG_AT(TIM3_BKR,0x5295);

/* TIM3 Output idle state register */
DEF_8BIT_REG_AT(TIM3_OISR,0x5296);

/* 16-Bit Timer 1 (TIM1) */
/*****************************************************************/

/* TIM1 Control register 1 */
DEF_8BIT_REG_AT(TIM1_CR1,0x52b0);

/* TIM1 Control register 2 */
DEF_8BIT_REG_AT(TIM1_CR2,0x52b1);

/* TIM1 Slave Mode Control register */
DEF_8BIT_REG_AT(TIM1_SMCR,0x52b2);

/* TIM1 external trigger register */
DEF_8BIT_REG_AT(TIM1_ETR,0x52b3);

/* TIM1 DMA request enable register */
DEF_8BIT_REG_AT(TIM1_DER,0x52b4);

/* TIM1 Interrupt enable register */
DEF_8BIT_REG_AT(TIM1_IER,0x52b5);

/* TIM1 Status register 1 */
DEF_8BIT_REG_AT(TIM1_SR1,0x52b6);

/* TIM1 Status register 2 */
DEF_8BIT_REG_AT(TIM1_SR2,0x52b7);

/* TIM1 Event Generation register */
DEF_8BIT_REG_AT(TIM1_EGR,0x52b8);

/* TIM1 Capture/Compare mode register 1 */
DEF_8BIT_REG_AT(TIM1_CCMR1,0x52b9);

/* TIM1 Capture/Compare mode register 2 */
DEF_8BIT_REG_AT(TIM1_CCMR2,0x52ba);

/* TIM1 Capture/Compare mode register 3 */
DEF_8BIT_REG_AT(TIM1_CCMR3,0x52bb);

/* TIM1 Capture/Compare mode register 4 */
DEF_8BIT_REG_AT(TIM1_CCMR4,0x52bc);

/* TIM1 Capture/Compare enable register 1 */
DEF_8BIT_REG_AT(TIM1_CCER1,0x52bd);

/* TIM1 Capture/Compare enable register 2 */
DEF_8BIT_REG_AT(TIM1_CCER2,0x52be);

/* TIM1 Counter */
DEF_16BIT_REG_AT(TIM1_CNTR,0x52bf);
/* TIM1 Counter High */
DEF_8BIT_REG_AT(TIM1_CNTRH,0x52bf);
/* TIM1 Counter Low */
DEF_8BIT_REG_AT(TIM1_CNTRL,0x52c0);

/* TIM1 Prescaler register */
DEF_16BIT_REG_AT(TIM1_PSCR,0x52c1);
/* TIM1 Prescaler Register High */
DEF_8BIT_REG_AT(TIM1_PSCRH,0x52c1);
/* TIM1 Prescaler Register Low */
DEF_8BIT_REG_AT(TIM1_PSCRL,0x52c2);

/* TIM1 Auto-reload register */
DEF_16BIT_REG_AT(TIM1_ARR,0x52c3);
/* TIM1 Auto-Reload Register High */
DEF_8BIT_REG_AT(TIM1_ARRH,0x52c3);
/* TIM1 Auto-Reload Register Low */
DEF_8BIT_REG_AT(TIM1_ARRL,0x52c4);

/* TIM1 Repetition counter register */
DEF_8BIT_REG_AT(TIM1_RCR,0x52c5);

/* TIM1 Capture/Compare register 1 */
DEF_16BIT_REG_AT(TIM1_CCR1,0x52c6);
/* TIM1 Capture/Compare Register 1 High */
DEF_8BIT_REG_AT(TIM1_CCR1H,0x52c6);
/* TIM1 Capture/Compare Register 1 Low */
DEF_8BIT_REG_AT(TIM1_CCR1L,0x52c7);

/* TIM1 Capture/Compare register 2 */
DEF_16BIT_REG_AT(TIM1_CCR2,0x52c8);
/* TIM1 Capture/Compare Register 2 High */
DEF_8BIT_REG_AT(TIM1_CCR2H,0x52c8);
/* TIM1 Capture/Compare Register 2 Low */
DEF_8BIT_REG_AT(TIM1_CCR2L,0x52c9);

/* TIM1 Capture/Compare register 3 */
DEF_16BIT_REG_AT(TIM1_CCR3,0x52ca);
/* TIM1 Capture/Compare Register 3 High */
DEF_8BIT_REG_AT(TIM1_CCR3H,0x52ca);
/* TIM1 Capture/Compare Register 3 Low */
DEF_8BIT_REG_AT(TIM1_CCR3L,0x52cb);

/* TIM1 Capture/Compare register 4 */
DEF_16BIT_REG_AT(TIM1_CCR4,0x52cc);
/* TIM1 Capture/Compare Register 4 High */
DEF_8BIT_REG_AT(TIM1_CCR4H,0x52cc);
/* TIM1 Capture/Compare Register 4 Low */
DEF_8BIT_REG_AT(TIM1_CCR4L,0x52cd);

/* TIM1 Break register */
DEF_8BIT_REG_AT(TIM1_BKR,0x52ce);

/* TIM1 Dead-time register */
DEF_8BIT_REG_AT(TIM1_DTR,0x52cf);

/* TIM1 Output idle state register */
DEF_8BIT_REG_AT(TIM1_OISR,0x52d0);

/* TIM1 DMA1 control register 1 */
DEF_8BIT_REG_AT(TIM1_DCR1,0x52d1);

/* TIM1 DMA1 control register 2 */
DEF_8BIT_REG_AT(TIM1_DCR2,0x52d2);

/* TIM1 DMA1 address for burst mode */
DEF_8BIT_REG_AT(TIM1_DMA1R,0x52d3);

/* 8-Bit  Timer 4 (TIM4) */
/*****************************************************************/

/* TIM4 Control Register 1 */
DEF_8BIT_REG_AT(TIM4_CR1,0x52e0);

/* TIM4 Control Register 2 */
DEF_8BIT_REG_AT(TIM4_CR2,0x52e1);

/* TIM4 Slave Mode Control Register */
DEF_8BIT_REG_AT(TIM4_SMCR,0x52e2);

/* TIM4 DMA request Enable Register */
DEF_8BIT_REG_AT(TIM4_DER,0x52e3);

/* TIM4 Interrupt Enable Register */
DEF_8BIT_REG_AT(TIM4_IER,0x52e4);

/* TIM4 Status Register 1 */
DEF_8BIT_REG_AT(TIM4_SR1,0x52e5);

/* TIM4 Event Generation Register */
DEF_8BIT_REG_AT(TIM4_EGR,0x52e6);

/* TIM4 Counter */
DEF_8BIT_REG_AT(TIM4_CNTR,0x52e7);

/* TIM4 Prescaler Register */
DEF_8BIT_REG_AT(TIM4_PSCR,0x52e8);

/* TIM4 Auto-Reload Register */
DEF_8BIT_REG_AT(TIM4_ARR,0x52e9);

/* Infra Red Interface (IR) */
/*****************************************************************/

/* Infra-red control register */
DEF_8BIT_REG_AT(IR_CR,0x52ff);

/* 16-Bit  Timer 5 (TIM5) */
/*****************************************************************/

/* TIM5 Control register 1 */
DEF_8BIT_REG_AT(TIM5_CR1,0x5300);

/* TIM5 Control register 2 */
DEF_8BIT_REG_AT(TIM5_CR2,0x5301);

/* TIM5 Slave Mode Control register */
DEF_8BIT_REG_AT(TIM5_SMCR,0x5302);

/* TIM5 External trigger register */
DEF_8BIT_REG_AT(TIM5_ETR,0x5303);

/* TIM5 DMA request enable register */
DEF_8BIT_REG_AT(TIM5_DER,0x5304);

/* TIM5 Interrupt enable register */
DEF_8BIT_REG_AT(TIM5_IER,0x5305);

/* TIM5 Status register 1 */
DEF_8BIT_REG_AT(TIM5_SR1,0x5306);

/* TIM5 Status register 2 */
DEF_8BIT_REG_AT(TIM5_SR2,0x5307);

/* TIM5 Event Generation register */
DEF_8BIT_REG_AT(TIM5_EGR,0x5308);

/* TIM5 Capture/Compare mode register 1 */
DEF_8BIT_REG_AT(TIM5_CCMR1,0x5309);

/* TIM5 Capture/Compare mode register 2 */
DEF_8BIT_REG_AT(TIM5_CCMR2,0x530a);

/* TIM5 Capture/Compare enable register 1 */
DEF_8BIT_REG_AT(TIM5_CCER1,0x530b);

/* TIM5 Counter */
DEF_16BIT_REG_AT(TIM5_CNTR,0x530c);
/* TIM5 Counter High */
DEF_8BIT_REG_AT(TIM5_CNTRH,0x530c);
/* TIM5 Counter Low */
DEF_8BIT_REG_AT(TIM5_CNTRL,0x530d);

/* TIM5 Prescaler register */
DEF_8BIT_REG_AT(TIM5_PSCR,0x530e);

/* TIM5 Auto-reload register */
DEF_16BIT_REG_AT(TIM5_ARR,0x530f);
/* TIM5 Auto-Reload Register High */
DEF_8BIT_REG_AT(TIM5_ARRH,0x530f);
/* TIM5 Auto-Reload Register Low */
DEF_8BIT_REG_AT(TIM5_ARRL,0x5310);

/* TIM5 Capture/Compare register 1 */
DEF_16BIT_REG_AT(TIM5_CCR1,0x5311);
/* TIM5 Capture/Compare Register 1 High */
DEF_8BIT_REG_AT(TIM5_CCR1H,0x5311);
/* TIM5 Capture/Compare Register 1 Low */
DEF_8BIT_REG_AT(TIM5_CCR1L,0x5312);

/* TIM5 Capture/Compare register 2 */
DEF_16BIT_REG_AT(TIM5_CCR2,0x5313);
/* TIM5 Capture/Compare Register 2 High */
DEF_8BIT_REG_AT(TIM5_CCR2H,0x5313);
/* TIM5 Capture/Compare Register 2 Low */
DEF_8BIT_REG_AT(TIM5_CCR2L,0x5314);

/* TIM5 Break register */
DEF_8BIT_REG_AT(TIM5_BKR,0x5315);

/* TIM5 Output idle state register */
DEF_8BIT_REG_AT(TIM5_OISR,0x5316);

/* Analog to digital converter 1 (ADC1) */
/*****************************************************************/

/* ADC1 Configuration register 1 */
DEF_8BIT_REG_AT(ADC1_CR1,0x5340);

/* ADC1 Configuration register 2 */
DEF_8BIT_REG_AT(ADC1_CR2,0x5341);

/* ADC1 Configuration register 3 */
DEF_8BIT_REG_AT(ADC1_CR3,0x5342);

/* ADC1 status register */
DEF_8BIT_REG_AT(ADC1_SR,0x5343);

/* ADC1 Data register */
DEF_16BIT_REG_AT(ADC1_DR,0x5344);
/* ADC Data Register High */
DEF_8BIT_REG_AT(ADC1_DRH,0x5344);
/* ADC Data Register Low */
DEF_8BIT_REG_AT(ADC1_DRL,0x5345);

/* ADC1 high threshold register */
DEF_16BIT_REG_AT(ADC1_HTR,0x5346);
/* ADC High Threshold Register High */
DEF_8BIT_REG_AT(ADC1_HTRH,0x5346);
/* ADC High Threshold Register Low */
DEF_8BIT_REG_AT(ADC1_HTRL,0x5347);

/* ADC1 low threshold register */
DEF_16BIT_REG_AT(ADC1_LTR,0x5348);
/* ADC Low Threshold Register High */
DEF_8BIT_REG_AT(ADC1_LTRH,0x5348);
/* ADC Low Threshold Register Low */
DEF_8BIT_REG_AT(ADC1_LTRL,0x5349);

/* ADC1 channel sequence 1 register */
DEF_8BIT_REG_AT(ADC1_SQR1,0x534a);

/* ADC1 channel sequence 2 register */
DEF_8BIT_REG_AT(ADC1_SQR2,0x534b);

/* ADC1 channel sequence 3 register */
DEF_8BIT_REG_AT(ADC1_SQR3,0x534c);

/* ADC1 channel sequence 4 register */
DEF_8BIT_REG_AT(ADC1_SQR4,0x534d);

/* ADC1 Trigger disable 1 */
DEF_8BIT_REG_AT(ADC1_TRIGR1,0x534e);

/* ADC1 Trigger disable 2 */
DEF_8BIT_REG_AT(ADC1_TRIGR2,0x534f);

/* ADC1 Trigger disable 3 */
DEF_8BIT_REG_AT(ADC1_TRIGR3,0x5350);

/* ADC1 Trigger disable 4 */
DEF_8BIT_REG_AT(ADC1_TRIGR4,0x5351);

/* Digital to analog converter (DAC) */
/*****************************************************************/

/* DAC channel 1 control register 1 */
DEF_8BIT_REG_AT(DAC_CH1CR1,0x5380);

/* DAC channel 1 control register 2 */
DEF_8BIT_REG_AT(DAC_CH1CR2,0x5381);

/* DAC channel 2 control register 1 */
DEF_8BIT_REG_AT(DAC_CH2CR1,0x5382);

/* DAC channel 2 control register 2 */
DEF_8BIT_REG_AT(DAC_CH2CR2,0x5383);

/* DAC software trigger register */
DEF_8BIT_REG_AT(DAC_SWTRIGR,0x5384);

/* DAC status register */
DEF_8BIT_REG_AT(DAC_SR,0x5385);

/* DAC channel 1 right aligned data holding register */
DEF_16BIT_REG_AT(DAC_CH1RDHR,0x5388);
/* DAC channel 1 right aligned data holding register high */
DEF_8BIT_REG_AT(DAC_CH1RDHRH,0x5388);
/* DAC channel 1 right aligned data holding register low */
DEF_8BIT_REG_AT(DAC_CH1RDHRL,0x5389);

/* DAC channel 1 left aligned data holding register */
DEF_16BIT_REG_AT(DAC_CH1LDHR,0x538c);
/* DAC channel 1 left aligned data holding register high */
DEF_8BIT_REG_AT(DAC_CH1LDHRH,0x538c);
/* DAC channel 1 left aligned data holding register low */
DEF_8BIT_REG_AT(DAC_CH1LDHRL,0x538d);

/* DAC channel 1 8-bit data holding register */
DEF_8BIT_REG_AT(DAC_CH1DHR8,0x5390);

/* DAC channel 2 right aligned data holding register */
DEF_16BIT_REG_AT(DAC_CH2RDHR,0x5394);
/* DAC channel 2 right aligned data holding register high */
DEF_8BIT_REG_AT(DAC_CH2RDHRH,0x5394);
/* DAC channel 2 right aligned data holding register low */
DEF_8BIT_REG_AT(DAC_CH2RDHRL,0x5395);

/* DAC channel 2 left aligned data holding register */
DEF_16BIT_REG_AT(DAC_CH2LDHR,0x5398);
/* DAC channel 2 left aligned data holding register high */
DEF_8BIT_REG_AT(DAC_CH2LDHRH,0x5398);
/* DAC channel 2 left aligned data holding register low */
DEF_8BIT_REG_AT(DAC_CH2LDHRL,0x5399);

/* DAC channel 2 8-bit data holding register */
DEF_8BIT_REG_AT(DAC_CH2DHR8,0x539c);

/* DAC channel 1 right aligned data holding register */
DEF_16BIT_REG_AT(DAC_DCH1RDHR,0x53a0);
/* DAC channel 1 right aligned data holding register high */
DEF_8BIT_REG_AT(DAC_DCH1RDHRH,0x53a0);
/* DAC channel 1 right aligned data holding register low */
DEF_8BIT_REG_AT(DAC_DCH1RDHRL,0x53a1);

/* DAC channel 2 right aligned data holding register */
DEF_16BIT_REG_AT(DAC_DCH2RDHR,0x53a2);
/* DAC channel 2 right aligned data holding register high */
DEF_8BIT_REG_AT(DAC_DCH2RDHRH,0x53a2);
/* DAC channel 2 right aligned data holding register low */
DEF_8BIT_REG_AT(DAC_DCH2RDHRL,0x53a3);

/* DAC channel 1 left aligned data holding register */
DEF_16BIT_REG_AT(DAC_DCH1LDHR,0x53a4);
/* DAC channel 1 left aligned data holding register high */
DEF_8BIT_REG_AT(DAC_DCH1LDHRH,0x53a4);
/* DAC channel 1 left aligned data holding register low */
DEF_8BIT_REG_AT(DAC_DCH1LDHRL,0x53a5);

/* DAC channel 2 left aligned data holding register */
DEF_16BIT_REG_AT(DAC_DCH2LDHR,0x53a6);
/* DAC channel 2 left aligned data holding register high */
DEF_8BIT_REG_AT(DAC_DCH2LDHRH,0x53a6);
/* DAC channel 2 left aligned data holding register low */
DEF_8BIT_REG_AT(DAC_DCH2LDHRL,0x53a7);

/* DAC channel 1 8-bit data holding register */
DEF_8BIT_REG_AT(DAC_DCH1DHR8,0x53a8);

/* DAC channel 2 8-bit data holding register */
DEF_8BIT_REG_AT(DAC_DCH2DHR8,0x53a9);

/* DAC channel 1 data output register */
DEF_16BIT_REG_AT(DAC_CH1DOR,0x53ac);
/* DAC channel 1 data output register high */
DEF_8BIT_REG_AT(DAC_CH1DORH,0x53ac);
/* DAC channel 1 data output register low */
DEF_8BIT_REG_AT(DAC_CH1DORL,0x53ad);

/* DAC channel 2 data output register */
DEF_16BIT_REG_AT(DAC_CH2DOR,0x53b0);
/* DAC channel 2 data output register high */
DEF_8BIT_REG_AT(DAC_CH2DORH,0x53b0);
/* DAC channel 2 data output register low */
DEF_8BIT_REG_AT(DAC_CH2DORL,0x53b1);

/* Serial Peripheral Interface 2 (SPI2) */
/*****************************************************************/

/* SPI2 Control Register 1 */
DEF_8BIT_REG_AT(SPI2_CR1,0x53c0);

/* SPI2 Control Register 2 */
DEF_8BIT_REG_AT(SPI2_CR2,0x53c1);

/* SPI2 Interrupt Control Register */
DEF_8BIT_REG_AT(SPI2_ICR,0x53c2);

/* SPI2 Status Register */
DEF_8BIT_REG_AT(SPI2_SR,0x53c3);

/* SPI2 Data Register */
DEF_8BIT_REG_AT(SPI2_DR,0x53c4);

/* SPI2 CRC Polynomial Register */
DEF_8BIT_REG_AT(SPI2_CRCPR,0x53c5);

/* SPI2 Rx CRC Register */
DEF_8BIT_REG_AT(SPI2_RXCRCR,0x53c6);

/* SPI2 Tx CRC Register */
DEF_8BIT_REG_AT(SPI2_TXCRCR,0x53c7);

/* Universal synch/asynch receiver transmitter 2 (USART2) */
/*****************************************************************/

/* USART2 Status Register */
DEF_8BIT_REG_AT(USART2_SR,0x53e0);

/* USART2 Data Register */
DEF_8BIT_REG_AT(USART2_DR,0x53e1);

/* USART2 Baud Rate Register 1 */
DEF_8BIT_REG_AT(USART2_BRR1,0x53e2);

/* USART2 Baud Rate Register 2 */
DEF_8BIT_REG_AT(USART2_BRR2,0x53e3);

/* USART2 Control Register 1 */
DEF_8BIT_REG_AT(USART2_CR1,0x53e4);

/* USART2 Control Register 2 */
DEF_8BIT_REG_AT(USART2_CR2,0x53e5);

/* USART2 Control Register 3 */
DEF_8BIT_REG_AT(USART2_CR3,0x53e6);

/* USART2 Control Register 4 */
DEF_8BIT_REG_AT(USART2_CR4,0x53e7);

/* USART2 Control Register 5 */
DEF_8BIT_REG_AT(USART2_CR5,0x53e8);

/* USART2 Guard time Register */
DEF_8BIT_REG_AT(USART2_GTR,0x53e9);

/* USART2 Prescaler Register */
DEF_8BIT_REG_AT(USART2_PSCR,0x53ea);

/* Universal synch/asynch receiver transmitter 3 (USART3) */
/*****************************************************************/

/* USART3 Status Register */
DEF_8BIT_REG_AT(USART3_SR,0x53f0);

/* USART3 Data Register */
DEF_8BIT_REG_AT(USART3_DR,0x53f1);

/* USART3 Baud Rate Register 1 */
DEF_8BIT_REG_AT(USART3_BRR1,0x53f2);

/* USART3 Baud Rate Register 2 */
DEF_8BIT_REG_AT(USART3_BRR2,0x53f3);

/* USART3 Control Register 1 */
DEF_8BIT_REG_AT(USART3_CR1,0x53f4);

/* USART3 Control Register 2 */
DEF_8BIT_REG_AT(USART3_CR2,0x53f5);

/* USART3 Control Register 3 */
DEF_8BIT_REG_AT(USART3_CR3,0x53f6);

/* USART3 Control Register 4 */
DEF_8BIT_REG_AT(USART3_CR4,0x53f7);

/* USART3 Control Register 5 */
DEF_8BIT_REG_AT(USART3_CR5,0x53f8);

/* USART3 Guard time Register */
DEF_8BIT_REG_AT(USART3_GTR,0x53f9);

/* USART3 Prescaler Register */
DEF_8BIT_REG_AT(USART3_PSCR,0x53fa);

/* LCD controller (LCD) */
/*****************************************************************/

/* LCD control register 1 */
DEF_8BIT_REG_AT(LCD_CR1,0x5400);

/* LCD control register 2 */
DEF_8BIT_REG_AT(LCD_CR2,0x5401);

/* LCD control register 3 */
DEF_8BIT_REG_AT(LCD_CR3,0x5402);

/* LCD frequency selection register */
DEF_8BIT_REG_AT(LCD_FRQ,0x5403);

/* LCD Port mask register 0 */
DEF_8BIT_REG_AT(LCD_PM0,0x5404);

/* LCD Port mask register 1 */
DEF_8BIT_REG_AT(LCD_PM1,0x5405);

/* LCD Port mask register 2 */
DEF_8BIT_REG_AT(LCD_PM2,0x5406);

/* LCD Port mask register 3 */
DEF_8BIT_REG_AT(LCD_PM3,0x5407);

/* LCD Port mask register 4 */
DEF_8BIT_REG_AT(LCD_PM4,0x5408);

/* LCD Port mask register 5 */
DEF_8BIT_REG_AT(LCD_PM5,0x5409);

/* LCD display memory 0 */
DEF_8BIT_REG_AT(LCD_RAM0,0x540c);

/* LCD display memory 1 */
DEF_8BIT_REG_AT(LCD_RAM1,0x540d);

/* LCD display memory 2 */
DEF_8BIT_REG_AT(LCD_RAM2,0x540e);

/* LCD display memory 3 */
DEF_8BIT_REG_AT(LCD_RAM3,0x540f);

/* LCD display memory 4 */
DEF_8BIT_REG_AT(LCD_RAM4,0x5410);

/* LCD display memory 5 */
DEF_8BIT_REG_AT(LCD_RAM5,0x5411);

/* LCD display memory 6 */
DEF_8BIT_REG_AT(LCD_RAM6,0x5412);

/* LCD display memory 7 */
DEF_8BIT_REG_AT(LCD_RAM7,0x5413);

/* LCD display memory 8 */
DEF_8BIT_REG_AT(LCD_RAM8,0x5414);

/* LCD display memory 9 */
DEF_8BIT_REG_AT(LCD_RAM9,0x5415);

/* LCD display memory 10 */
DEF_8BIT_REG_AT(LCD_RAM10,0x5416);

/* LCD display memory 11 */
DEF_8BIT_REG_AT(LCD_RAM11,0x5417);

/* LCD display memory 12 */
DEF_8BIT_REG_AT(LCD_RAM12,0x5418);

/* LCD display memory 13 */
DEF_8BIT_REG_AT(LCD_RAM13,0x5419);

/* LCD display memory 14 */
DEF_8BIT_REG_AT(LCD_RAM14,0x541a);

/* LCD display memory 15 */
DEF_8BIT_REG_AT(LCD_RAM15,0x541b);

/* LCD display memory 16 */
DEF_8BIT_REG_AT(LCD_RAM16,0x541c);

/* LCD display memory 17 */
DEF_8BIT_REG_AT(LCD_RAM17,0x541d);

/* LCD display memory 18 */
DEF_8BIT_REG_AT(LCD_RAM18,0x541e);

/* LCD display memory 19 */
DEF_8BIT_REG_AT(LCD_RAM19,0x541f);

/* LCD display memory 20 */
DEF_8BIT_REG_AT(LCD_RAM20,0x5420);

/* LCD display memory 21 */
DEF_8BIT_REG_AT(LCD_RAM21,0x5421);

/* LCD control register 4 */
DEF_8BIT_REG_AT(LCD_CR4,0x542f);

/* Routing interface (RI) */
/*****************************************************************/

/* Timer input capture routing register 1 */
DEF_8BIT_REG_AT(RI_ICR1,0x5431);

/* Timer input capture routing register 2 */
DEF_8BIT_REG_AT(RI_ICR2,0x5432);

/* I/O input register 1 */
DEF_8BIT_REG_AT(RI_IOIR1,0x5433);

/* I/O input register 2 */
DEF_8BIT_REG_AT(RI_IOIR2,0x5434);

/* I/O input register 3 */
DEF_8BIT_REG_AT(RI_IOIR3,0x5435);

/* I/O control mode register 1 */
DEF_8BIT_REG_AT(RI_IOCMR1,0x5436);

/* I/O control mode register 2 */
DEF_8BIT_REG_AT(RI_IOCMR2,0x5437);

/* I/O control mode register 3 */
DEF_8BIT_REG_AT(RI_IOCMR3,0x5438);

/* I/O switch register 1 */
DEF_8BIT_REG_AT(RI_IOSR1,0x5439);

/* I/O switch register 2 */
DEF_8BIT_REG_AT(RI_IOSR2,0x543a);

/* I/O switch register 3 */
DEF_8BIT_REG_AT(RI_IOSR3,0x543b);

/* I/O group control register */
DEF_8BIT_REG_AT(RI_IOGCR,0x543c);

/* Analog switch register 1 */
DEF_8BIT_REG_AT(RI_ASCR1,0x543d);

/* Analog switch register 2 */
DEF_8BIT_REG_AT(RI_ASCR2,0x543e);

/* Resistor control register */
DEF_8BIT_REG_AT(RI_RCR,0x543f);

/* Comparators (COMP) */
/*****************************************************************/

/* Comparator control and status register 1 */
DEF_8BIT_REG_AT(COMP_CSR1,0x5440);

/* Comparator control and status register 2 */
DEF_8BIT_REG_AT(COMP_CSR2,0x5441);

/* Comparator control and status register 3 */
DEF_8BIT_REG_AT(COMP_CSR3,0x5442);

/* Comparator control and status register 4 */
DEF_8BIT_REG_AT(COMP_CSR4,0x5443);

/* Comparator control and status register 5 */
DEF_8BIT_REG_AT(COMP_CSR5,0x5444);

/* Global configuration register (CFG) */
/*****************************************************************/

/* CFG Global configuration register */
DEF_8BIT_REG_AT(CFG_GCR,0x7f60);

/* Interrupt Software Priority Registers (ITC) */
/*****************************************************************/

/* Interrupt Software priority register 1 */
DEF_8BIT_REG_AT(ITC_SPR1,0x7f70);

/* Interrupt Software priority register 2 */
DEF_8BIT_REG_AT(ITC_SPR2,0x7f71);

/* Interrupt Software priority register 3 */
DEF_8BIT_REG_AT(ITC_SPR3,0x7f72);

/* Interrupt Software priority register 4 */
DEF_8BIT_REG_AT(ITC_SPR4,0x7f73);

/* Interrupt Software priority register 5 */
DEF_8BIT_REG_AT(ITC_SPR5,0x7f74);

/* Interrupt Software priority register 6 */
DEF_8BIT_REG_AT(ITC_SPR6,0x7f75);

/* Interrupt Software priority register 7 */
DEF_8BIT_REG_AT(ITC_SPR7,0x7f76);

/* Interrupt Software priority register 8 */
DEF_8BIT_REG_AT(ITC_SPR8,0x7f77);

#endif /* __STM8L152C__ */
