/*
 * MPC_POR_Projekt.c
 *
 * Created: 12.04.2021 18:24:56
 * Author : xkysil01
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/lcd.h"
#include "include/i2c.h"
#include "include/timer.h"
#include "include/rtc.h"
#include "include/usart.h"
#include "include/ADC.h"
#include "include/lcdScreens.h"
#include "include/relay.h"

char* str;
char usartBuffer[32];
uint8_t btnState;
uint8_t menuState;
uint8_t menuTimeState;
uint8_t lastTimeVal;
uint8_t dispShifted;

float actualTemp;
float hysteresis;
float tempCalibration;
float setTemp;

enum screen{mainScreen, menuScreen, subMenuScreen, dateAndTimeScreen};

int main(void)
{
	initTimer0();
	lcdInit();
	i2cInit();
	rtcInit();
	usartInit();
	ADCInit();
	relayInit();
	sei();	

	rtcSetDateAndTime(5, 16, 4, 2021, 12, 0, 22);
	rtcSQWESet();
	
	showMainScreen();
		
	setTemp = 23.0;
	hysteresis = 1.0;
	tempCalibration = 0.0;
	
	/*if(memoryRead8(0) == 1)
	{
		hysteresis = (float)memoryRead32(1);
		tempCalibration = (float)memoryRead32(5);
	}*/
	
	enum screen activeScreen = 0;
	
	btnState = 0;
	menuState = 1;
	menuTimeState = 0;
	dispShifted = 0;
		
	lastTimeVal = 0;
	uint32_t setTime1 = millis();
	uint32_t setTime2 = millis();

	while (1)
	{
		btnState = lcdBtnPressState();
		actualTemp = temperature + tempCalibration;
		
		if ((millis() - setTime2) > 1000)
		{
			relayTempCtrl(actualTemp, setTemp, hysteresis);
			setTime2 = millis();
		}
					
		/*if (usartReceiveDone())
		{
			int hour, min, sec, date, month, day, year;
			
			str = usartRead();
			sscanf(str, "t#%d:%d:%d", &hour, &min, &sec);
			rtcSetTime((uint8_t)hour, (uint8_t)min, (uint8_t)sec);
		}*/
		
		switch (activeScreen)
		{
		case mainScreen:
		
			lcdCursorPosition(2,10);
			fprintf(&display, "%.1f", setTemp);
			
			if ((millis() - setTime1) > 200)
			{
				ADC1StartCnv();
				lcdCursorPosition(1,10);
				fprintf(&display, "%.1f", temperature + tempCalibration);
							
				setTime1 = millis();
			}
			
			if (clockFlag == 1)
			{
				clockFlag = 0;
				lcdCursorPosition(1,16);
				fprintf(&display, "%02d:%02d:%02d", rtcGetHour(), rtcGetMinutes(), rtcGetSecond());
				lcdCursorPosition(2,16);
				fprintf(&display, "%s %d.%d.%d", rtcGetDayString(), rtcGetDate(), rtcGetMonth(), rtcGetYear());
			}
			
			switch (btnState)
			{
			case 0:
				break;
			case 1:
				if(!dispShifted)
				{
					dispShifted = lcdDisplayShift(1,16);
				}				
				break;
			case 2:
				setTemp += 0.1;
				break;
			case 3:
				setTemp -= 0.1;
				break;
			case 4:
				if (dispShifted)
				{
					dispShifted = lcdDisplayShift(0,16);
				}				
				break;
			case 5:
				showMenuScreen();
				menuState = 1;
				menuState = menuList(menuState);
				activeScreen = menuScreen;
				break;
			}
			break;
						
		case menuScreen:
			
			switch (btnState)
			{
			case 0:
				break;
			case 1:
				activeScreen = subMenuScreen;
				showMenuItemScreen(menuState);
				menuTimeState = 1;
				break;
			case 2:
				menuState -= 1; 
				menuState = menuList(menuState);
				break;
			case 3:
				menuState += 1;
				menuState = menuList(menuState);
				break;
			case 4:
				showMainScreen();
				activeScreen = mainScreen;
				break;
			case 5:
				showMainScreen();
				activeScreen = mainScreen;
				break;
			}
			break;
		
		case subMenuScreen:
		
			switch (menuState)
			{
			case 1:	//Hysteresis setting value
			
				lcdCursorPosition(2,10);			
				fprintf(&display, "%.1f ", hysteresis);
				
				switch (btnState)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					hysteresis += 0.1;
					break;
				case 3:
					hysteresis -= 0.1;
					break;
				case 4:
					memoryWrite8(0,1);
					memoryWrite32(1, (uint32_t)hysteresis);
					showMenuScreen();
					menuList(menuState);
					activeScreen = menuScreen;
					break;
				case 5:
					showMainScreen();
					activeScreen = mainScreen;
					break;
				}
				break;
				
			case 2:	//Date and time setting value
				
				switch (btnState)
				{
				case 0:
					break;
				case 1:
					activeScreen = dateAndTimeScreen;
					lastTimeVal = showDateAndTimeItemScreen(menuTimeState);
					break;
				case 2:
					menuTimeState -= 1;
					menuTimeState = dateAndTimeList(menuTimeState);
					break;
				case 3:
					menuTimeState += 1;
					menuTimeState = dateAndTimeList(menuTimeState);
					break;
				case 4:
					showMenuScreen();
					menuList(menuState);
					activeScreen = menuScreen;
					break;
				case 5:
					showMainScreen();
					activeScreen = mainScreen;
					break;
				}
				break;
				
			case 3: //Temperature calibration setting value
				
				lcdCursorPosition(2,10);
				fprintf(&display, "%.1f ", tempCalibration);
								
				switch (btnState)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					tempCalibration += 0.1;
					break;
				case 3:
					tempCalibration -= 0.1;
					break;
				case 4:
					memoryWrite8(0,1);
					memoryWrite32(5, (uint32_t)tempCalibration);
					showMenuScreen();
					menuList(menuState);
					activeScreen = menuScreen;
					break;
				case 5:
					showMainScreen();
					activeScreen = mainScreen;
					break;
				}				
				break;
			}
			break;
					
		case dateAndTimeScreen:
													
			switch (btnState)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				lastTimeVal += 1;
				lastTimeVal = updateDateAndTimeValue(menuTimeState, lastTimeVal);
				break;
			case 3:
				lastTimeVal -= 1;
				lastTimeVal = updateDateAndTimeValue(menuTimeState, lastTimeVal);	
				break;
			case 4:				
				if (menuTimeState == 1)						//Hour
				{
					rtcSetTime(lastTimeVal, rtcGetMinutes(), rtcGetSecond());
				}
				else if (menuTimeState == 2)				//Minutes
				{
					rtcSetTime(rtcGetHour(), lastTimeVal, rtcGetSecond());
				}
				else if (menuTimeState == 3)				//Seconds
				{
					rtcSetTime(rtcGetHour(), rtcGetMinutes(), lastTimeVal);
				}
				else if (menuTimeState == 4)				//Day
				{
					rtcSetDate(lastTimeVal, rtcGetDate(), rtcGetMonth(), rtcGetYear());
				}
				else if (menuTimeState == 5)				//Date
				{
					rtcSetDate(rtcGetDay(), lastTimeVal, rtcGetMonth(), rtcGetYear());
				}
				else if (menuTimeState == 6)				//Month
				{
					rtcSetDate(rtcGetDay(), rtcGetDate(), lastTimeVal, rtcGetYear());
				}
				else if (menuTimeState == 7)				//Year
				{
					rtcSetDate(rtcGetDay(), rtcGetDate(), rtcGetMonth(), 2000 + lastTimeVal);
				}
				showDateAndTimeScreen();
				dateAndTimeList(menuTimeState);
				activeScreen = subMenuScreen;
				break;
			case 5:	//Acknowledge settings
				showMainScreen();
				activeScreen = mainScreen;
				break;
			}				
			break;			
		}
	}
}

ISR(PCINT1_vect)
{
	if (!(PINC & (1 << PINC3)))
	{
		clockFlag = 1;
	}	
}

