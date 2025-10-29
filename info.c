/*
* filename: info.c
* author: Elias Mouthey
* date: 10/29/25
* description:
* Note: 
*/
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/utsname.h>
#include <errno.h>
#include <sys/sysinfo.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //struct for the system info - name, version, release ect..
    struct utsname system_info;
    //struct for mem info physical memory in bytes and total free memory
    struct sysinfo mem_info;
    //timespec struct used for the calculation in current time
    struct timespec ts;

     //sys info
    if (uname(&system_info) == -1) {
        perror("uname");
        return 1;
    }

    //mem info
    if (sysinfo(&mem_info) == -1) {
        perror("sysinfo");
        return 1;
    }

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
    perror("clock_gettime");
    return 1;
}

    //total time represented in nanoseconds is the total time in seconds plus
    //the total time in nanoseconds
    long long total_nanoseconds = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec; 

    //print section 
    printf("------info------\n");
    printf("Current Time of Day (ns): %lld\n", total_nanoseconds);
    printf("Network name: %s\n", system_info.nodename);
    printf("Operating System: %s\n", system_info.sysname);
    printf("OS Release: %s\n", system_info.release);
    printf("OS Version: %s\n", system_info.version);
    printf("Hardware Identifier: %s\n", system_info.machine);
    printf("Number of CPUs: %d\n", get_nprocs_conf());
    printf("Total Physical Memory (bytes): %lu\n", mem_info.totalram);
    printf("Total Free Memory (bytes): %lu\n", mem_info.freeram);


    return 0;
    
}