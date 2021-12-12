/*
 * ****************************************************
 * File:	  cc1101.c
 * Project:   RF communication with stm32 and cc1101
 * MCU: 	  STM32L011K4
 * Others:    CC1101
 * Author:	Theocharis Ketoglou
 * Date:	  20/09/2021
 * ****************************************************
 */

#include "cc1101.h"
#include "spi.h"
#include "flags.h"

//Define the arrays
//**************************************************************************************************************************************************************

//PA Table for define dBm Power
uint8_t PA_TABLE[9] = {PATABLE,0xC5,0xC5,0xC5,0xC5,0xC5,0xC5,0xC5,0xC5};

//**************************************************************************************************************************************************************
//Rf settings for CC1101
uint8_t rfSettings[48] = {
	BURST_BYTE_WR,				  //Header Burst Write
    0x29,  // IOCFG2              GDO2 Output Pin Configuration						--Don't care
    0x2E,  // IOCFG1              GDO1 Output Pin Configuration						--Don't care
    0x06,  // IOCFG0              GDO0 Output Pin Configuration						--Interrupt when packet received/transmitted
    0x47,  // FIFOTHR             RX FIFO and TX FIFO Thresholds					--TX,RX FIFOs size and 0dB RX Attenuation

    0xD3,  // SYNC1               Sync Word, High Byte								--First 2 bytes of address
    0x91,  // SYNC0               Sync Word, Low Byte								--Address: 0xD391

	0xFF,  // PKTLEN    		  Packet Length										--Variable packet length
    0x04,  // PKTCTRL1            Packet Automation Control							--PQT off, CRC_AUTOFLUSH off, APPEND_STATUS off, ADDRESS_CKECK off
    0x05,  // PKTCTRL0            Packet Automation Control                  		--CRC calculation ON, Variable packed length mode
    0x00,  // ADDR                Device Address									--Don't care, we set ADDRESS_CKECK off
    0x00,  // CHANNR              Channel Number									--Center frequency (Channel 0)

    0x06,  // FSCTRL1             Frequency Synthesizer Control						--intermediate frequency = (26MHz/2^10)*6 = 152.343 kHz
    0x00,  // FSCTRL0             Frequency Synthesizer Control						--frequency offset = 0
    0x21,  // FREQ2               Frequency Control Word, High Byte					--carrier frequency = (26MHz/2^16)*FREQ[23:0] = (26MHz/2^16)*2187894 = 868MHz
    0x62,  // FREQ1               Frequency Control Word, Middle Byte
    0x76,  // FREQ0               Frequency Control Word, Low Byte

    0xC8,  // MDMCFG4             Modem Configuration								--Channel Bandwidth = 100 kHz
    0x93,  // MDMCFG3             Modem Configuration								--Data Rate = 1 kBaud
	0x13,  // MDMCFG2             Modem Configuration								--Better sensitivity, GFSK, no machester encoding, sync mode = 30/32 sync word bits
    0x22,  // MDMCFG1             Modem Configuration								--disable Forward Error Correction (FEC), 4 preamble bytes to be send, 2 bit exponent of channel spacing
    0xF8,  // MDMCFG0             Modem Configuration								--Used to set channel spacing = 200 kHz
	0x34,  // DEVIATN             Modem Deviation Setting							--Deviation 19 kHz

    0x07,  // MCSM2               Main Radio Control State Machine Configuration	--Don't care we don't use SWOR
    0x30,  // MCSM1               Main Radio Control State Machine Configuration	--Go to IDLE state after RX/TX state end
    0x18,  // MCSM0               Main Radio Control State Machine Configuration	--Calibrate when going from IDLE to RX/TX

    0x16,  // FOCCFG              Frequency Offset Compensation Configuration
    0x6C,  // BSCFG               Bit Synchronization Configuration
    0x43,  // AGCCTRL2            AGC Control
    0x40,  // AGCCTRL1            AGC Control
    0x91,  // AGCCTRL0            AGC Control
    0x87,  // WOREVT1             High Byte Event0 Timeout							--Don't care we don't use SWOR
    0x6B,  // WOREVT0             Low Byte Event0 Timeout							--Don't care we don't use SWOR
    0xFB,  // WORCTRL             Wake On Radio Control								--Don't care we don't use SWOR
    0x56,  // FREND1              Front End RX Configuration						--Reset state
    0x10,  // FREND0              Front End TX Configuration						--Reset state

    0xE9,  // FSCAL3              Frequency Synthesizer Calibration					--Value given from SmartRF Studio
    0x2A,  // FSCAL2              Frequency Synthesizer Calibration					--Value given from SmartRF Studio
    0x00,  // FSCAL1              Frequency Synthesizer Calibration					--Value given from SmartRF Studio
    0x1F,  // FSCAL0              Frequency Synthesizer Calibration					--Value given from SmartRF Studio

    0x41,  // RCCTRL1             RC Oscillator Configuration						--Value given from SmartRF Studio
    0x00,  // RCCTRL0             RC Oscillator Configuration						--Value given from SmartRF Studio

    0x59,  // FSTEST              Frequency Synthesizer Calibration Control
    0x7F,  // PTEST               Production Test
    0x3F,  // AGCTEST             AGC Test
    0x81,  // TEST2               Various Test Settings
    0x35,  // TEST1               Various Test Settings
    0x09   // TEST0               Various Test Settings
};
//**************************************************************************************************************************************************************

void init_cc1101(void){

	//Software reset CC1101
	uint8_t tx_byte[1] = {SRES};
	spi_transmit_wait(tx_byte,1);

	//Send all registers values
	spi_transmit_wait(rfSettings,48);

	//Send PA table
	spi_transmit_wait(PA_TABLE,9);
}

//**************************************************************************************************************************************************************

void cc1101_transmit(uint8_t *buffer, uint8_t size){

	//Clear Flag
	flag0.f1 = 0;

	//Go to IDLE state and wait CC1101 to go to IDLE state
	USER_BUFFER[0] = SIDLE;
	USER_BUFFER[1] = SNOP;
	while((SPI_RX_BUFFER[1] & 0xF0) != 0x00)
		spi_transmit_wait(USER_BUFFER,2);

	//Initialize USER_BUFFER[0] with a command
	USER_BUFFER[0] = FIFO_TX_BURST; //Write TX buffer

	//Copy data to USER_BUFFER
	for(uint8_t i=1;i<(size+1);i++){
		USER_BUFFER[i] = buffer[i-1];
	}

	//Send the data
	spi_transmit_wait(USER_BUFFER,size+1);
	//Start transmission
	USER_BUFFER[0] = STX;
	spi_transmit_wait(USER_BUFFER,1);

	//Wait for transmission to complete
	while(!flag0.f1);

	//Flush/Clear TX FIFO
	USER_BUFFER[0] = SFTX;
	spi_transmit_wait(USER_BUFFER,1);

	//Clear flag
	flag0.f1 = 0;
}

//**************************************************************************************************************************************************************

uint16_t init_receive_packet(uint8_t *buffer, uint16_t size){

	buffer[0] = FIFO_RX_BURST; //Read RX buffer
	for(uint16_t i=1;i<(size+1);i++){
		buffer[i] = SNOP;
	}

	return (size + 1);
}

//**************************************************************************************************************************************************************
