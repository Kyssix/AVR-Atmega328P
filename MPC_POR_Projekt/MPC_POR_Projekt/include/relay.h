/*
 * relay.h
 *
 * Created: 17.04.2021 15:46:46
 *  Author: xkysil01
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#include <avr/io.h>

#define RELAY_PORT		PORTB
#define HEATING_PIN		(1 << PINB3)
#define COOLING_PIN		(1 << PINB4)

void relayInit();
void relayTempCtrl(float actTemp, float setTemp, float hyst);


#endif /* RELAY_H_ */