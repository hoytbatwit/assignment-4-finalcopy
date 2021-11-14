# Level 2

For this level, we will be updating the wrapper functions from level 1, and add buffering capabilities. As you may
recall, buffering can significantly improve the performance by reducing the number of system calls. This can lead to
reduced:

1. Reduced number of context switches (from user to kernel and back)
2. Reduced number of hardware interactions.

The functions act in the same manner as those from level 1, but with one major difference. The struct contains an
internal buffer that the functions. For example, 

    struct files_t* f = files_open("numbers.txt", 1024);

will create a buffer of size 1024 bytes. Later, when the read functions are called, the functions first issue a
system call and read 1024 bytes, and copy from this buffer:

    char buffer[64];
    files_read(f, buffer, 128); // 896 bytes left
    files_read(f, buffer, 128); // 768 bytes left
    files_read(f, buffer, 128); // 640 bytes left
    ...
    files_read(f, buffer, 128); // 128 bytes left
    files_read(f, buffer, 128); // 0 bytes left
    files_read(f, buffer, 128); // Reload. Again 896 bytes left

## Opening/Closing

In this part, you will complete the following function:

    struct files_t* files_open(char* path);
    void files_open(struct files_t *file);

These functions are roughly similar to those in level 1. However, the struct you need to initialize has several
additional member variables.

1. `internal_buffer`: The internal buffer memory
2. `ib_size`: Size of the internal buffer
3. `ib_position`: How far did you read so far in the internal buffer memory
4. `position`: How far did you read so far of the file
5. `ib_left`: How many valid bytes are currently left

## Reading

In this part, you will complete the following function:

    enum files_status files_read(struct files_t* file, char* buffer, int bufflen);

Because of the internal buffer, you need manage a lot of internal state (which is the struct you initialized `open`
function).

For example, if `open` was called with 64 bytes for the internal buffer, you should have the following values
initially:

1. `internal_buffer`: The internal buffer memory
2. `ib_size`: 64
3. `ib_position`: 0
4. `position`: 0
5. `ib_left`: 0

The latter three variables are all 0 because you didn't read from the file yet. Once you call read, you should first
fill the internal buffer:

1. `internal_buffer`: The internal buffer memory
2. `ib_size`: 64
3. `ib_position`: 0
4. `position`: 0
5. `ib_left`: 64

Then use `memcpy` to copy the data to the user buffer (16 bytes):

1. `internal_buffer`: The internal buffer memory
2. `ib_size`: 64
3. `ib_position`: 16
4. `position`: 16
5. `ib_left`: 48

## Hints

This problem has a lot of corner cases. For example, what if you have 128 bytes left, but read 256 bytes? You need to:

1. Copy 128 bytes
2. Refill the buffer
3. Copy remaining 128 bytes

Try to solve the easier problem first. For example,

1. First make it work when the internal is a multiple of the external buffer (i.e. `files_open(1024);
   files_read(128)`
2. Then make it work when the internal is not a multiple (so small leftover bytes)
3. Then make it work when the internal buffer is actually smaller than the external buffer

Best of luck!
