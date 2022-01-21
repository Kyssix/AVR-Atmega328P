/*
 * i2c.h
 *
 * Created: 30.03.2021 18:12:20
 *  Author: xkysil01
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

void i2cInit();
void i2cStart();
void i2cWrite(uint8_t data);
uint8_t i2cRead();
uint8_t i2cStatusCode();
void i2cStop();

#endif /* I2C_H_ */