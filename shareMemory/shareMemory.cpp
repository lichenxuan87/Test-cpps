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
#include <semaphore.h>

using namespace std;

const string SHARE_MEMORY_NAME = "TMP_100KB_SHARE_MEMORY";
const int SHARE_MEMORY_SIZE = 100 * 1024; //BYTES


sem_t *semr;
sem_t *semt;


void usage()
{
    cout << "Usage: shareMemory <number>" << endl;
    cout << "By default this act as a client" << endl;
    cout << " 1   act as client / user" << endl;
    cout << " 2   act as server / creator" << endl;
}


// Creator and receiver
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
				string recvMessage = "";
				int recvLength;

				// Initialize Semaphores
				sem_unlink("sem_r");
				semr = sem_open("sem_r", O_CREAT | O_RDWR, 0666, 0);
				if (semr == SEM_FAILED )
				{
					printf("errno = %d\n", errno );
					return;
				}

				sem_unlink("sem_w");
				semt = sem_open("sem_w", O_CREAT | O_RDWR, 0666, 1 );
				if (semt == SEM_FAILED)
				{
					printf("errno = %d\n", errno );
					return;
				}

				while (true)
				{
					sem_wait(semr);
					cout <<"semr Ready" << endl;
					recvMessage = "";

					// Get length
					int index = 0;
					while (true)
					{
						if (reinterpret_cast<char*>(shm_ptr)[index] != ';')
							recvMessage += reinterpret_cast<char*>(shm_ptr)[index];
						else
							break;
						index++;
					}

					recvLength = stoi(recvMessage);

					// Get content
					recvMessage = "";
					for (int i = 0; i < recvLength; i++)
						recvMessage += reinterpret_cast<char*>(shm_ptr)[index+i+1];


					cout << "Received: " << recvMessage << endl;

					sem_post(semt);
				}

            }
        }
    }

    // Release memory mapped to this process
	munmap(shm_ptr, SHARE_MEMORY_SIZE);

}


// User and sender
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
            string inputMessage;

            // Initialize Semaphores
			semr = sem_open("sem_r", O_CREAT | O_RDWR, 0666, 0);
			if (semr == SEM_FAILED )
			{
				printf("errno = %d\n", errno );
				return;
			}

			semt = sem_open("sem_w", O_CREAT | O_RDWR, 0666, 1 );
			if (semt == SEM_FAILED)
			{
				printf("errno = %d\n", errno );
				return;
			}

            while (true)
            {
                sem_wait(semt);
                cout <<"semt Ready" << endl;

                // Get user input and add length before it
                // e.g. input: Hello World; Send: 12;Hello World
            	cout << "Input your mesage:";
            	cin >> inputMessage;

            	inputMessage = to_string(inputMessage.length()) + string(";") + inputMessage;

            	strncpy(reinterpret_cast<char*>(shm_ptr), inputMessage.c_str(), inputMessage.length()+1);

            	sem_post(semr);
            }


        }

    }

    // Release memory mapped to this process
    munmap(shm_ptr, SHARE_MEMORY_SIZE);

    // Unlink share memory file
    shm_unlink(SHARE_MEMORY_NAME.c_str());
}


int main(int argc, char* argv[])
{
	semr = NULL;
	semt = NULL;


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
