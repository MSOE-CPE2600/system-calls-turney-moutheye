/*
* filename: pmod.c
* author: Elias Mouthey
* date: 10/29/25
* description:
* Note: 
*/
/**************************************************************
Info about altering a process:

nice() - rating given as an integer that indicates its willingness 
to yield CPU time to other processes. higher value is lower priority
default 0 can go from 19 to -20

man nice            vs        man 2 nice
higher priority     vs        lower priority

nanosleep(const struct timespec *req, struct timespec *rem) - suspends 
calling thread time in nanoseconds allowing for precise sleep time compared
to regular sleep function



**************************************************************/

#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <time.h>
int main(int argc, char* argv[])
{
    int current_nice;

    errno = 0;
    current_nice = getpriority(PRIO_PROCESS, 0);

    if (errno != 0) {
        perror("getpriority");
        return 1;
    }

    printf("Current nice value: %d\n", current_nice);

    //reduce the priority by 10 -> increase the nice value
    int new_nice = current_nice - 10;
    printf("Nice value: %d\n", new_nice);

    //Sleep for 1,837,272,638 nanoseconds
    //since tv_nsec has to be less than 1bil nanoseconds need to split
    //1 sec + 837,272,638 nanoseconds
    struct timespec ts = {.tv_sec = 1, .tv_nsec = 837272638};

    nanosleep(&ts, NULL);

    printf("Good Bye!\n");

    return 0;
}