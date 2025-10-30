/*
* filename: pinfo.c
* author: Elias Mouthey
* date: 10/29/25
* description:
* Note: 
*/
/**************************************************************
Info about process control system calls:

getpid - gets process id
getpriority - gets the nice value of a process
sched_getscheduler - get scheduling policy
getcpu - retrieves the cpu core that the process is currently running on
getrusage - gets resource usage (CPU time, memory usage, etc.)for the process
getrlimit - gets resource limit (file size or memory size)

**************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{

    pid_t pid;
    int scheduler;
    int priority;

    //Determine target PID
    if (argc == 1) {
        //current process
        pid = getpid(); 
    } else if (argc == 2) {
        pid = (pid_t)atoi(argv[1]);
        if (pid <= 0) {
            fprintf(stderr, "Error: Invalid PID '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Get scheduling policy
    scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        perror("sched_getscheduler");
        fprintf(stderr, "Error: Could not get scheduler for PID %d\n", pid);
        return EXIT_FAILURE;
    }

    //Get process nice value
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("getpriority");
        fprintf(stderr, "Error: Could not get priority for PID %d\n", pid);
        return EXIT_FAILURE;
    }

    //Display the results
    printf("Process ID: %d\n", pid);
    printf("Process Priority (nice value): %d\n", priority);

    printf("Scheduling Policy: ");
    switch (scheduler) {
        case SCHED_OTHER: printf("SCHED_OTHER (Normal)\n"); break;
        case SCHED_BATCH: printf("SCHED_BATCH\n"); break;
        case SCHED_IDLE:  printf("SCHED_IDLE\n"); break;
        case SCHED_FIFO:  printf("SCHED_FIFO (Real-time)\n"); break;
        case SCHED_RR:    printf("SCHED_RR (Round-robin)\n"); break;
#ifdef SCHED_DEADLINE
        case SCHED_DEADLINE: printf("SCHED_DEADLINE (Real-time deadline)\n"); break;
#endif
        default:           printf("Unknown (%d)\n", scheduler);
    }

    return EXIT_SUCCESS;
}
