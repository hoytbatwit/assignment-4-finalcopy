#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "files.h"

int main(int argc, char* argv[]) {
    int num_args = argc - 1;
    // TODO: Read command-line arguments as bufsize
    int bufsize = atoi(argv[num_args]);
    // TODO: Open file files_open("pi.txt", bufsize)
    struct files_t* f = files_open("pi.txt", bufsize);
    // TODO: Measure and print resul
    char buffer[11];
    buffer[10]=0;
    struct timeval start;
    gettimeofday(&start, NULL);
    enum files_status status = files_read(f, buffer, 10);
    while(status == FILES_OK)
    {
        status = files_read(f, buffer, 10);
    }

    struct timeval end;
    gettimeofday(&end, NULL);
    int seconds  = start.tv_sec - end.tv_sec;
    int milli = start.tv_usec - end.tv_usec;
    printf("Is %d seconds and %d milliseconds.", seconds, milli);
    return EXIT_SUCCESS;
}