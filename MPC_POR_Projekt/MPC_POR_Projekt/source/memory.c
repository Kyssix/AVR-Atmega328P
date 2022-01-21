/*
 * memory.c
 *
 * Created: 31.03.2021 16:24:59
 *  Author: xkysil01
 */ 

#include "../include/memory.h"

void memoryWrite8(uint16_t memAddress, uint8_t data)
{
	//while(EECR & (1 << EEPE));
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cWrite(data);
	i2cStop();
	busyWait(1000);		
}

uint8_t memoryRead8(uint16_t memAddress)
{
	//while(EECR & (1 << EEPE));
	uint8_t data = 0;
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cStart();
	i2cWrite(MEMORY_READ_ADDRESS);
	data = i2cRead();
	i2cStop();
	busyWait(1000);
	return data;
}

void memoryWrite16(uint16_t memAddress, uint16_t data)
{
	while(EECR & (1 << EEPE));
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cWrite(data);
	i2cStop();	
}

uint16_t memoryRead16(uint16_t memAddress)
{
	uint16_t data = 0;
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cStart();
	i2cWrite(MEMORY_READ_ADDRESS);
	data = ((uint16_t)i2cRead() << 8);
	data += i2cRead();
	i2cStop();
	return data;
}

void memoryWrite32(uint16_t memAddress, uint32_t data)
{
	while(EECR & (1 << EEPE));
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cWrite(data >> 24);
	i2cWrite(data >> 16);
	i2cWrite(data >> 8);
	i2cWrite(data);
	i2cStop();
}

uint32_t memoryRead32(uint16_t memAddress)
{
	uint32_t data = 0;
	i2cStart();
	i2cWrite(MEMORY_WRITE_ADDRESS);
	i2cWrite(memAddress >> 8);
	i2cWrite(memAddress);
	i2cStart();
	i2cWrite(MEMORY_READ_ADDRESS);
	data = ((uint32_t)i2cRead() << 24);
	data += ((uint32_t)i2cRead() << 16);
	data += ((uint32_t)i2cRead() << 8);
	data += i2cRead();
	i2cStop();
	return data;
}