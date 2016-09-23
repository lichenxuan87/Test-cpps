/*
 * time.cpp
 *
 *  Created on: Sep 23, 2016
 *      Author: saic
 *
 *  This cpp will use time functions
 */


#include <time.h>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <cstdlib>
#include <unistd.h>

void printWellFormatedTime(timespec& tp)
{
    // Print wall clock time
    tm* clockTime = gmtime(&tp.tv_sec); //Convert time to a structure

    printf("Current wall time: %.2d:%.2d:%.2d.%.6ld\n", clockTime->tm_hour, clockTime->tm_min, clockTime->tm_sec, tp.tv_nsec/1000);
}

time_t getTime()
{
    timespec wallTp = {0};
    timespec kernelTp = {0};

    // Get Current wall clock time
    clock_gettime(CLOCK_REALTIME_COARSE, &wallTp); // CLOCK_REALTIME_COARSE: faster but less precise

    // Get current kernel time
    clock_gettime(CLOCK_MONOTONIC_RAW, &kernelTp); // Kernel time

    printWellFormatedTime(wallTp);

    // Print kernel time
    printf("Kernel time: %ld.%.6ld\n", kernelTp.tv_sec, kernelTp.tv_nsec/1000);

    return wallTp.tv_sec;
}

void setTime(time_t t)
{
    if (stime(&t) != 0)
    {
        printf("Current kernel time: stime returned error: %s\n", strerror(errno));
    }
}

int main()
{

    time_t wallTime = getTime();


    // Set current wall clock time
    wallTime -= 3600;
    setTime(wallTime);

    //
    usleep(1000);

    getTime();

    return 0;
}

