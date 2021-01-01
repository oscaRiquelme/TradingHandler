#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "date.h"

status date_setDateToCurrent(Date *date){
    
    time_t now;
    struct tm *local;
    
    time(&now);

    local = localtime(&now);

    date->hours = local->tm_hour;          /* get hours since midnight (0-23) */
    date->minutes = local->tm_min;         /* get minutes passed after the hour (0-59) */
    date->seconds = local->tm_sec;         /* get seconds passed after minute (0-59) */
    date->day = local->tm_mday;            /* get day of month (1 to 31) */
    date->month = local->tm_mon + 1;       /* get month of year (0 to 11) */ 
    date->year = local->tm_year + 1900;    /* get year since 1900 */
    
    return OK;
}

void date_printDate(Date date, FILE *f){

    if(!f) return;
    fprintf(f, "%02d/%02d/%d ", date.day, date.month, date.year);

    if (date.hours < 12)    /* before midday */
        fprintf(f, "%02d:%02d:%02d am\n", date.hours, date.minutes, date.seconds);
 
    else    /* after midday */
        fprintf(f, "%02d:%02d:%02d pm\n", date.hours - 12, date.minutes, date.seconds);
 
    
}

status date_setDate(Date *date, int year, int month, int day, int hours, int minutes){

    if(!date || year < 2020 || month < 1 || month > 12 || day < 1 || day > 31 || hours > 23 || hours < 0 || minutes < 0 || minutes > 59){
        printf("Wrong arguments passed to set a date, returning error...");
        return ERR;
    }

    date->minutes = minutes;
    date->hours = hours;
    date->day = day;
    date->month = month;
    date->year = year;

    return OK;

}