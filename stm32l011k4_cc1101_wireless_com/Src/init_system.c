/*
 * File		:	init_system.c
 * Project	: 	RF communication with stm32 and cc1101
 * MCU		: 	STM32L011K4
 * Others	: 	CC1101
 * Author	: 	Theocharis Ketoglou
 * Date		:	20/09/2021
 */

#include "init_system.h"

//**************************************************************************************************************************************************************

void init_emb_flash_mem(void){

	/*
	 *  ART ACCELARATOR PREFETCH ENABLE
	 *  LATENCY = 0 WS
	 */
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_PRFTEN;

}

//**************************************************************************************************************************************************************

void init_rcc(void){

	/*
	//HSI16 & PLL => 24MHz clock
	RCC->CR |= RCC_CR_HSION; //Enable HSI16
	while(!(RCC->CR & RCC_CR_HSIRDY)); //Wait for HSI16 to be ready
	RCC->CR |= RCC_CR_HSIDIVEN; //Enable HSI16/4
	while(!(RCC->CR & RCC_CR_HSIDIVF)); //Wait for HSI16/4 to be ready

	RCC->ICSCR = 0x0000B000; //No trimming

	RCC->CFGR |= RCC_CFGR_PLLDIV_0; //PLL output/2
	RCC->CFGR |= RCC_CFGR_PLLMUL_2; //PLL*12;

	RCC->CR |= RCC_CR_PLLON; //Enable PLL
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY); //Wait for PLL to be ready

	RCC->CFGR |= RCC_CFGR_SW;    //PLL as system clock
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS); //Wait for PLL to be the system clock
	*/


	//MSI => 2MHz clock
	RCC->CR |= RCC_CR_MSION; //MSI ON
	while(!(RCC->CR & RCC_CR_MSIRDY)); //Wait for MSI clock to be ready
	while(RCC->CFGR & RCC_CFGR_SWS); //Wait for MSI to be the system clock

	//CMSIS function set SystemCoreClock variable based on RCC configurations
	SystemCoreClockUpdate();
}

//**************************************************************************************************************************************************************

void init_iwdg(void){

	//Unlock IWDG_PR, IWDG_RLR registers
	IWDG->KR = 0x5555UL;

	//Set prescaler to 16 => 32kHz/16 = 2kHz
	IWDG->PR = 0x02UL;

	//Set reload counter to 500
	//With 2kHz clock we have 500/2000 = 0.25 sec = 250 ms
	IWDG->RLR = 500;

	//Start the watchdog
	IWDG->KR = 0xCCCCUL;
}

//**************************************************************************************************************************************************************
