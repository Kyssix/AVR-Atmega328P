/*
 * USART.c
 *
 * Created: 04.03.2021 20:33:20
 *  Author: xkysil01
 */ 
#include "../include/usart.h"

int uart_putchar(char aVar, FILE *stream)
{
	if (aVar == '\n')
	{
		uart_putchar('\r', stream);
	}
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = aVar;
	return 0;
}

void usartInit()
{
	//Setting the Baud rate
	UBRR0H = (SET_BAUD >> 8);
	UBRR0L = (SET_BAUD);
	// no parity bit, 1 stop bit, 8 bit selection
	UCSR0C = (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
	// Enable transmission
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	
	rxData = 0;
	rxDone = 0;
	rxIndex = 0;
	rxAvailable = 0;
}

uint8_t usartReceiveDone()
{
	if (rxDone)
	{
		rxDone = 0;
		return 1; 	
	}
	else
	{
		return 0;
	}
}

void usartWriteByte(uint8_t data)
{
	while((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = data;
}

uint8_t usartReadByte()
{
	while((UCSR0A & (1 << RXC0)) == 0);
	return UDR0;
}

void usartWrite(char* data)
{
	int i = 0;
	while(data[i] != 0)
	{
		usartWriteByte(data[i++]);
	}
}

char* usartRead()
{
	return dataBuffer;	
}

ISR(USART_RX_vect)
{
	rxData = UDR0;
	
	if (rxData == '{')
	{
		rxAvailable = 0;
	}
	
	if (rxData != '}')
	{
		dataBuffer[rxIndex++] = rxData;
	}
	else
	{
		dataBuffer[rxIndex++] = rxData;
		dataBuffer[rxIndex] = '\0';
		rxAvailable = 1;
		rxIndex = 0;
	}
	
	/*rxDone = 0;	
	rxData = UDR0;	
	
	if (rxData == '\n')
	{
		rxDone = 1; 
		dataBuffer[rxIndex] = '\0';
		rxIndex = 0;
		rxData = UDR0;
	}
	
	if (rxData != '\r')
	{
		dataBuffer[rxIndex++] = rxData;
	}*/
}


