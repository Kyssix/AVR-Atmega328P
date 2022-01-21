/*
 * lcd.h
 *
 * Created: 12.03.2021 11:36:04
 *  Author: xkysil01
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include "../include/timer.h"
#include <stdio.h>

#define LCD_D4 4											// PORT D
#define LCD_D5 5											// PORT D
#define LCD_D6 6											// PORT D
#define LCD_D7 7											// PORT D

#define LCD_RS 0											// PORT B
#define LCD_EN 1											// PORT B
#define LCD_BCKL 2											// PORT B

#define LCD_TEMP_VAL_POS 9									// temperature value position
#define LCD_ADC_VAL_POS 21									// ADC value position
#define LCD_BTN_VAL_POS 5									// button value position
#define LCD_BTN_NAME_POS 21									// button value position

#define LCD_CLEAR						0b00000001          // clear display
#define LCD_HOME						0b00000010			// return cursor home
#define LCD_ENTRY_MODE					0b00000110          // shift cursor from left to right
#define LCD_DISPLAY_OFF					0b00001000			// turn display off
#define LCD_DISPLAY_ON					0b00001100          // display on, cursor off, blink cursor position off
#define LCD_FUNC_4BIT_2LINE				0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define LCD_RESET						0b00110000          // reset the LCD
#define	LCD_SHIFT_CURSOR_R				0b00010100			// shift cursor to right
#define	LCD_SHIFT_CURSOR_L				0b00010000			// shift cursor to left
#define	LCD_SHIFT_DISPLAY_R				0b00011100			// shift display to right
#define	LCD_SHIFT_DISPLAY_L				0b00011000			// shift display to left
#define	LCD_SET_LINE_1					0b10000000			// Set cursor to line 1
#define	LCD_SET_LINE_2					0b11000000			// Set cursor to line 2

int lcd_putchar(uint8_t aVar, FILE *stream);

static FILE display = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

/*Initialize display */
void lcdInit(); 

/*Set the property*/
void lcdSet(uint8_t aVal);

/*Clear display*/
void lcdClear();

void lcdClearRow(uint8_t row);

/*Choose display settings
  on_off = 1 -> display on; on_off = 0 -> display off
  show = 1 -> show cursor on display; show = 0 -> hide cursor on display
  blink = 1 -> enable blinking cursor; blink = 0 -> disable blinking cursor 
*/
void lcdDisplaySettings(uint8_t on_off, uint8_t show, uint8_t blink);

/*Send character to display*/
void lcdWriteChar(uint8_t ch);

/*Send string to display*/
void lcdPrint(char *str);

/*Set cursor position*/
void lcdCursorPosition(uint8_t line, uint8_t pos);

/*Shift display
  direction = 1 -> shift display to left; direction = 0 -> shift display to right;
  set offset (range 0 - 40)
*/
uint8_t lcdDisplayShift(uint8_t direction, uint8_t offset);

/*Print name of pressed button*/
uint8_t lcdBtnPress(int aADC);
uint8_t lcdBtnPressState();

#endif /* LCD_H_ */