/*
 * lcdScreens.c
 *
 * Created: 16.04.2021 10:16:01
 *  Author: xkysil01
 */

#include "../include/lcdScreens.h"

void showMainScreen()
{
	lcdClear();
	lcdCursorPosition(1,0);
	lcdPrint("Act Temp: ");
	lcdCursorPosition(1,14);
	lcdWriteChar(0xDF);
	lcdWriteChar('C');
	lcdCursorPosition(2,0);
	lcdPrint("Set Temp: ");
	lcdCursorPosition(2,14);
	lcdWriteChar(0xDF);
	lcdWriteChar('C');
}

void showMenuScreen()
{
	lcdClear();
	lcdCursorPosition(1,0);
	lcdPrint("MENU:");
}

void showDateAndTimeScreen()
{
	lcdClear();
	lcdCursorPosition(1,0);
	lcdPrint("Date and Time");
}

uint8_t menuList(uint8_t aItem)
{
	if (aItem < 1)
	{
		//menuState = 3;
		aItem = 3;
	}
	else if (aItem > 3)
	{
		//menuState = 1;
		aItem = 1;
	}
	
	if (aItem == 1)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Hysteresis");
		return 1;
	}
	else if (aItem == 2)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Date and Time");
		return 2;
	}
	else if (aItem == 3)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Temp calibration");
		return 3;
	}
	else
	{
		return 0;
	}
}

void showMenuItemScreen(uint8_t aItem)
{
	if (aItem == 1)					//Hysteresis
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Hysteresis");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
	}
	else if(aItem == 2)				//Date and Time
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Date and Time");
		dateAndTimeList(1);
	}
	else if(aItem == 3)				//Temp calibration
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Temp calibration");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
	}
}

uint8_t dateAndTimeList(uint8_t aItem)
{
	uint8_t lastVal = 0;
	
	if (aItem < 1)
	{
		//menuTimeState = 7;
		aItem = 7;
	}
	else if (aItem > 7)
	{
		//menuTimeState = 1;
		aItem = 1;
	}
	
	if (aItem == 1)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Hour: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetHour();
		fprintf(&display, "%02d", lastVal);
		return 1;
	}
	else if (aItem == 2)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Minutes: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetMinutes();
		fprintf(&display, "%02d", lastVal);
		return 2;
	}
	else if (aItem == 3)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Seconds: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetSecond();
		fprintf(&display, "%02d", lastVal);
		return 3;
	}
	else if (aItem == 4)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Day: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetDay();
		fprintf(&display, "%s", rtcGetDayString());
		return 4;
	}
	else if (aItem == 5)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Date: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetDate();
		fprintf(&display, "%d", lastVal);
		return 5;
	}
	else if (aItem == 6)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Month: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetMonth();
		fprintf(&display, "%d", lastVal);
		return 6;
	}
	else if (aItem == 7)
	{
		lcdCursorPosition(2,0);
		lcdClearRow(2);
		lcdPrint("Year: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetYearInt8();
		fprintf(&display, "%d", 2000 + lastVal);
		return 7;
	}
	else
	{
		return 0;
	}
}

uint8_t showDateAndTimeItemScreen(uint8_t aItem)
{
	uint8_t lastVal = 0;	
	if (aItem == 1)							//Hour
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Hour");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetHour();
		fprintf(&display, "%02d", lastVal);
		return lastVal;
	}
	else if (aItem == 2)					//Minutes
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Minutes");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetMinutes();
		fprintf(&display, "%02d", lastVal);
		return lastVal;
	}
	else if (aItem == 3)					//Seconds
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Seconds");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetSecond();
		fprintf(&display, "%02d", lastVal);
		return lastVal;
	}
	else if (aItem == 4)					//Day
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Day");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetDay();
		fprintf(&display, "%s", rtcGetDayString());
		return lastVal;
	}
	else if (aItem == 5)					//Date
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Date");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetDate();
		fprintf(&display, "%d", lastVal);
		return lastVal;
	}
	else if (aItem == 6)					//Month
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Month");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetMonth();
		fprintf(&display, "%d", lastVal);
		return lastVal;
	}
	else if (aItem == 7)					//Year
	{
		lcdClear();
		lcdCursorPosition(1,0);
		lcdPrint("Year");
		lcdCursorPosition(2,0);
		lcdPrint("Set val: ");
		lcdCursorPosition(2,10);
		lastVal = rtcGetYearInt8();
		fprintf(&display, "%d", 2000 + lastVal);
		return lastVal;
	}
	else
	{
		return 0;
	}
}

uint8_t updateDateAndTimeValue(uint8_t aItem, uint8_t aLastVal)
{
	
	if (aItem == 1 )						//Hour
	{
		if (aLastVal < 0)
		{
			aLastVal = 23;
		}
		else if(aLastVal > 23)
		{
			aLastVal = 0;
		}
		lcdCursorPosition(2,10);
		fprintf(&display, "%02d", aLastVal);
		return aLastVal;
	}
	else if (aItem == 2 || aItem == 3)		//Minutes and Second
	{
		if (aLastVal < 0)
		{
			aLastVal = 59;
		}
		else if(aLastVal > 59)
		{
			aLastVal = 0;
		}
		lcdCursorPosition(2,10);
		fprintf(&display, "%02d", aLastVal);
		return aLastVal;		
	}
	else if (aItem == 4)					//Day
	{
		if (aLastVal < 1)
		{
			aLastVal = 7;
		}
		else if(aLastVal > 7)
		{
			aLastVal = 1;
		}
		lcdCursorPosition(2,10);
		fprintf(&display, "%s", rtcDayToString(aLastVal));
		return aLastVal;		
	}
	else if (aItem == 5)					//Date
	{
		if (aLastVal < 1)
		{
			aLastVal = 31;
		}
		else if(aLastVal > 31)
		{
			aLastVal = 1;
		}
		lcdCursorPosition(2,10);
		fprintf(&display, "%02d", aLastVal);
		return aLastVal;
	}
	else if (aItem == 6)					//Month
	{
		if (aLastVal < 1)
		{
			aLastVal = 12;
		}
		else if(aLastVal > 12)
		{
			aLastVal = 1;
		}
		lcdCursorPosition(2,10);
		fprintf(&display, "%02d", 2000 + aLastVal);
		return aLastVal;
	}
	else if (aItem == 7)					//Year
	{
		lcdCursorPosition(2,10);
		fprintf(&display, "%d", 2000 + aLastVal);
		return aLastVal;
	}
	else
	{
		return 0;
	}
}
