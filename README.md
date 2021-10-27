# Radio Frequency Wireless Communication

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)\
![MCU](https://img.shields.io/badge/MCU-STM32-blue)
![MCU Family](https://img.shields.io/badge/Family-L0-yellow)
![IDE](https://img.shields.io/badge/STM32CubeIDE-blue)
![firmware-size](https://img.shields.io/badge/Firmware%20Size-3.55%20kB-red)
![ram-usage](https://img.shields.io/badge/RAM%20Usage-1.15%20kB-red)

This project demonstrates RF wireless communication with the use
of STM32L011K4 as MCU and CC1101 as RF IC. User can send a message
with the press of a button and receive a message anytime. The 
communication is half-duplex (cannot receive only when send). For
development i have used STM32CubeIDE with bare metal code.

## <span style="color:red">RF Characteristics</span>
```diff
+ Modulation:			GFSK
! Frequency:			868 MHz
- Channel Bandwidth:	100 kHz
- Channel Spacing:		200 kHz
- Selected Channel:		0
- Deviation:			19 kHz
- Data Rate:			1 kBaud
```

## Message Structure
Message Address is specified to rfSettings array. You can change it if 
you want. When a transmit occurs, CC1101 send automatically two times the
address (0xD391) and after that it send the number of bytes that will follow
so the receiver get knowledge of how much bytes to expect. Receiver must
have the same Address to receive the message.

| Byte 0 	| Byte 1 	| Byte 2 	| Byte 3 	|            Byte 4           	|
|:------:	|:------:	|:------:	|:------:	|:---------------------------:	|
|  0xD3  	|  0x91  	|  0xD3  	|  0x91  	| Number of Bytes that follow 	|

## Hardware
| Pin | Usage       |
|-----|-------------|
| PA8 | CC1101 INT  |
| PA7 | CC1101 MOSI |
| PA6 | CC1101 MISO |
| PA5 | CC1101 SCK  |
| PA4 | CC1101 CS   |
| PA0 | Button      |
| PB3 | LED         |

## Flashing
Import the project to STM32CubeIDE and build it or build it directly
with gcc-arm-none-eabi. Flash it and you are ready.
