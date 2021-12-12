/*
 * ****************************************************
 * File:	  init_system.c
 * Project:   RF communication with stm32 and cc1101
 * MCU: 	  STM32L011K4
 * Others:    CC1101
 * Author:	Theocharis Ketoglou
 * Date:	  20/09/2021
 * ****************************************************
 */
#include "init_system.h"

//**************************************************************************************************************************************************************

void init_emb_flash_mem(void){

	/*
	 *  ART ACCELARATOR PREFETCH ENABLE
	 *  LATENCY = 1 WS
	 */
	SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY);
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);

}

//**************************************************************************************************************************************************************

void init_rcc(void){


	//MSI => 2MHz clock
	SET_BIT(RCC->CR, RCC_CR_MSION); //MSI ON
	while(!READ_BIT(RCC->CR, RCC_CR_MSIRDY)); //Wait for MSI clock to be ready
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS)); //Wait for MSI to be the system clock

	//CMSIS function set SystemCoreClock variable based on RCC configurations
	SystemCoreClockUpdate();
}

//**************************************************************************************************************************************************************

void init_iwdg(void){

	//Unlock IWDG_PR, IWDG_RLR registers
	WRITE_REG(IWDG->KR, 0x5555UL);

	//Set prescaler to 16 => 32kHz/16 = 2kHz
	WRITE_REG(IWDG->PR, 0x02UL);

	//Set reload counter to 500
	//With 2kHz clock we have 500/2000 = 0.25 sec = 250 ms
	WRITE_REG(IWDG->RLR, 500);

	//Start the watchdog
	WRITE_REG(IWDG->KR, 0xCCCCUL);
}

//**************************************************************************************************************************************************************
