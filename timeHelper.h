/*

Header file for some functions relating to time. 

Helps converts the raw nanosecond samples into ms for the output terminal and led
As well as functions for getting current time, and sleeping



*/
#ifndef TIMEHELPER_H
#define TIMEHELPER_H


long long getTimeInMs(void);

long long getTimeInNs(void);

void sleepForMs(long long delayInMs);

double nanoToMs(long long nanoTime);


#endif