#ifndef RTC_H
#define RTC_H

#include <stdint.h>

uint64_t rtc_year();
uint64_t rtc_month();
uint64_t rtc_day();
uint64_t rtc_hour();
uint64_t rtc_minute();
uint64_t rtc_second();

#endif