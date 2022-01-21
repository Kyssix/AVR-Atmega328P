/*
 * lcdScreens.h
 *
 * Created: 16.04.2021 10:16:15
 *  Author: xkysil01
 */ 


#ifndef LCDSCREENS_H_
#define LCDSCREENS_H_

#include <avr/io.h>
#include "../include/lcd.h"
#include "../include/rtc.h"

void showMainScreen();
void showMenuScreen();
void showDateAndTimeScreen();

uint8_t menuList(uint8_t aItem);
void showMenuItemScreen(uint8_t aItem);
uint8_t dateAndTimeList(uint8_t aItem);
uint8_t showDateAndTimeItemScreen(uint8_t aItem);
uint8_t updateDateAndTimeValue(uint8_t aItem, uint8_t aLastVal);

#endif /* LCDSCREENS_H_ */