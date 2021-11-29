/*
 * File		:	nvic.c
 * Project	: 	RF communication with stm32 and cc1101
 * MCU		: 	STM32L011K4
 * Others	: 	CC1101
 * Author	: 	Theocharis Ketoglou
 * Date		:	20/09/2021
 */

#include "nvic.h"
#include "spi.h"
#include "flags.h"

//Variables
uint8_t button0_counter = 0;		//Used for sampling button

//**************************************************************************************************************************************************************

void init_external_irq(void){

	//Enable System configuration controller
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//Enable external interrupt from line 8 		(CC1101 GDO0)
	EXTI->IMR |= EXTI_IMR_IM8;
	//Enable interrupt on rising edge from line 8 	(CC1101 GDO0)
	EXTI->RTSR |= EXTI_RTSR_RT8;
	//Configure PA8 as interrupt source 			(CC1101 GDO0)
	SYSCFG->EXTICR[2] &= (0xFFF0 | SYSCFG_EXTICR3_EXTI8_PA);

	//Enable EXTI4_15 Interrupt
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

//**************************************************************************************************************************************************************

void SPI1_IRQHandler(void){

	//RX buffer not empty interrupt
	if(SPI1->SR & SPI_SR_RXNE){
		SPI_RX_BUFFER[SPI_RX_COUNTER] = SPI1->DR;
		SPI_RX_COUNTER ++;
	}

	//TX buffer empty interrupt
	if(SPI1->SR & SPI_SR_TXE){

		if(!SPI_TX_SIZE){
			//Disable NSS pin
			nss_pin_handler(CURRENT_NSS,0);
			//Disable SPI TX interrupt
			SPI1->CR2 &= ~SPI_CR2_TXEIE;
		}else{
			SPI1->DR = SPI_TX_BUFFER[SPI_TX_COUNTER];
			SPI_TX_SIZE --;
			SPI_TX_COUNTER ++;
		}

	}

}

//**************************************************************************************************************************************************************

/*
 * Line 8 Pin:
 * Asserts when sync word has been sent / received, and de-asserts at the end of the packet.
 * In RX, the pin will also de-assert when a packet is discarded due to address or maximum length
 * filtering or when the radio enters RXFIFO_OVERFLOW state. In TX the pin will de-assert if the TX FIFO underflows.
 */
void EXTI4_15_IRQHandler(void){

	//Interrupt on line 8
	if(EXTI->PR & EXTI_PR_PIF8){

		if(!flag0.f0){
			//Disable interrupt on rising edge from line 8
			EXTI->RTSR &= ~EXTI_RTSR_RT8;
			//Enable interrupt on falling edge from line 8
			EXTI->FTSR |= EXTI_FTSR_FT8;
			flag0.f0 = 1;
		}else{
			//Enable interrupt on rising edge from line 8
			EXTI->RTSR |= EXTI_RTSR_RT8;
			//Disable interrupt on falling edge from line 8
			EXTI->FTSR &= ~EXTI_FTSR_FT8;
			flag0.f0 = 1;
			flag0.f1 = 1;
		}

		//Clear flag
		EXTI->PR |= EXTI_PR_PIF8;
	}
}

//**************************************************************************************************************************************************************

void TIM2_IRQHandler(void){

	//Sampling Button
	//-----------------------------------------------------
	if(GPIOA->IDR & 0x01){
		button0_counter = 0;
		flag0.f2 = 0;
	}else{
		if(!flag0.f2)
			button0_counter ++;
	}

	if(button0_counter == 10 && !flag0.f2){
		flag0.f3 = 1;
		flag0.f2 = 1;
	}
	//-----------------------------------------------------


	//Clear Timer 2 Flag
	TIM2->SR &= ~TIM_SR_UIF;
}

//**************************************************************************************************************************************************************

