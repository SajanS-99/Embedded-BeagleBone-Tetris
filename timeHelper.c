#include "timeHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// get time
long long getTimeInMs(void){
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoseconds = spec.tv_nsec;
    long long milliseconds = seconds * 1000 + nanoseconds / 1000000;
    return milliseconds;
} 
// get time, scaled to ns
long long getTimeInNs(void){
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoseconds = spec.tv_nsec;
    nanoseconds = seconds * 1000000000 + nanoseconds;
    return nanoseconds;
} 
// sleep
void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}
// converts nano seconds to ms by divinding by 10^6
// and typecast to double for output later
double nanoToMs(long long nanoTime){
    return ((double)nanoTime/1000000);
}