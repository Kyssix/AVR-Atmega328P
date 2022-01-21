/*
 * ADC.h
 *
 * Created: 09.03.2021 15:46:45
 *  Author: xkysil01
 */ 


#ifndef ADC_H_
#define ADC_H_

#define BETA 3895
#define R_0 10000
#define R_3 1500
#define T_0 298.15
#define R_trim 20000
#define U_REF 5

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <math.h>

volatile float temperature;
volatile uint16_t RawADC;
char binNumber[10];


void initTimerForADC();
void ADCInitTriggTimer();

void ADCInit();
void ADC1StartCnv();
void ADC0StartCnv();
char* ADCBinVal();

float cnvADC2Temp (int aVal);


#endif /* ADC_H_ */