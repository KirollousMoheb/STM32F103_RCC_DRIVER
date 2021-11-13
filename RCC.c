/******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC.c
 *
 * Description: Source file for the STM32103 RCC driver
 *
 * Author: Kirollous Moheb
 *
 *******************************************************************************/
#include "RCC.h"
#include "stm32f10x.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/***************************************************************************************************
 * [Function Name]:          RCC_enableHSI
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/

void RCC_enableHSI(void){
	SET_BIT(RCC->CR,RCC_CR_HSION);//Enable HSI.
	while(BIT_IS_CLEAR(RCC->CIR,RCC_CR_HSIRDY));//Polling until HSI is ready.
	SET_BIT(RCC ->CIR, RCC_CIR_HSIRDYC); //Clear HSI ready flag.
	CLEAR_BIT(RCC ->CFGR, RCC_CFGR_SW_0); //Select HSI as system clock.
	CLEAR_BIT(RCC -> CFGR, RCC_CFGR_SW_1); //Select HSI as system clock.
}
/***************************************************************************************************
 * [Function Name]:          RCC_enableHSE
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/

void RCC_enableHSE(void){
	SET_BIT(RCC->CR,RCC_CR_HSEON);//Enable HSE.
	while((RCC->CIR&RCC_CR_HSERDY)==0);//Polling until HSE is ready.
	SET_BIT(RCC ->CIR, RCC_CIR_HSERDYC); //Clear HSE ready flag.
	SET_BIT(RCC ->CFGR, RCC_CFGR_SW_0); //Select HSE as system clock.
	CLEAR_BIT(RCC -> CFGR, RCC_CFGR_SW_1); //Select HSE as system clock.
}

/***************************************************************************************************
 * [Function Name]:          RCC_enablePLL
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/

void RCC_enablePLL(uint8 PLL_multiplication_factor,uint8 PLL_CLOCK){
	RCC -> CFGR = ((RCC ->CFGR) & (uint32)0xFFC3FFFF) | (PLL_multiplication_factor << (uint8)RCC_CFGR_PLLMULL_0); //Set value of PLL multiplication factor.
	SET_BIT(RCC->CR,RCC_CR_PLLON);//Enable PLL.
	while((RCC->CIR&RCC_CR_PLLRDY)==0);//Polling until PLL is ready.
	SET_BIT(RCC ->CIR, RCC_CIR_PLLRDYC); //Clear PLL ready flag.
	switch(PLL_CLOCK){
	case Half_HSI:
		CLEAR_BIT(RCC -> CFGR, RCC_CFGR_PLLSRC);
		break;
	case HSE:
		SET_BIT(RCC -> CFGR, RCC_CFGR_PLLSRC); //HSE oscillator clock selected as PLL input clock.
		CLEAR_BIT(RCC -> CFGR, RCC_CFGR_PLLXTPRE); //HSE clock not divided.
		break;
	default :
		break;
	}
}
/***************************************************************************************************
 * [Function Name]:          RCC_enableLSI
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableLSI(void){
	SET_BIT(RCC->CSR,RCC_CSR_LSION);//Enable LSE
	while(BIT_IS_CLEAR(RCC->CSR,RCC_CSR_LSIRDY));
	SET_BIT(RCC->CIR,RCC_CIR_LSIRDYC);
	CLEAR_BIT(RCC ->BDCR, RCC_BDCR_RTCSEL_0); //RTC clock source selection.
	SET_BIT(RCC -> BDCR, RCC_BDCR_RTCSEL_1); //RTC clock source selection.
}
/***************************************************************************************************
 * [Function Name]:          RCC_enableLSE
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableLSE(void){
	SET_BIT(RCC->BDCR,RCC_BDCR_LSEON);//Enable LSE
	while(BIT_IS_CLEAR(RCC->BDCR,RCC_BDCR_LSERDY));
	SET_BIT(RCC->CIR,RCC_CIR_LSERDYC);
	SET_BIT(RCC ->BDCR, RCC_BDCR_RTCSEL_0); //RTC clock source selection.
	CLEAR_BIT(RCC -> BDCR, RCC_BDCR_RTCSEL_1); //RTC clock source selection.
}
/***************************************************************************************************
 * [Function Name]:          RCC_enableRTC
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_enableRTC(void){
	SET_BIT(RCC->BDCR,RCC_BDCR_RTCEN);
}
/***************************************************************************************************
 * [Function Name]:          RCC_MCO_CLOCK
 *
 * [Description]:
 *
 * [Arguments]:              MCO CLOCK
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_MCO_CLOCK(MCO_CLOCK clock){
	RCC -> CFGR = ((RCC -> CFGR) & 0xF8FFFFFF) | (clock << RCC_CFGR_MCO);
}
/***************************************************************************************************
 * [Function Name]:          AHB_setPrescaler
 *
 * [Description]:
 *
 * [Arguments]:              AHB PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void AHB_setPrescaler(AHB_PRESCALER prescaler){
	RCC -> CFGR = ((RCC ->CFGR) & 0xFFFFFF0F) | (prescaler << RCC_CFGR_HPRE_0);
}
/***************************************************************************************************
 * [Function Name]:          APB1_setPrescaler
 *
 * [Description]:
 *
 * [Arguments]:              APB1 PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void APB1_setPrescaler(APB1_PRESCALER prescaler){
	RCC -> CFGR = ((RCC -> CFGR) & 0xFFFFF8FF) | (prescaler << RCC_CFGR_PPRE1_0);
}
/***************************************************************************************************
 * [Function Name]:          APB2_setPrescaler
 *
 * [Description]:
 *
 * [Arguments]:              APB2 PRESCALER
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void APB2_setPrescaler(APB2_PRESCALER prescaler){
	RCC -> CFGR = ((RCC -> CFGR) & 0xFFFFC7FF) | (prescaler << RCC_CFGR_PPRE2_0);
}
/***************************************************************************************************
 * [Function Name]:          RCC_AHB_EnableCLK
 *
 * [Description]:
 *
 * [Arguments]:              AHB Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_AHB_EnableCLK(AHB_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	SET_BIT(RCC->AHBENR,peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_APB1_EnableCLK
 *
 * [Description]:
 *
 * [Arguments]:              APB1 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB1_EnableCLK(APB1_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	SET_BIT(RCC->APB1ENR,peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_EnableCLK
 *
 * [Description]:
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_EnableCLK(APB2_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	SET_BIT(RCC->APB2ENR,peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_AHB_DisableCLK
 *
 * [Description]:
 *
 * [Arguments]:              AHB Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_AHB_DisableCLK(AHB_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	CLEAR_BIT(RCC->AHBENR,peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_APB1_DisableCLK
 *
 * [Description]:
 *
 * [Arguments]:              APB1 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB1_DisableCLK(APB1_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	CLEAR_BIT(RCC->APB1ENR,peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_DisableCLK
 *
 * [Description]:
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_DisableCLK(APB2_PERIPHERAL_CLOCK_ENABLE_DISABLE peripheral){
	SET_BIT(RCC->APB2ENR,peripheral);
}
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
void RCC_APB1_ResetPeripheral(APB1_PERIPHERAL_RESET peripheral){
SET_BIT(RCC -> APB1RSTR, peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_APB2_ResetPeripheral
 *
 * [Description]:            Reset the peripheral entire register set,flags...etc.
 *
 * [Arguments]:              APB2 Peripheral Index
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_APB2_ResetPeripheral(APB2_PERIPHERAL_RESET peripheral){
SET_BIT(RCC -> APB2RSTR, peripheral);
}
/***************************************************************************************************
 * [Function Name]:          RCC_Config
 *
 * [Description]:
 *
 * [Arguments]:              VOID
 *
 * [Returns]:                VOID
 ***************************************************************************************************/
void RCC_Config(void){
#if(Enable_HSI)
	RCC_enableHSI();
#elif(Enable_HSE)
	RCC_enableHSE();
#elif(Enable_PLL)
	RCC_enablePLL(PLL_CLK, PLL_Multiplication);
#endif

#if(Enable_LSI)
	RCC_enableLSI();
#endif
#if(Enable_LSE)
	RCC_enableLSE();
#endif

#if(Enable_RTC)
	RCC_enableRTC();
#endif

#if(Enable_AHB)
	AHB_setPrescaler(AHB_Prescaler);
#endif

#if(Enable_APB1)
	APB1_setPrescaler(APB1_Prescaler);
#endif

#if(Enable_APB2)
	APB2_setPrescaler(APB2_Prescaler);
#endif
#if(Enable_MCO)
	RCC_MCO_CLOCK(MCO_Prescaler);
#endif

}

