/*
 * i2c.c
 *
 *  Created: 30.03.2021 18:14:26
 *  Author: xkysil01
 */ 

#include "../include/i2c.h"
#include "../include/timer.h"

void i2cInit()
{
	TWSR = 0x00;
	TWBR = 0x48;
	TWCR = (1 << TWEN);
}

void i2cStart()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while((TWCR & (1 << TWINT)) == 0);
}

void i2cWrite(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while((TWCR & (1 << TWINT)) == 0);
}

uint8_t i2cRead()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

void i2cStop()
{	
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t i2cStatusCode()
{
	return (TWSR & 0xF8); // upper 5 bits
}


