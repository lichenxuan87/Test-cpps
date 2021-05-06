/*
 * time.h
 *
 *  Created on: Jan 1, 2018
 *      Author: knowyou
 */

#ifndef TIME_TIME_H_
#define TIME_TIME_H_

#include "time.h"

time_t getTime();


void printWellFormatedTime(timespec& tp);

void setTime(time_t t);

#endif /* TIME_TIME_H_ */
