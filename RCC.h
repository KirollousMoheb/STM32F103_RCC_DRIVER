/******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC.h
 *
 * Description: Header file for the STM32F103XX RCC driver
 *
 * Author: Kirollous Moheb
 *
 *******************************************************************************/
#ifndef _rcc_h
#define _rcc_h
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                                HSI Config		                               *
 *******************************************************************************/
/* Choose HSI as system CLK */
#define Enable_HSI						0
/*******************************************************************************
 *                                HSE Config		                               *
 *******************************************************************************/
/* Choose HSE as system CLK */
#define Enable_HSE						1
/*******************************************************************************
 *                                PLL Config		                               *
 *******************************************************************************/
/* Choose PLL as system CLK */
#define Enable_PLL						0
#if(Enable_PLL)
/*Select PLL CLK*/
#define PLL_CLK							HSE
/*Select PLL Multiplier*/
#define PLL_Multiplication		PLL_input_clock_x16
#endif
/*******************************************************************************
 *                                LSI Config		                               *
 *******************************************************************************/
#define Enable_LSI						0
/*******************************************************************************
 *                                LSE Config		                               *
 *******************************************************************************/
#define Enable_LSE						0
/*******************************************************************************
 *                                RTC Config		                               *
 *******************************************************************************/
#define Enable_RTC						0
/*******************************************************************************
 *                                AHB Config		                               *
 *******************************************************************************/
#define Enable_AHB						0
#if(Enable_AHB)
#define AHB_Prescaler			AHB_SYSCLK_not_divided
#endif
/*******************************************************************************
 *                                APB1 Config		                               *
 *******************************************************************************/
#define Enable_APB1						0
#if(Enable_AHB)
#define APB1_Prescaler			APB1_HCLK_not_divided
#endif
/*******************************************************************************
 *                                APB2 Config		                               *
 *******************************************************************************/
#define Enable_APB2						0
#if(Enable_AHB)
#define APB2_Prescaler			APB2_HCLK_not_divided
#endif
/*******************************************************************************
 *                                MCO Config		                               *
 *******************************************************************************/
