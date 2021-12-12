/*
 * ****************************************************
 * File:	  cc1101.h
 * Project:   RF communication with stm32 and cc1101
 * MCU: 	  STM32L011K4
 * Others:    CC1101
 * Author:	  Theocharis Ketoglou
 * Date:	  20/09/2021
 * ****************************************************
 */

#ifndef CC1101_H_
#define CC1101_H_

#include "CMSIS/stm32l0xx.h"

//************************************************************************************************************************************************************************************

//Commands definition for CC1101
//************************************************************************************************************************************************************************************
// PA table
#define PATABLE         0x7E		//PA table Burst access

//Burst Bytes for Write/Read register in Burst Mode
#define BURST_BYTE_WR	0x40 	   //Write,Burst,Start address = 0x00
#define BURST_BYTE_RD	0xC0 	   //Read,Burst,Start address = 0x00

//Command Strobes
#define SRES			0x30 	    //Reset chip
#define SFSTXON		    0x31		//Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define SXOFF			0x32		//Turn off crystal oscillator
#define SCAL			0x33		//Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define SRX			    0x34		//Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
#define STX			    0x35		//In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1.  If in RX state and CCA is enabled: Only go to TX if channel is clear.
#define SIDLE			0x36		//Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
#define SWOR			0x38		//Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if WORCTRL.RC_PD=0.
#define SPWD			0x39		//Enter power down mode when CSn goes high
#define SFRX		 	0x3A		//Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states.
#define SFTX		    0x3B		//Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states.
#define SWORRST	  	    0x3C		//Reset real time clock to Event1 value.
#define SNOP			0x3D		//No operation. May be used to get access to the chip status byte.

//Other
#define MARCSTATE	    0xF5		//Main Radio Control State Machine State
#define TXBYTES		    0xFA		//Number of bytes in TX FIFO
#define RXBYTES		    0xFB		//Number of bytes in RX FIFO

//FIFO RX/TX
#define FIFO_TX		    0x3F		//Single byte access to TX FIFO
#define FIFO_TX_BURST	0x7F		//Burst access to TX FIFO
#define FIFO_RX		    0xBF		//Single byte access to RX FIFO
#define FIFO_RX_BURST	0xFF		//Burst access to RX FIFO

//************************************************************************************************************************************************************************************
//Functions definition

/**
 * 	@function init_cc1101
 *
 *	@brief Initialize CC1101. Send via SPI the appropriate
 *	commands to it.
 *
 * 	@return void
 */
void init_cc1101(void);

/**
 * 	@function cc1101_transmit
 *
 *	@brief Send data to CC1101 and start the transmission
 *
 * 	@return void
 */
void cc1101_transmit(uint8_t *buffer, uint8_t size);

/**
 * 	@function cc1101_transmit
 *
 *	@brief Fill buffer with a number of SNOPs
 *	so that buffer can be send to CC1101 and receive data.
 *
 * 	@return uint16_t
 */
uint16_t init_receive_packet(uint8_t *buffer, uint16_t size);

#endif /* CC1101_H_ */
