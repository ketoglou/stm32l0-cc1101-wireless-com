/*
 * ****************************************************
 * File:	gpio.c
 * Project:	RF communication with stm32 and cc1101
 * MCU:		STM32L011K4
 * Others:	CC1101
 * Author:	Theocharis Ketoglou
 * Date:	20/09/2021
 * ****************************************************
 */

#include "gpio.h"

void init_gpio(void){

	//Enable GPIO clock
	SET_BIT(RCC->IOPENR, RCC_IOPENR_IOPAEN); //Port A clock enable
	SET_BIT(RCC->IOPENR, RCC_IOPENR_IOPBEN); //Port B clock enable

	/*
	 * MODER Register Reset State:
	 * GPIOA_MODER = 0xEBFF FCFF
	 * GPIOx_MODER = 0xFFFF FFFF
	 */

	//SPI INT: PA8 (GPI, Push-Pull, High Speed, Pull down)
	CLEAR_BIT(GPIOA->MODER, (GPIO_MODER_MODE8_1 | GPIO_MODER_MODE8_0));
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED8_1);
	SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD8_1);

	//SPI MOSI: PA7 (AF, Push-Pull, Medium Speed, No pull up/down)(AF0:MOSI)
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE7_0);
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED7_0); //Medium speed (2MHz)

	//SPI MISO: PA6 (AF, Push-Pull, Medium Speed, No pull up/down)(AF0:MISO)
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE6_0);
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED6_0); //Medium speed (2MHz)

	//SPI SCK: PA5 (AF, Push-Pull, Medium Speed, No pull up/down)(AF0:SCK)
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE5_0);
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED5_0); //Medium speed (2MHz)

	//SPI CS: PA4 (GPO, Push-Pull, Medium Speed,Pull up)
	SET_BIT(GPIOA->MODER, GPIO_MODER_MODE4_0);
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED4_0); //Medium speed (2MHz)
	SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD4_0);

	//LED : PB3 (GPO, Push-Pull, Medium Speed,No pull up/down)
	CLEAR_BIT(GPIOB->MODER, GPIO_MODER_MODE3_1);
	SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEED3_0); //Medium speed (2MHz)

	//Button : PA0 (GPI, Push-Pull, High Speed, Pull up)
	CLEAR_BIT(GPIOA->MODER, (GPIO_MODER_MODE0_1 | GPIO_MODER_MODE0_0));
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEED0_1);
	SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD0_0);

}
