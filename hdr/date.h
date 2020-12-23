#ifndef DATE_H
#define DATE_H

#include "types.h"

typedef struct{
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    int seconds;
} Date;

status date_setDateToCurrent(Date *date);
void date_printDate(Date date);
status date_setDate(Date *date, int year, int month, int day, int hours, int minutes);

#endif