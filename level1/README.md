# Level 1

For the this level, we will be writing wrapper functions for file I/O, and practicing the following system calls:

- open
- close
- read

You may also use the following C library functions:

- malloc
- free
- memcpy

Using these, complete the following functions.

## Opening/Closing

In this part, you will complete the following function:

    struct files_t* files_open(char* path);
    void files_open(struct files_t *file);

The first function opens a file with the given path and the mode `O_RDONLY`. The file descriptor returned form the `open`
system call should be stored in a new `struct files_t`, which is allocated on the heap. If the file descriptor is
invalid (for example, file doesn't exist), return `NULL` instead (for details, read the manpages for `open`).

The second function takes the created struct and frees it.

## Reading

In this part, you will complete the following function:

    enum files_status files_read(struct files_t* file, char* buffer, int bufflen);

When this function is called, you should use the `read` system call to fill the buffer.

When done, you should return one of the following:

- return `FILES_OK` if there were no problems
- return `FILES_EOF` if there were no problems, but you reach the end of file (`read` returned 0)
- return `FILES_ERR_ARGS` if there were problems with the function arguments
- return `FILES_ERR_OTHER` if there were other problems (`read` encountered an unspecified problem)

Check the return values of the `read` system call for more details on what errors can occur.
