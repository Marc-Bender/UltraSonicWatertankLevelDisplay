/*
 * uart.c
 *
 * Created: 19.05.2024 19:28:59
 *  Author: marc
 */ 

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h> // for memset

volatile USARTHandle_t uart0Handle = {.baudrate=9600};

void UART_disable(void)
{
	// to be implemented
}

void USART_Init(void)
{
	memset((void*)uart0Handle.receiveBuffer, 0, UARTBUFFERSIZE);
	memset((void*)uart0Handle.transmitBuffer, 0, UARTBUFFERSIZE);
	uart0Handle.freeByteIndexReceiveBuffer = 0;
	uart0Handle.freeByteIndexTransmitBuffer = 0;
	uart0Handle.readByteIndexReceiveBuffer = 0;
	uart0Handle.readByteIndexTransmitBuffer = 0;

	/* Set baud rate */
	volatile const uint32_t helper = (8000uLL * 1000 / 16 / uart0Handle.baudrate) - 1;
	UBRR0H = (unsigned char)(helper>>8);
	UBRR0L = (unsigned char)helper;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (0<<USBS)|(3<<UCSZ0);
}

void USART_Transmit(const char * const data, const uint8_t byteCount)
{
	if(uart0Handle.freeByteIndexTransmitBuffer != uart0Handle.readByteIndexTransmitBuffer)
	{
		// not everything read from the buffer that is still in there thus just putting the byte in the buffer should be enough to send out the byte eventually via chain of interrupts.
		for(uint8_t i=0;i<byteCount;i++)
		{
			uart0Handle.transmitBuffer[uart0Handle.freeByteIndexTransmitBuffer] = data[i];
			uart0Handle.freeByteIndexTransmitBuffer = (uart0Handle.freeByteIndexTransmitBuffer + 1) % UARTBUFFERSIZE;
		}
	}
	else
	{
		// interrupt chain currently broken because no bytes in the buffer anymore thus initiate the transfer of the buffer by sending out the first byte directly from here
		for(uint8_t i=1;i<byteCount;i++)
		{
			uart0Handle.transmitBuffer[uart0Handle.freeByteIndexTransmitBuffer] = data[i];
			uart0Handle.freeByteIndexTransmitBuffer = (uart0Handle.freeByteIndexTransmitBuffer + 1) % UARTBUFFERSIZE;
		}
		/* Wait for empty transmit buffer */ 
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		/* Put data into buffer, sends the data */
		UDR0 = data[0];
		UCSR0B |= 1<<TXCIE; // ensure the interrupt for transmit direction is on when we send the first byte of a buffer to ensure that the remaining buffer contents may get sent by interrupts. 
		sei(); // ensure the interrupt is also enabled and thus may be served by the isr
	}
}

usartReceiveResult_t USART_Receive( void )
{
	usartReceiveResult_t returnValue = 
	{
		.wasSuccessful = (uart0Handle.readByteIndexReceiveBuffer != uart0Handle.freeByteIndexReceiveBuffer), // when the two indices are not equal there are bytes in the buffer that where written but not read thus there is data to be passed to the caller and the function was successfui
		.dataByte = uart0Handle.receiveBuffer[uart0Handle.readByteIndexReceiveBuffer],
	};

	uart0Handle.readByteIndexReceiveBuffer = (uart0Handle.readByteIndexReceiveBuffer + 1) % UARTBUFFERSIZE;

	return returnValue;
}

uint8_t USART_getReceivableBytes(void)
{
	if(uart0Handle.readByteIndexReceiveBuffer <= uart0Handle.freeByteIndexReceiveBuffer)
	{
		// more written than read available number of bytes is difference
		return uart0Handle.freeByteIndexReceiveBuffer - uart0Handle.readByteIndexReceiveBuffer;
		// evaluates to 0 if equal with less arithmethic effort than else case... 
	}
	else 
	{
		//(uart0Handle.freeByteIndexReceiveBuffer < uart0Handle.readByteIndexReceiveBuffer)
		// read index comes after free byte index thus there must be data after read index buffer loops over and ends at free byte index
		//     size is max index +1 thus -1 here
		return UARTBUFFERSIZE - uart0Handle.readByteIndexReceiveBuffer - 1  + uart0Handle.freeByteIndexReceiveBuffer;
	}
	
}

ISR(USART0_RX_vect)
{
	// do not notify the application that something was received because the only point when that would make sense is in display on state but in idle mode the uart is not really working.
	uart0Handle.receiveBuffer[uart0Handle.freeByteIndexReceiveBuffer] = UDR0; // put the received character into the receive buffer for further digestion in the application
	uart0Handle.freeByteIndexReceiveBuffer = (uart0Handle.freeByteIndexReceiveBuffer + 1) % UARTBUFFERSIZE; // update the freeByteindex for the reception of the next character
}

ISR(USART0_TX_vect)
{
	// no need to set a wake reason since the system will only send when awake...
	if(uart0Handle.readByteIndexTransmitBuffer != uart0Handle.freeByteIndexTransmitBuffer)
	{
		UDR0 = uart0Handle.transmitBuffer[uart0Handle.readByteIndexTransmitBuffer];
		uart0Handle.readByteIndexTransmitBuffer = (uart0Handle.readByteIndexTransmitBuffer + 1) % UARTBUFFERSIZE; // update the index denoting which bytes are already read from the buffer and thus sent for the buffering mechanism to work
	}
	else
	{
		// nothing to send... 
		UCSR0B &= ~(1<<TXCIE); // ensure the tx complete interrupt does not fire continuously when there is nothing to be send anymore
	}
}
