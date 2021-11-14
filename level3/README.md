# Level 3

## Background

This level goes over the basics of performance measurement in C. Unix systems typically provide the `gettimeofday`
system call that provides very accurate measurement of the current time. You can use this to measure right before some
functions are called, and right after. For example

    files_open(...);

    struct timeval start;
    gettimeofday(&start, NULL);

    enum files_status status = files_read(f, buffer, buffer_size);
    while(status == FILES_OK) {
        status = files_read(f, buffer, buffer_size);
    }

    struct timeval end;
    gettimeofday(&end, NULL);

You can then subtract two structs and subtracting member variables.

    struct timeval {
        int     tv_sec;     /* seconds */
        int     tv_usec;    /* microseconds */
    };

For this level, you are to complete `level3.c`, and complete the report.md file. 

## Code for Level 3

The program should take a single command line argument, the size of the internal buffer. You can convert the command
line argument into an int using the `atoi` function.

Then call the `files_open` function with the size of the internal buffer.

Call the`files_read` function in a loop and get the time difference (see the Background section above).

Last, print the time difference in seconds and micro-seconds (1/1000000 seconds) when reading the entirty of a file
"pi.txt," using different buffer sizes. Take a look at the code from PA1, level 2 if you don't remember how to get the
difference between two time structures.

An example run would look like this:

    ./level3 2
    1s 484786us

## Report

Using the `level3` program you just wrote, complete the questions in `report.md`.
