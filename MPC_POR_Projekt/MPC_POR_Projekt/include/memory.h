/*
 * memory.h
 *
 * Created: 31.03.2021 16:24:47
 *  Author: xkysil01
 */ 


#ifndef MEMORY_H_
#define MEMORY_H_

#include <avr/io.h>
#include "../include/i2c.h"
#include "../include/timer.h"


#define MEMORY_WRITE_ADDRESS 0xA0
#define MEMORY_READ_ADDRESS 0xA1

void memoryWrite8(uint16_t memAddress, uint8_t data);
uint8_t memoryRead8(uint16_t memAddress);

void memoryWrite16(uint16_t memAddress, uint16_t data);
uint16_t memoryRead16(uint16_t memAddress);

void memoryWrite32(uint16_t memAddress, uint32_t data);
uint32_t memoryRead32(uint16_t memAddress);


#endif /* MEMORY_H_ */