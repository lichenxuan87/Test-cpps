/*
 * shareMemory.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: saic
 *
 *  This Cpp is to use share memory and act as a server/creator or client/user.
 */


#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

using namespace std;

const string SHARE_MEMORY_NAME = "TMP_100KB_SHARE_MEMORY";
const int SHARE_MEMORY_SIZE = 100 * 1024; //BYTES

void usage()
{
    cout << "Usage: shareMemory <number>" << endl;
    cout << "By default this act as a client" << endl;
    cout << " 1   act as client / user" << endl;
    cout << " 2   act as server / creator" << endl;
}


void createShm()
{
    int shm_fd = 0;
    void* shm_ptr = nullptr;
    bool result = false;

    shm_unlink(SHARE_MEMORY_NAME.c_str());
    shm_fd = shm_open(SHARE_MEMORY_NAME.c_str(),
            O_RDWR | O_CREAT | O_EXCL,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (shm_fd <= -1)
    {
        cout << "Error creating share memory file: " << strerror(errno) << endl;
    }
    else
    {
        if (ftruncate(shm_fd, SHARE_MEMORY_SIZE) <= -1)
        {
            cout << "Error truncating share memory: " << strerror(errno) << endl;
        }
        else
        {
            shm_ptr = (void*)mmap(nullptr, SHARE_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

            if (MAP_FAILED == shm_ptr)
            {
                cout << "Error creating memory mapping: " << strerror(errno) << endl;
            }
            else
            {
                cout << "Create memory mapping success" << endl;
                result = true;

                // Do something here
                memcpy(shm_ptr, "Hello world", 12);
            }
        }
    }

    // Release memory mapped to this process
	munmap(shm_ptr, SHARE_MEMORY_SIZE);

}


void useShm()
{
    int shm_fd = 0;
    void* shm_ptr = nullptr;
    bool result = false;

    shm_fd = shm_open(SHARE_MEMORY_NAME.c_str(),
                O_RDWR,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (shm_fd <= -1)
    {
        cout << "Error creating share memory file: " << strerror(errno) << endl;
    }
    else
    {

        shm_ptr = (void*)mmap(nullptr, SHARE_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        if (MAP_FAILED == shm_ptr)
        {
            cout << "Error creating memory mapping: " << strerror(errno) << endl;
        }
        else
        {
            cout << "Create memory mapping success" << endl;
            result = true;

            // Do something here
            char hello[12] = {0};
            memcpy(hello, shm_ptr, 12);

            cout << "String from share memory: " << hello << endl;
        }

    }

    // Release memory mapped to this process
    munmap(shm_ptr, SHARE_MEMORY_SIZE);

    // Unlink share memory file
    shm_unlink(SHARE_MEMORY_NAME.c_str());
}


int main(int argc, char* argv[])
{

	if (argc == 1)
	{
		usage();
	}
	else
	{
		char* inputChoice = argv[1];

		if (inputChoice[0] == '1')
		{
			useShm();
		}
		else if (inputChoice[0] == '2')
		{
			createShm();
		}
		else
		{
			usage();
		}
	}


}
