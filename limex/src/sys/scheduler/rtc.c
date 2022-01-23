#include "sys/scheduler/rtc.h"
#include "sys/io/io.h"

int bcdtobin(int value)
{
    return (value >> 4) * 10 + (value & 15);
}

uint64_t rtc_year()
{
    outb(0x70, 0x09);
    return bcdtobin(inb(0x71));
}

uint64_t rtc_month()
{
    outb(0x70, 0x08);
    return bcdtobin(inb(0x71));
}

uint64_t rtc_day()
{
    outb(0x70, 0x07);
    return bcdtobin(inb(0x71));
}

uint64_t rtc_hour()
{
    outb(0x70, 0x04);
    return bcdtobin(inb(0x71));
}

uint64_t rtc_minute()
{
    outb(0x70, 0x02);
    return bcdtobin(inb(0x71));
}

uint64_t rtc_second()
{
    outb(0x70, 0x00);
    return bcdtobin(inb(0x71));
}
