/*
 * rtc.c
 *
 * Created: 31.03.2021 16:54:42
 *  Author: xkysil01
 */ 

#include "../include/rtc.h"
#include "../include/i2c.h"
#include <stdio.h>

uint8_t DecToBCD(uint8_t aVal)
{
	return (aVal + 6 * (aVal / 10));
}

uint8_t BCDToDec(uint8_t aVal)
{
	return (aVal - 6 * (aVal >> 4));
}

void rtcInit()
{
	DDRC |= (0 << PINC3) | (0 << PINC4) | (0 << PINC5);
	PORTC |= (1 << PINC3) | (1 << PINC4) | (1 << PINC5);
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT11); //PC3

	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x00);
	i2cWrite(0x00);
	i2cStop();
	
	clockFlag = 0;
}

uint8_t rtcRead(uint8_t memAddress)
{
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(memAddress);
	i2cStart();
	i2cWrite(RTC_READ_ADDRESS);
	uint8_t data = i2cRead();
	i2cStop();
	return data;
}

void rtcSetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x00);
	i2cWrite(DecToBCD(second));
	i2cWrite(DecToBCD(minute));
	i2cWrite(DecToBCD(hour));
	i2cStop();
}

void rtcSetDate(uint8_t day, uint8_t date, uint8_t month, int year)
{
	uint8_t y = (uint8_t)(year - 2000);
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x03);
	i2cWrite(DecToBCD(day));
	i2cWrite(DecToBCD(date));
	i2cWrite(DecToBCD(month));
	i2cWrite(DecToBCD(y));
}

void rtcSetDateAndTime(uint8_t day, uint8_t date, uint8_t month, int year, uint8_t hour, uint8_t minute, uint8_t second)
{
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x00);
	i2cWrite(DecToBCD(second));
	i2cWrite(DecToBCD(minute));
	i2cWrite(DecToBCD(hour));
	i2cStop();

	uint8_t y = (uint8_t)(year - 2000);
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x03);
	i2cWrite(DecToBCD(day));
	i2cWrite(DecToBCD(date));
	i2cWrite(DecToBCD(month));
	i2cWrite(DecToBCD(y));
}

uint8_t rtcGetSecond()
{
	uint8_t data;
	data = rtcRead(0x00) & (0x70);
	data += rtcRead(0x00) & (0x0F);
	return BCDToDec(data);
	
}

uint8_t rtcGetMinutes()
{
	uint8_t data;
	data = rtcRead(0x01) & (0x70);
	data += rtcRead(0x01) & (0x0F);
	return BCDToDec(data);
}

uint8_t rtcGetHour()
{
	uint8_t data;
	data = rtcRead(0x02) & (0x30);
	data += rtcRead(0x02) & (0x0F);
	return BCDToDec(data);
}

uint8_t rtcGetDay()
{
	uint8_t day;
	day = rtcRead(0x03) & (0x07);
	day = BCDToDec(day);
	return day;
}

char* rtcDayToString(uint8_t aDay)
{
	char* str;
	
	switch (aDay)
	{
		case 1:
		str = "Mon";
		break;
		case 2:
		str = "Tue";
		break;
		case 3:
		str = "Wed";
		break;
		case 4:
		str = "Thu";
		break;
		case 5:
		str = "Fri";
		break;
		case 6:
		str = "Sat";
		break;
		case 7:
		str = "Sun";
		break;
		default:
		str = "Mon";
		break;
	}
	return str;
}

char* rtcGetDayString()
{
	uint8_t day;
	day = rtcRead(0x03) & (0x07);
	day = BCDToDec(day);

	char* str;
	
	switch (day)
	{
		case 1:
			str = "Mon";
			break;
		case 2:
			str = "Tue";
			break;
		case 3:
			str = "Wed";
			break;
		case 4:
			str = "Thu";
			break;
		case 5:
			str = "Fri";
			break;
		case 6:
			str = "Sat";
			break;
		case 7:
			str = "Sun";
			break;
		default:
			str = "Mon";
			break;
	}
	return str;
}

uint8_t rtcGetDate()
{
	uint8_t data;
	data = rtcRead(0x04) & (0x30);
	data += rtcRead(0x04) & (0x0F);
	return BCDToDec(data);
}

uint8_t rtcGetMonth()
{
	uint8_t data;
	data = rtcRead(0x05) & (0x10);
	data += rtcRead(0x05) & (0x0F);
	return BCDToDec(data);
}

uint16_t rtcGetYear()
{
	uint8_t data;
	data = rtcRead(0x06) & (0xF0);
	data += rtcRead(0x06) & (0x0F);
	return 2000 + BCDToDec(data);
}

uint8_t rtcGetYearInt8()
{
	uint8_t data;
	data = rtcRead(0x06) & (0xF0);
	data += rtcRead(0x06) & (0x0F);
	return BCDToDec(data);
}

char* rtcReadTime()
{
	char* str;
	sprintf(str, "%d:%d:%d ", rtcGetHour(), rtcGetMinutes(), rtcGetSecond());
	return str;
}

char* rtcReadDate()
{
	char* str;
	sprintf(str, "%s %d.%d.%d", rtcGetDay(), rtcGetDate(), rtcGetMonth(), rtcGetYear());
	return str;
}

void rtcSQWESet()
{
	i2cStart();
	i2cWrite(RTC_WRITE_ADDRESS);
	i2cWrite(0x07);
	i2cWrite(0x10);
	i2cStop();
}

