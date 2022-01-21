/*
 * ADC.c
 *
 * Created: 09.03.2021 15:47:08
 *  Author: xkysil01
 */ 

#include "../include/ADC.h"

void initTimerForADC()
{
	/*POZOR!!
	- Timer1 v rezimu CTC dokaze porovnavat pouze s registry OCR1A a ICF1.
	- ADC v autotrigger modu se zase dokaze spoustet na zaklade COMP B u Timer1.
	- Timer1 nastavime tedy tak aby hodnota v OCR1A odpovidala 500 ms a hodnota v OCR1B = 0,
	  dojde k tomu ze timer dopocita do hodnoty OCR1A, zacne s OCR1B kde je 0 -> vysledkem je tedy 500 ms -> spusti se ADC
	- V ADC interrupt se musi resetovat bity OCF1A a OCF1B. (TIFR1 |= (1 << OCF1B) | (1 << OCF1A);)     
	*/
	
	//INIT TIMER for autotrigger ADC
	TCNT1 = 0;
	TCCR1B |= (1 << WGM12);
	OCR1A = 31249;				// 500 ms
	TCCR1B |= (1 << CS12);
}

void ADCInitTriggTimer()
{
	ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << REFS0) | (1 << MUX0);
	ADCSRB = (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0);
	initTimerForADC();
}

void ADCInit()
{
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << REFS0) | (1 << MUX0);
	ADCSRB = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);	// free running mode	
}

void ADC1StartCnv()
{
	ADMUX |= (1 << MUX0);
	ADCSRA |= (1 << ADSC); 
	while(ADCSRA & (1 << ADSC))	//wait until conversion is complete
	{
	
	}
}

void ADC0StartCnv()
{
	ADMUX &= ~(1 << MUX0);
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC))	//wait until conversion is complete
	{
		
	}
}

char* ADCBinVal()
{
	binNumber[10] = 0;
  	for (int i = 9; i >= 0; i--)
	{
		if ((RawADC % 2) == 1)
		{ 
			binNumber[i] = '1'; 
		}
		else 
		{ 
			binNumber[i] = '0';
		}
		RawADC = RawADC/2;
	}
	return binNumber;
		
}

float cnvADC2Temp (int aVal)
{
	float tmpVal = (float)aVal;
	tmpVal = tmpVal*U_REF/1024;											
	tmpVal = (U_REF*R_3 - tmpVal*(R_trim + R_3))/(tmpVal - U_REF);
	tmpVal = log(tmpVal/R_0)/BETA + (1/T_0);
	tmpVal = 1/tmpVal;
	tmpVal = tmpVal - 273.15;
	return tmpVal;
}

ISR(ADC_vect)
{
	RawADC = ADC;
	if (ADMUX & (1 << MUX0))
	{
		temperature = cnvADC2Temp(ADC);
	}	
}

