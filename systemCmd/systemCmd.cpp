/*
  This file is compare the performance of system command and system api.
  Please use "top" along with this program
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

const int DURATION = 10; // lasting duration
const int FREQUENCY = 50; // times per second
const int THREADS = 10;
const int STRING_LEN = 255;

// Get time difference in macro seconds
int getDifference(timespec& start, timespec& end)
{
    int diff = (end.tv_sec - start.tv_sec) * 1000000000 
               + (end.tv_nsec - start.tv_nsec);
    
    return diff / 1000;
}

// Use api "mkdir" to create directories and then delete them
void* create_file_api(void* input)
{
    char cmd[STRING_LEN] = {};
    int threadOrder = reinterpret_cast<long>(input);
    timespec tp_start = {};
    timespec tp_end = {};
    
    long long totalTime = 0;
    unsigned int averageTime = 0;
    
    for (int i = threadOrder * DURATION * FREQUENCY; 
         i < (threadOrder + 1) * DURATION * FREQUENCY; 
         i++)
    {
        clock_gettime(CLOCK_REALTIME, &tp_start);
        {
            memset(cmd, 0, sizeof(cmd));
            
            snprintf(cmd, STRING_LEN, "/tmp/file%d", i);
            mkdir(cmd, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // 775
            
            rmdir(cmd);
        }
        clock_gettime(CLOCK_REALTIME, &tp_end);
        
        int difference = getDifference(tp_start, tp_end);
        totalTime += difference;
        
        if (1000000/FREQUENCY < difference)
        {
            printf("API takes too much time: %d us, and can't meet frequence demand\n", difference);
            break;
        }
        usleep(1000000/FREQUENCY - difference);
    }
    
    averageTime = totalTime /(DURATION * FREQUENCY);
    
    printf("Average time:%d us\n", averageTime);
}



// Use system command "mkdir" to create directories and then delete them
void* create_file_command(void* input)
{
    char cmd[STRING_LEN] = {};
    int threadOrder = reinterpret_cast<long>(input);
    timespec tp_start = {};
    timespec tp_end = {};
    
    long long totalTime = 0;
    unsigned int averageTime = 0;
    
    for (int i = threadOrder * DURATION * FREQUENCY; 
         i < (threadOrder + 1) * DURATION * FREQUENCY; 
         i++)
    {
        clock_gettime(CLOCK_REALTIME, &tp_start);
        {
            memset(cmd, 0, sizeof(cmd));
            
            snprintf(cmd, STRING_LEN, "mkdir -p /tmp/file%d", i);
            system(cmd);
            
            snprintf(cmd, STRING_LEN, "rmdir /tmp/file%d", i);
            system(cmd);
        }
        clock_gettime(CLOCK_REALTIME, &tp_end);
        
        int difference = getDifference(tp_start, tp_end);
        totalTime += difference;
        
        if (1000000/FREQUENCY < difference)
        {
            printf("API takes too much time: %d us, and can't meet frequence demand\n", difference);
            break;
        }
        usleep(1000000/FREQUENCY - difference);
    }
    
    averageTime = totalTime /(DURATION * FREQUENCY);
    
    printf("Average time:%d us\n", averageTime);
}


int main()
{
    pthread_t threads[THREADS] = {};
    
    printf("Configuration: use %d threads\n", THREADS);
    
    // Step 1
    printf("Step1 starts: use api \"mkdir\"\n");
    
    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&threads[i], NULL, create_file_api, reinterpret_cast<void*>(i));
    }
    
    // Wait for last threads to finish
    pthread_join(threads[THREADS-1], NULL);
    
    // Step 2
    printf("Step2 starts: use system command \"mkdir\"\n");
    
    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&threads[i], NULL, create_file_command, reinterpret_cast<void*>(i));
    }
    
    // Wait for last threads to finish
    pthread_join(threads[THREADS-1], NULL);  

    return 0;
}

