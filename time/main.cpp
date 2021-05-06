/*
 * main.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: peter
 */

#include "wellFormatedTime.h"

#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <unistd.h>

int main()
{

	for (int i = 0; i < 10; i++ )
	{
		getTime();
		usleep(1000);

	}

    return 0;
}


