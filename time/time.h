/*
 * time.h
 *
 *  Created on: Jan 1, 2018
 *      Author: knowyou
 */

#ifndef TIME_TIME_H_
#define TIME_TIME_H_


#include <time.h>
#include <string.h>
#include <stdio.h>

timespec getTime()
{
    timespec wallTp = {0};

    // Get Current wall clock time
    clock_gettime(CLOCK_REALTIME_COARSE, &wallTp); // CLOCK_REALTIME_COARSE: faster but less precise

    return wallTp;
}


void printWellFormatedTime(timespec& tp)
{
    // Print wall clock time
    tm* clockTime = gmtime(&tp.tv_sec); //Convert time to a structure

    printf("Current wall time: %.2d:%.2d:%.2d.%.6ld\n", clockTime->tm_hour, clockTime->tm_min, clockTime->tm_sec, tp.tv_nsec/1000);
}

void printCurrentTime()
{
    timespec time = getTime();
    printWellFormatedTime(time);
}

#endif /* TIME_TIME_H_ */