#define Enable_MCO						0
#if(Enable_MCO)
#define MCO_Prescaler		MCO_OLL
#endif
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/*MCO CLOCK PRESCALER*/
typedef enum {
	MCO_NO_CLOCK=0,
	MCO_SYSCLK=4,
	MCO_HSI=5,
	MCO_HSE=6,
	MCO_OLL=7
}MCO_CLOCK;
/*PLL CLOCK MULTIPLIER*/
typedef enum {
	PLL_input_clock_x2,
	PLL_input_clock_x3,
	PLL_input_clock_x4,
	PLL_input_clock_x5,
	PLL_input_clock_x6,
	PLL_input_clock_x7,
	PLL_input_clock_x8,
	PLL_input_clock_x9,
	PLL_input_clock_x10,
	PLL_input_clock_x11,
	PLL_input_clock_x12,
	PLL_input_clock_x13,
	PLL_input_clock_x14,
	PLL_input_clock_x15,
	PLL_input_clock_x16,
}PLL_MULTIPLIER;
/*PLL CLOCK SOURCE*/
typedef enum {
	Half_HSI,HSE	
}PLL_CLOCK;
/*AHB CLOCK PRESCALER*/
typedef enum {
	AHB_SYSCLK_not_divided,
	AHB_SYSCLK_divided_by_2 = 8,
	AHB_SYSCLK_divided_by_4,
	AHB_SYSCLK_divided_by_8,
	AHB_SYSCLK_divided_by_16,
	AHB_SYSCLK_divided_by_64,
	AHB_SYSCLK_divided_by_128,
	AHB_SYSCLK_divided_by_256,
	AHB_SYSCLK_divided_by_512
}AHB_PRESCALER;
/*APB1 CLOCK PRESCALER*/
typedef enum {
	APB1_HCLK_not_divided,
	APB1_HCLK_divided_by_2 = 4,
	APB1_HCLK_divided_by_4,
	APB1_HCLK_divided_by_8,
	APB1_HCLK_divided_by_16
}APB1_PRESCALER;
/*APB2 CLOCK PRESCALER*/
typedef enum {

	APB2_HCLK_not_divided,
	APB2_HCLK_divided_by_2 = 4,
	APB2_HCLK_divided_by_4,
	APB2_HCLK_divided_by_8,
	APB2_HCLK_divided_by_16
}APB2_PRESCALER;
/*AHB PERIPHERALS Enable ID*/
typedef enum {
	DMA1EN,DMA2EN,SRAMEN,FLITFEN=4,CRCEN=6,FSMCEN=8,SDIOEN=10
}AHB_PERIPHERAL_CLOCK_ENABLE_DISABLE;
/*APB1 PERIPHERALS Enable ID*/
typedef enum {
	TIM2EN,TIM3EN,TIM4EN,TIM5EN,TIM6EN,TIM7EN,WWDGEN=11,SPI2EN=14,SPI3EN,
	USART2EN=17,USART3EN,USART4EN,USART5EN,I2C1EN,I2C2EN,USBEN,CANEN=25,BKPEN=27,
	PWREN,DACEN
}APB1_PERIPHERAL_CLOCK_ENABLE_DISABLE;
/*APB2 PERIPHERALS ENABLE ID*/
typedef enum {
	AFIOEN,IOPAEN=2,IOPBEN,IOPCEN,IOPDEN,IOPEEN,IOPFEN,IOPGEN,ADC1EN,ADC2EN,TIM1EN,SPI1EN,TIM8EN,USART1EN,ADC3EN
}APB2_PERIPHERAL_CLOCK_ENABLE_DISABLE;
/*APB1 PERIPHERALS RESET ID*/
typedef enum{
	TIM2RST,TIM3RST,TIM4RST,TIM5RST,TIM6RST,TIM7RST,WWDGRST=11,SPI2RST=14,SPI3RST,USART2RST=17,
	USART3RST,UART4RST,UART5RST,I2C1RST,I2C2RST,USBRST,CANRST=25,BKPRST=27,PWRRST,DACRST
}APB1_PERIPHERAL_RESET;
/*APB2 PERIPHERALS RESET ID*/
typedef enum{
	AFIORST,IOPARST=2,IOPBRST,IOPCRST,IOPDRST,IOPERST,IOPFRST,IOPGRST,ADC1RST,
	ADC2RST,TIM1RST,SPI1RST,TIM8RST,USART1RST,ADC3RST
}APB2_PERIPHERAL_RESET;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/***************************************************************************************************
 * [Function Name]:          RCC_enableHSI
 *
 * [Description]:            Configure RCC module to operate in HSI(High Speed Internal) mode.
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableHSI(void);
/***************************************************************************************************
 * [Function Name]:          RCC_enableHSE
 *
 * [Description]:            Configure RCC module to operate in HSE(High Speed External) mode.
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableHSE(void);
/***************************************************************************************************
 * [Function Name]:          RCC_enablePLL
 *
 * [Description]:            Configure RCC module to operate in PLL(Phase Locked Loop) mode.
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enablePLL(uint8 PLL_multiplication_factor,uint8 PLL_CLOCK);
/***************************************************************************************************
 * [Function Name]:          RCC_enableLSI
 *
 * [Description]:            Configure RCC module to operate in LSI(Low Speed Internal) mode.
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableLSI(void);
/***************************************************************************************************
 * [Function Name]:          RCC_enableLSE
 *
 * [Description]:            Configure RCC module to operate in LSE(Low Speed External) mode.
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableLSE(void);
/***************************************************************************************************
 * [Function Name]:          RCC_enableRTC
 *
 * [Description]:            Enable RTC (Real time clock)module of the microcontroller
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableRTC(void);
/***************************************************************************************************
 * [Function Name]:          RCC_MCO_CLOCK
 *
 * [Description]:            Select the generated clock by the MCO pin
 *
 * [Arguments]:              MCO CLOCK
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_MCO_CLOCK(MCO_CLOCK clock);
/***************************************************************************************************
 * [Function Name]:          AHB_setPrescaler
 *
 * [Description]:            Set the AHB prescaler
 *
 * [Arguments]:              AHB PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void AHB_setPrescaler(AHB_PRESCALER prescaler);
/***************************************************************************************************
 * [Function Name]:          APB1_setPrescaler
 *
 * [Description]:            Set the APB1 prescaler
 *
 * [Arguments]:              APB1 PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void APB1_setPrescaler(APB1_PRESCALER prescaler);
/***************************************************************************************************
 * [Function Name]:          APB2_setPrescaler
 *
 * [Description]:            Set the APB2 prescaler
 *
 * [Arguments]:              APB2 PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void APB2_setPrescaler(APB2_PRESCALER prescaler);
/***************************************************************************************************
 * [Function Name]:          RCC_Config
 *
 * [Description]:            Configure the RCC module based on the configurations in the header file
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_Config(void);
/***************************************************************************************************
 * [Function Name]:          RCC_AHB_EnableCLK
 *
 * [Description]:            Enable clock for a specific peripheral on the AHB
 *
 * [Arguments]:              AHB Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_AHB_EnableCLK(AHB_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_APB1_EnableCLK
 *
 * [Description]:            Enable clock for a specific peripheral on the APB1
 *
 * [Arguments]:              APB1 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB1_EnableCLK(APB1_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_EnableCLK
 *
 * [Description]:            Enable clock for a specific peripheral on the APB2
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_EnableCLK(APB2_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_AHB_DisableCLK
 *
 * [Description]:            Disable clock for a specific peripheral on the AHB
 *
 * [Arguments]:              AHB Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_AHB_DisableCLK(AHB_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_APB1_DisableCLK
 *
 * [Description]:            Disable clock for a specific peripheral on the APB1
 *
 * [Arguments]:              APB1 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB1_DisableCLK(APB1_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_DisableCLK
 *
 * [Description]:            Disable clock for a specific peripheral on the APB2
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_DisableCLK(APB2_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral);

/*The Peripheral Reset Registers should cause the peripheral's entire register set and internal state to be reset 
to power-on defaults. This means not just the registers that are exposed to the user, but also any internal registers,
counters, or flags should be set as they would be when the device is initially powered on. However, this is not clearly
specified in the datasheet or reference manual, which is unfortunate.*/
/***************************************************************************************************
 * [Function Name]:          RCC_APB1_ResetPeripheral
 *
 * [Description]:            Reset the peripheral entire register set,flags...etc.
 *
 * [Arguments]:              APB1 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB1_ResetPeripheral(APB1_PERIPHERAL_RESET peripheral);
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_ResetPeripheral
 *
 * [Description]:            Reset the peripheral entire register set,flags...etc.
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_ResetPeripheral(APB2_PERIPHERAL_RESET peripheral);
#endif
