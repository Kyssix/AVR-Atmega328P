/*
 * lcd.c
 *
 * Created: 12.03.2021 11:38:33
 *  Author: xkysil01
 */ 

#include "../include/lcd.h"

void lcdInit()
{
	DDRD |=  (1 << LCD_D7) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4);
	DDRB |=  (1 << LCD_EN) | (1 << LCD_RS) | (1 << LCD_BCKL);
	PORTB |= (1 << LCD_BCKL);

	lcdSet(LCD_FUNC_4BIT_2LINE);
	lcdSet(LCD_DISPLAY_OFF);
	lcdSet(LCD_CLEAR);
	lcdSet(LCD_HOME);
	lcdSet(LCD_ENTRY_MODE);
	lcdSet(LCD_DISPLAY_ON);
}

int lcd_putchar(uint8_t aVar, FILE *stream)
{
	if (aVar == '\n')
	{
		lcdWriteChar('\r');
	}
	lcdWriteChar(aVar);
	return 0;
}


void lcdSet(uint8_t aVal)
{
	PORTD = aVal;
	PORTB |= (1 << LCD_EN);
	busyWait(1);
	PORTB &= ~(1 << LCD_EN);
	busyWait(1);
	
	PORTD = (aVal << 4);
	PORTB |= (1 << LCD_EN);
	busyWait(1);
	PORTB &= ~(1 << LCD_EN);
	
	busyWait(2000);
}

void lcdClear()
{
	lcdSet(LCD_CLEAR);
	lcdSet(LCD_HOME);
}

void lcdClearRow(uint8_t row)
{
	lcdCursorPosition(row,0);
	lcdPrint("                ");
	lcdCursorPosition(row,0);
}

void lcdDisplaySettings(uint8_t on_off, uint8_t show, uint8_t blink) 
{
	if ((on_off == 1) && (show == 1) && (blink == 1)) { lcdSet(0x0F); }
	else if ((on_off == 1) && (show == 1) && (blink == 0)) { lcdSet(0x0E); }
	else if ((on_off == 1) && (show == 0)) { lcdSet(LCD_DISPLAY_ON); }	
	else if ((on_off == 0)) { lcdSet(LCD_DISPLAY_OFF); }		
}

void lcdWriteChar(uint8_t ch)
{
	PORTB |= (1 << LCD_RS);
	
	lcdSet(ch);
	
	PORTB &= ~(1 << LCD_RS);
	
}

void lcdPrint(char *str)
{
	PORTB |= (1 << LCD_RS);
	
	for(uint8_t i=0; str[i]!=0 ; i++)
	{
		lcdSet(str[i]);
	}
	
	PORTB &= ~(1 << LCD_RS);
}

void lcdCursorPosition(uint8_t line, uint8_t pos)
{
	if(line == 1)
	{
		lcdSet(LCD_SET_LINE_1);
		for(; pos!= 0; pos--)
		{
			lcdSet(LCD_SHIFT_CURSOR_R);
		}
	}
	else if (line == 2)
	{
		lcdSet(LCD_SET_LINE_2);
		for(; pos!= 0; pos--)
		{
			lcdSet(LCD_SHIFT_CURSOR_R);
		}
	}
}


uint8_t lcdDisplayShift(uint8_t direction, uint8_t offset) 
{
	if (direction)
	{
		for(; offset !=0; offset--)
		{
			lcdSet(LCD_SHIFT_DISPLAY_L);
		}
		return 1;
	}
	else
	{
		for(; offset !=0; offset--)
		{
			lcdSet(LCD_SHIFT_DISPLAY_R);
		}
		return 0;
	}	
}

uint8_t lcdBtnPress(int aADC)
{
	if (aADC < 50){lcdPrint("Right "); }
	else if (aADC < 170){lcdPrint("Up    "); }
	else if (aADC < 350){lcdPrint("Down  "); }
	else if (aADC < 550){lcdPrint("Left  "); }
	else if (aADC < 800){lcdPrint("Select"); }
	else { lcdPrint("None  "); }
}

uint8_t lcdBtnPressState()
{
	ADC0StartCnv();
	if (ADC < 50)				//Right
	{
		busyWait(200000); 
		return 1; 
	}			
	else if (ADC < 170)			//Up
	{ 
		busyWait(200000);
		return 2; 
	}	
	else if (ADC < 350)			//Down
	{ 
		busyWait(200000);
		return 3; 		
	}	
	else if (ADC < 550)			//Left
	{ 
		busyWait(200000);
		return 4; 
	}	
	else if (ADC < 800)			//Select
	{ 
		busyWait(200000);
		return 5; 
	}	
	else
	{ 
		//busyWait(200000);
		return 0; 
	}					
}
