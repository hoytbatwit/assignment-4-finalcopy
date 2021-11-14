#include "files.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct files_t* files_open(char* path, int buffer_size) {
    // TODO: Malloc and open
    return NULL;
}

enum files_status files_read(struct files_t* file, char* buffer, int bufflen) {
    // TODO
    return FILES_OK;

}

void files_close(struct files_t* file) {
    // TODO: Close and free
}
