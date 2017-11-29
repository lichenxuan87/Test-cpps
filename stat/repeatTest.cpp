/*
 * main.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: knowyou
 */

#include "stdio.h"
#include "unistd.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, const char** argv)
{

    if (argc < 2)
    {
        printf("Error, Usage: repeatTest <filename>\n");
        return -1;
    }

    const char* filename = argv[1];


    while (true)
    {
        string removeCmd = string("rm ") + filename;
        string createCmd = string("echo 1 > ") + filename;

        system(createCmd.c_str());
        system(removeCmd.c_str());

        struct stat buf;

        if(stat(filename, &buf)!=0)
        {
             printf("Failed: error is %d \n",errno);
        }
        else
        {
            printf("Success\n");
            return 0;
        }
    }

    return 0;

}

