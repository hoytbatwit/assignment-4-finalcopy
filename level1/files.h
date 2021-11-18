#ifndef FILES_H
#define FILES_H

/**
 * Stores all of the constants that we use
 * to return from the read call
 */
enum files_status {
    FILES_EOF = 1,
    FILES_OK = 0,
    FILES_ERR_ARGS = -1,
    FILES_ERR_OTHER = -2,
};

/**
 * A struct that contains the file data
 * returned from the open system call
 */
struct files_t {
    int fd;
};

/**
 * This will take in a file path and return a
 * a file descriptor that is stored in a malloced
 * struct
 *
 * @param path The file path of the file we want to open
 * @returns struct files_t* A struct holding the file descriptor
 */
struct files_t* files_open(char* path);

/**
 * Will read from the passed in file and return that status of the read
 *
 * @param file The file we are reading from
 * @param buffer The buffer we use to store what we read
 * @param bufflen The length of the buffer determines how much we read
 * @returns The status of the read system call
 */
enum files_status files_read(struct files_t* file, char* buffer, int bufflen);

/**
 * Will close the file and free the
 * memory used to store the file
 *
 * @param file The file struct that stores the file data
 */
void files_close(struct files_t* file);

#endif
