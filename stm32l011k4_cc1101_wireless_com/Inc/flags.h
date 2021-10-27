/*
 * File		:	flags.h
 * Project	: 	RF communication with stm32 and cc1101
 * MCU		: 	STM32L011K4
 * Others	: 	CC1101
 * Author	: 	Theocharis Ketoglou
 * Date		:	20/09/2021
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#include <stdint.h>

//Define the data type of the flags (number of flags)
#define DATA_TYPE	uint32_t

//Flag enumeration
typedef enum{
	FLAG0 = 0x01,
	FLAG1 = 0x02,
	FLAG2 = 0x04,
	FLAG3 = 0x08,
	FLAG4 = 0x10,
	FLAG5 = 0x20,
	FLAG6 = 0x40,
	FLAG7 = 0x80,
	FLAG8 = 0x100,
	FLAG9 = 0x200,
	FLAG10 = 0x400,
	FLAG11 = 0x800,
	FLAG12 = 0x1000,
	FLAG13 = 0x2000,
	FLAG14 = 0x4000,
	FLAG15 = 0x8000
} FLAG;

/*	--FLAG_BUFF0--
 * 	FLAG0: 	Used in CC1101 interrupt (EXTI4_15_IRQHandler)
 * 	FLAG1: 	Used to notify main that an interrupt from CC1101 pending
 * 	FLAG2: 	Used in Timer2 to notify when Button 0 change state
 * 	FLAG3:	Used when Button is pressed
 * 	FLAG4:
 * 	FLAG5:
 * 	FLAG6:
 * 	FLAG7:
 * 	FLAG8:
 * 	FLAG9:
 * 	FLAG10:
 * 	FLAG11:
 * 	FLAG12:
 * 	FLAG13:
 * 	FLAG14:
 * 	FLAG15:
 * 	...
 * 	FLAG31:
 */
DATA_TYPE FLAG_BUFF0;


//Simple defines for set/clear/read bits
#define FLAG_SET(flag)		(FLAG_BUFF0 |= flag)
#define FLAG_CLEAR(flag)	(FLAG_BUFF0 &= ~flag)
#define FLAG_READ(flag)		((FLAG_BUFF0 & flag) ? 1 : 0)
#define FLAG_CLEAR_ALL()	(FLAG_BUFF0 &= 0)


#endif /* FLAGS_H_ */
