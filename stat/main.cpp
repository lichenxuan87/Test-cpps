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
#include <string>

using std::string;

int main(int argc, const char** argv)
{

    if (argc < 2)
    {
        printf("Error, Usage: statfile <filename>\n");
        return -1;
    }

    string filename = argv[1];
    filename += " ";

    struct stat buf;
    if(stat(filename.c_str(), &buf)!=0)
    {
         printf("Failed: error is %d for %s\n",errno, filename.c_str());
    }
    else
    {
        printf("Success\n");
    }


    return 0;

}

