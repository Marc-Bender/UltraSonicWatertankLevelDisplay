/*
 * uart.h
 *
 * Created: 19.05.2024 19:28:26
 *  Author: marc
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include <stdint.h>

#define UARTBUFFERSIZE (64)

typedef struct 
{
	char receiveBuffer[UARTBUFFERSIZE];	
	char transmitBuffer[UARTBUFFERSIZE];	
	uint8_t freeByteIndexReceiveBuffer;
	uint8_t freeByteIndexTransmitBuffer;
	uint8_t readByteIndexReceiveBuffer;
	uint8_t readByteIndexTransmitBuffer;

	uint32_t baudrate;
} USARTHandle_t;

typedef struct
{
	bool wasSuccessful;
	uint8_t dataByte;
} usartReceiveResult_t;

extern volatile USARTHandle_t uart0Handle;

uint8_t USART_getReceivableBytes(void);
void UART_disable(void);
void USART_Init(void);
void USART_Transmit(const char * const data, const uint8_t byteCount);
usartReceiveResult_t USART_Receive( void );

#endif /* UART_H_ */
