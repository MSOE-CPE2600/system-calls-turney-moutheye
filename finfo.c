/*
* filename: finfo.c
* author: Elias Mouthey
* date: 10/30/25
* lab 9
* section: 121 
* description:
* Note: 
*/
/**************************************************************
Info about file management system calls
fstat() - information about a file - populates a struct stat with 
various details about the file

**************************************************************/

#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>

//helper method to print the file in a good readable format


int main(int argc, char* argv[])
{

    struct stat sb;

    //if arguments is not two program should fail
           if (argc != 2) {
               fprintf(stderr, "Usage: %s <path>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

           printf("ID of containing device:  [%x,%x]\n",
                  major(sb.st_dev),
                  minor(sb.st_dev));

           printf("File type:                ");

           //prints the file type as a readable format
           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);

           printf("Mode:                     %jo (octal)\n",
                  (uintmax_t) sb.st_mode);

           printf("Link count:               %ju\n", (uintmax_t) sb.st_nlink);

           //allows for the username to be displayed for ownership
           //uses pwd for user info
           struct passwd *pw = getpwuid(sb.st_uid);
           if (pw != NULL) 
           {
                printf("Owner:                    %s (UID: %d)\n", pw->pw_name, sb.st_uid);
            } 
            else 
            {
                printf("Owner UID:           %d\n", sb.st_uid);
            }

           printf("Preferred I/O block size: %jd bytes\n",
                  (intmax_t) sb.st_blksize);
           printf("File size:                %jd bytes\n",
                  (intmax_t) sb.st_size);
           printf("Blocks allocated:         %jd\n",
                  (intmax_t) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));

           exit(EXIT_SUCCESS);
}