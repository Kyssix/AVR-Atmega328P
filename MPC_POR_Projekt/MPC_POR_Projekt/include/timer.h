/*
 * timer.h
 *
 * Created: 25.02.2021 19:20:33
 *  Author: xkysil01
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#define NOP() asm volatile ("nop");

#define LED_MASK (1<<5)

void busyWait(uint32_t time);

void initTimer0();
void delay_ms(uint32_t time_ms);
uint32_t millis();

void initTimer1();
uint32_t getTime();
void delay(uint32_t time_us);

#endif /* TIMER_H_ */