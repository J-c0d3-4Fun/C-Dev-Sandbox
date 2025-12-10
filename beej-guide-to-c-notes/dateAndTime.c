
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// UTC = GMT 

// Date Types


// time_t type

// a real type capable of holding time
// this could be a floating type or integer type
// holds calendar time


// struct tm 
// holds the components of a calendar time
// broken-down time
// i.e. the components of the time, hour, minute
// ,second, day, month, year, etc.

// Initialization & Conversion Between Types
// ctime() - prints the value in local time


// Converting time_t to struct tm
// two ways to convert
// localtime(): this function converts a 
// time_t to a struct tm in local time
// gmtime():  this function converts a time_t to a struct tm in UTC


// Convert struct tm to time_t
// use mktime() - sets the values of
// tm_wday & tm_yday for you
// can also set tm_isdst to -1 <- will make the determination for you 


// Formatted Date Output
// strftime() - like printf but for dates

// More Resolution. with timespec_get()
// you can get the number of seconds and nanoseconds since Epoch
// timespec_get thats two arguments:
//  one is a pointer to a struct timespec to hold the information
// the other is th base, which the spec lets you set to TIME_UTC
// TIME_UTC <- indicates you're interested in the seconds since Epoch

struct timespec ts;


// Differences Between Times
// use difftime() to compute the difference in seconds between two dates.

int main(void){

    time_t now;

    now = time(NULL);

    time(&now);

    printf("%s", ctime(&now));
    printf("Local: %s", asctime(localtime(&now)));

    timespec_get(&ts, TIME_UTC);
    printf("%ld s, %ld ns\n", ts.tv_sec, ts.tv_nsec);


    

   
}

