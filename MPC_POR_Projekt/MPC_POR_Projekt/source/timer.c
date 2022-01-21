/*
 * timer.c
 *
 * Created: 25.02.2021 19:25:26
 *  Author: xkysil01
 */ 

#include "../include/timer.h"

static volatile uint16_t timer1OverFlowCount = 0;
static volatile uint32_t timer0Count_ms = 0;
static volatile uint32_t timerMillis = 0;

void busyWait(uint32_t time)
{
	for (; time != 1; --time)
	{		
		NOP();
		NOP();
		NOP();
		NOP();
		NOP();
		NOP();
	}		
}

//================ TIMER 0 ===========================

void initTimer0()
{
	TCCR0A |= (0 << WGM02) | (1 << WGM01) | (0 << WGM00);
	TCNT0 = 0;
	OCR0A = 249;							// 1 ms
	TIMSK0 |= (1 << OCIE0A);
	TCCR0B |= (1 << CS01) | (1 << CS00);	// max value 1.024 ms
}

void delay_ms(uint32_t time_ms)
{
	timer0Count_ms = 0;
	while (timer0Count_ms != time_ms)
	{
		
	}	
}

uint32_t millis()
{
	return timerMillis;
}

ISR(TIMER0_COMPA_vect)
{
	timer0Count_ms++;
	timerMillis++;
}

//================ TIMER 1 ===========================

/*void initTimer1()
{
	TCNT1 = 0;
	TCCR1B = (1 << CS11);
	TIMSK1 = (1 << TOIE1);
}

uint32_t getTime()
{
	uint32_t count = timer1OverFlowCount;
	uint32_t time_us = (count << 16) + TCNT1;
	return time_us;
}
	

void delay(uint32_t time_us)
{
	time_us = (time_us - 17) << 1;
	uint32_t actualTime = getTime();
	uint32_t setTime = actualTime + time_us;
	
	while(setTime >= actualTime)
	{
		actualTime = getTime();
	}		
}

ISR(TIMER1_OVF_vect)
{
	timer1OverFlowCount++;
}*/