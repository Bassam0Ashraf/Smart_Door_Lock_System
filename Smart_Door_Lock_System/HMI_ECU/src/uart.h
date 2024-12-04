/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*How many bits we will send*/
typedef enum
{
	BIT_5,			// 5-bit
	BIT_6,			// 6-bit
	BIT_7,			// 7-bit
	BIT_8,			// 8-bit
	BIT_9 = 7		// 9-bit
}UART_BitDataType;


/* Enable or disable parity check */
typedef enum
{
	DISABLE,
	EVEN_PARITY = 2,
	ODD_PARITY
}UART_ParityType;


/*How many stop bits we will send*/
typedef enum
{
	BIT_1,			// 1-bit
	BIT_2			// 2-bit
}UART_StopBitType;


/*Value of UBRR according to our baud rate , while we works in double speed mode*/
typedef enum
{
	RATE_2400_bps   = 416,
	RATE_4800_bps   = 207,
	RATE_9600_bps   = 103,
	RATE_14_4_Kbps  = 68,
	RATE_19_2_Kbps  = 51,
	RATE_28_8_Kbps  = 34,
	RATE_38_4_Kbps  = 25,
	RATE_57_6_Kbps  = 16,
	RATE_115_2_Kbps = 8,
	RATE_230_4_Kbps = 3,
	RATE_250_Kbps   = 3,
	RATE_500_Kbps   = 1,
	RATE_1_Mbps 	= 0,
}UART_BaudRateType;

/* Configurations of UART */
typedef struct {
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
