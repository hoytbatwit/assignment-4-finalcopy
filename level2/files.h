#ifndef FILES_H
#define FILES_H

/**
 * Holds all the return values for the read method
 * telling the user how the buffer and file interacted
 * and how much was or was not read
 */
enum files_status {
    FILES_EOF = 1,
    FILES_OK = 0,
    FILES_ERR_ARGS = -1,
    FILES_ERR_OTHER = -2,
};

/**
 * A struct that holds all of the data needed for the file
 * the file descriptor, internal bufer size, position in file,
 * internal buffer position, how much is left in the internal buffer,
 * and the interanl buffer itself
 */
struct files_t {
    int fd;
    int ib_size;
    int position;
    int ib_position;
    int ib_left;
    char* internal_buffer;
};

/**
 * This will open the file and set the size of the internal buffer
 *
 * @param path The file path that program will read from
 * @param buffer_size The size of the internal buffer
 *
 * @returns A struct file with all the internal data that can be filled
 */
struct files_t* files_open(char* path, int buffer_size);
/**
 * This method will read from the file and put it into the buffer and return 
 * a status based on how much was read and if it filled the buffer or not
 *
 * @param file The file struct with the size of the internal buffer
 * @param buffer The buffer that will be used
 * @param bufflen How many bytes we want to read
 *
 * @reutrns A value stored in the enum that tells us what happened
 */
enum files_status files_read(struct files_t* file, char* buffer, int bufflen);
/**
 * This will close the file and free all the malloced memory
 *
 * @param file The file struct that needs to be cleared and freed
 */
void files_close(struct files_t* file);

#endif
