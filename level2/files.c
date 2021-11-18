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
    open_ds->fd = fd;
    open_ds->ib_size = buffer_size;
    open_ds->ib_position = 0;
    open_ds->position =  0;
    open_ds->ib_left =  0;
    return open_ds;
}

enum files_status files_read(struct files_t* file, char* buffer, int bufflen) {
    //first we get signal so we know how to handel the file
    int sig = read(file->fd, buffer, bufflen);
    //end of the file was reached
    if(sig == 0)
    {
        memcpy(buffer, file, bufflen);
        file->position = bufflen;
        file->ib_left = file->ib_left - bufflen;
        file->ib_position = bufflen;
        //files_read(file, buffer, bufflen);
        return FILES_EOF;
    }
    //file was read and matched length of the buffer
    else if(sig == bufflen)
    {
        file->internal_buffer= buffer;
        file->ib_left = file->ib_size;
        memcpy(buffer, file, bufflen);
        file->position = bufflen;
        file->ib_left = file->ib_left - bufflen;
        file->ib_position = bufflen;
        return FILES_OK;
    }
    //Still space in buffer but the file has been read completly
    else if(sig < bufflen)
    {
        memcpy(buffer, file, bufflen);
        file->position = bufflen;
        file->ib_left = file->ib_left - bufflen;
        file->ib_position = bufflen;
        files_read(file, buffer, bufflen);
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
