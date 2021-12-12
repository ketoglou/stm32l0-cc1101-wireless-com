/*
 * ****************************************************
 * File:	  nvic.h
 * Project:   RF communication with stm32 and cc1101
 * MCU: 	  STM32L011K4
 * Others:    CC1101
 * Author:	Theocharis Ketoglou
 * Date:	  20/09/2021
 * ****************************************************
 */
#ifndef NVIC_H_
#define NVIC_H_

#include "CMSIS/stm32l0xx.h"


/**
 * 	@function init_external_irq
 *
 *	 @brief Initialize the external interrupts
 *
 * 	@return void
 */
void init_external_irq(void);

#endif /* NVIC_H_ */
