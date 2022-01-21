/*
 * rtc.h
 *
 * Created: 31.03.2021 16:54:56
 *  Author: kysil
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>

#define RTC_WRITE_ADDRESS 0xD0
#define RTC_READ_ADDRESS 0xD1

volatile uint8_t clockFlag;

uint8_t DecToBCD(uint8_t aVal);
uint8_t BCDToDec(uint8_t aVal);

void rtcInit();
uint8_t rtcRead(uint8_t memAddress);
void rtcSetTime(uint8_t hour, uint8_t minute, uint8_t second);
void rtcSetDate(uint8_t day, uint8_t date, uint8_t month, int year);
void rtcSetDateAndTime(uint8_t day, uint8_t date, uint8_t month, int year, uint8_t hour, uint8_t minute, uint8_t second);

uint8_t rtcGetSecond();
uint8_t rtcGetMinutes();
uint8_t rtcGetHour();
uint8_t rtcGetDay();
char* rtcDayToString(uint8_t aDay);
char* rtcGetDayString();
uint8_t rtcGetDate();
uint8_t rtcGetMonth();
uint16_t rtcGetYear();
uint8_t rtcGetYearInt8();

char* rtcReadTime();
char* rtcReadDate();

void rtcSQWESet();

#endif /* RTC_H_ */