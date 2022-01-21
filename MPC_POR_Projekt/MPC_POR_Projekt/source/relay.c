/*
 * relay.c
 *
 * Created: 17.04.2021 15:48:05
 *  Author: xkysil01
 */ 

#include "../include/relay.h"

void relayInit()
{
	DDRB |= (1 << PINB3) | (1 << PINB4);
	RELAY_PORT |= HEATING_PIN;
	RELAY_PORT |= COOLING_PIN;
}

void relayTempCtrl(float actTemp, float setTemp, float hyst)
{
	if ((actTemp < (setTemp + 0.1)) && (actTemp > (setTemp - 0.1)))
	{
		RELAY_PORT |= HEATING_PIN;
		RELAY_PORT |= COOLING_PIN;
	}
	else if (actTemp > (setTemp + hyst/2))
	{
		RELAY_PORT |= HEATING_PIN;
		RELAY_PORT &= ~COOLING_PIN;
	}
	else if (actTemp < (setTemp - hyst/2))
	{
		RELAY_PORT &= ~HEATING_PIN;
		RELAY_PORT |= COOLING_PIN;
	}
} 