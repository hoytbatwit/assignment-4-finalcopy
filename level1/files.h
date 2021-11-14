#ifndef FILES_H
#define FILES_H

/**
 * TODO: Javadoc
 */
enum files_status {
    FILES_EOF = 1,
    FILES_OK = 0,
    FILES_ERR_ARGS = -1,
    FILES_ERR_OTHER = -2,
};

/**
 * TODO: Javadoc
 */
struct files_t {
    int fd;
};

/**
 * TODO: Javadoc
 */
struct files_t* files_open(char* path);
/**
 * TODO: Javadoc
 */
enum files_status files_read(struct files_t* file, char* buffer, int bufflen);
/**
 * TODO: Javadoc
 */
void files_close(struct files_t* file);

#endif
