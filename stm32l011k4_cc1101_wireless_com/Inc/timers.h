/*
 * ****************************************************
 * File:    timers.h
 * Project: RF communication with stm32 and cc1101
 * MCU:     STM32L011K4
 * Others:  CC1101
 * Author:  Theocharis Ketoglou
 * Date:    20/09/2021
 * ****************************************************
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "CMSIS/stm32l0xx.h"

/**
 * 	@function init_timer2
 *
 *	@brief Initialize Timer 2
 *
 * 	@return void
 */
void init_timer2(void);

#endif /* TIMERS_H_ */
