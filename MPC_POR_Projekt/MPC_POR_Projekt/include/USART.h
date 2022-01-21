/*
 * USART.h
 *
 * Created: 04.03.2021 20:31:52
 *  Author: xkysil01
 */ 

#ifndef USART_H_
#define USART_H_

#include <stdio.h>
#include <avr/interrupt.h>

//#define SET_BAUD 25
#define SET_BAUD 103  //baud rate 9600
#define LED_MASK (1<<5)

volatile uint8_t dataBuffer[32];
volatile uint8_t rxAvailable;
volatile uint8_t rxData;
volatile uint8_t rxDone;
volatile uint8_t rxIndex;


int uart_putchar(char aVar, FILE *stream);

static FILE usart = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void usartInit();
uint8_t usartReceiveDone();
void usartWriteByte(uint8_t data);
uint8_t usartReadByte();
void usartWrite(char* data);
char* usartRead();

#endif /* USART_H_ */