/*
 * ****************************************************
 * File:	flags.h
 * Project:	RF communication with stm32 and cc1101
 * MCU:		STM32L011K4
 * Others:	CC1101
 * Author:	Theocharis Ketoglou
 * Date:	20/09/2021
 * ****************************************************
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#include <stdint.h>

//Flag enumeration
typedef struct{
	uint8_t f0 : 1;
	uint8_t f1 : 1;
	uint8_t f2 : 1;
	uint8_t f3 : 1;
	uint8_t f4 : 1;
	uint8_t f5 : 1;
	uint8_t f6 : 1;
	uint8_t f7 : 1;
	uint8_t f8 : 1;
	uint8_t f9 : 1;
	uint8_t f10 : 1;
	uint8_t f11 : 1;
	uint8_t f12 : 1;
	uint8_t f13 : 1;
	uint8_t f14 : 1;
	uint8_t f15 : 1;
} flag;

flag flag0;

/*	--flag0--
 * 	f0: 
 * 	f1: Used to notify main that an interrupt from CC1101 pending
 * 	f2: Used in Timer2 to notify when Button 0 change state
 * 	f3: Used when Button is pressed
 * 	f4:
 * 	f5:
 * 	f6:
 * 	f7:
 * 	f8:
 * 	f9:
 * 	f10:
 * 	f11:
 * 	f12:
 * 	f13:
 * 	f14:
 * 	f15:
 * 	...
 * 	f31:
 */



#endif /* FLAGS_H_ */
