/*
 * ****************************************************
 * File:    gpio.h
 * Project: RF communication with stm32 and cc1101
 * MCU:     STM32L011K4
 * Others:  CC1101
 * Author:  Theocharis Ketoglou
 * Date:    20/09/2021
 * ****************************************************
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "CMSIS/stm32l0xx.h"

/**
 * 	@function init_gpio
 *
 *	@brief Simple function initialize the pins of
 *	STM MCU.
 *
 * 	@return void
 */
void init_gpio(void);

#endif /* GPIO_H_ */
