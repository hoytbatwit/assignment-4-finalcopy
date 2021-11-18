#include "files.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct files_t* files_open(char* path, int buffer_size) {
    struct files_t *open_ds;
    int fd = open(path,buffer_size);
    if(fd == -1)
    {
        return NULL;
    }
    open_ds = malloc(sizeof(struct files_t));
    char *buffer[buffer_size];
    open_ds->fd = fd;
    open_ds->ib_size = buffer_size;
    open_ds->ib_position = 0;
    open_ds->position =  0;
    open_ds->ib_left =  0;
    open_ds->internal_buffer = *buffer;
    return open_ds;
}

enum files_status files_read(struct files_t* file, char* buffer, int bufflen) {
    int sig = read(file->fd, buffer, bufflen);
    
    //end of file(still buffer space left)
    if(sig == 0)
    {
        file->ib_left = file->ib_size;
        memcpy(buffer, file, bufflen);
        file->ib_position = file->ib_left - bufflen;
        file->position = bufflen;
        return FILES_EOF;
    }
    //filled buffer
    else if(sig == bufflen)
    {
        file->ib_left = file->ib_size;
        memcpy(buffer, file, bufflen);
        file->ib_position = file->ib_left - bufflen;
        file->position = bufflen;
        return FILES_OK;
    }
    //Improper arguments passed in
    else if(sig < bufflen)
    {
        file->ib_left = file->ib_size;
        memcpy(buffer, file, bufflen);
        file->ib_position = file->ib_left - bufflen;
        file->position = bufflen;
        return FILES_ERR_ARGS;
    }
    //Unspecified error ocured
    return FILES_ERR_OTHER;

}

void files_close(struct files_t* file) {
    //without checking to ensure its not null we will get error
    //cause trying to close a null file so nothing to close
    if(file != NULL)
    {
        close(file->fd);
    }
    free(file);
}
