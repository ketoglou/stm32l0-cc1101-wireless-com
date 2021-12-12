/*
 * ****************************************************
 * File:	  main.c
 * Project:   RF communication with stm32 and cc1101
 * MCU: 	  STM32L011K4
 * Others:    CC1101
 * Author:	Theocharis Ketoglou
 * Date:	  20/09/2021
 * ****************************************************
 */

//Includes
#include "CMSIS/stm32l0xx.h"
#include "cc1101.h"
#include "flags.h"
#include "init_system.h"
#include "gpio.h"
#include "nvic.h"
#include "spi.h"
#include "timers.h"

//Defines
#define TOTAL_MSG_BYTES	  8	//Total number of message bytes
#define MSG_BYTES			7	//Number of clear message bytes

//Variables
uint8_t msg[TOTAL_MSG_BYTES] = { MSG_BYTES, 'H', 'e', 'l', 'l', 'o', ' ', '1' };	//Message

//**************************************************************************************************************************************************************
int main(void){

	init_emb_flash_mem();		   //Initialize latency WS
	init_rcc();					 //Initialize clock (RCC)
	init_gpio();					//Initialize GPIOs
	init_spi();					 //Initialize SPI
	init_cc1101();				  //Initialize CC1101
	init_timer2();				  //Initialize Timer 2 to sample button
	init_external_irq();			//Initialize interrupts from external source
	init_iwdg();					//Initialize WatchDog (Comment in DEBUG mode)

	//CC1101 Receive Mode Enable
	USER_BUFFER[0] = SRX;
	spi_transmit_wait(USER_BUFFER, 1);

	while(1){

		//Monitor if we receive something
		if(flag0.f1){
			//Receive data from CC1101 (USER_BUFFER[0] is garbage data because we send a command first)
			//Data start from SPI_RX_BUFFER[1] and there are MSG_BYTES_NUM bytes in number.
			spi_transmit_wait(USER_BUFFER,init_receive_packet(USER_BUFFER, TOTAL_MSG_BYTES));
			//Change LED status
			GPIOB->ODR ^= GPIO_ODR_OD3;

			//Clear Flag
			flag0.f1 = 0;

			//Enable Receive mode again
			USER_BUFFER[0] = SFRX; //Clear RX buffer
			USER_BUFFER[1] = SRX;  //Go to Receive Mode
			spi_transmit_wait(USER_BUFFER, 2);
		}

		//Monitor if the button is pressed
		if(flag0.f3){

			//Send the message
			cc1101_transmit(msg, TOTAL_MSG_BYTES);

			//Clear Flag
			flag0.f3 = 0;

			//Enable Receive mode again
			USER_BUFFER[0] = SFRX; //Clear RX buffer
			USER_BUFFER[1] = SRX;  //Go to Receive Mode
			spi_transmit_wait(USER_BUFFER, 2);
		}

		//Clear WatchDog (Comment in DEBUG mode)
		CLRWDT();
	}
}

//**************************************************************************************************************************************************************
