#include "files.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct files_t* files_open(char* path, int buffer_size) {
    struct files_t *open_ds;
    int fd = open(path,O_RDONLY);
    if(fd == -1)
    {
        return NULL;
    }
    //setting all the data inside the struct
    char *buffer = malloc(sizeof(char)*buffer_size);
    open_ds = malloc(sizeof(struct files_t));
    open_ds->internal_buffer = buffer;
    open_ds->fd = fd;
    open_ds->ib_size = buffer_size;
    open_ds->ib_position = 0;
    open_ds->position =  0;
    open_ds->ib_left =  0;
    return open_ds;
}

enum files_status files_read(struct files_t* file, char* buffer, int bufflen) {
    //first we get signal so we know how to handel the file
    int sig = read(file->fd, file->internal_buffer, bufflen);
    //setting the buffer to full
    file->ib_left = bufflen;
    //giving the user the info from the internal buffer
    memcpy(buffer, file->internal_buffer, bufflen);
    //updating all the other values insise the struct
    file->position = file->position + sig;
    file->ib_left = file->ib_left - bufflen;
    if(file->ib_size % bufflen != 0)
    {
        file->ib_position = file->ib_size - bufflen;
    }
    else
    {
        file->ib_position = file->ib_size;
    }
    
    
    //end of the file was reached
    if(sig == 0)
    {
        return FILES_EOF;
    }
    //file was read and matched length of the buffer
    else if(sig == bufflen)
    {
        
        return FILES_OK;
    }
    //Still space in buffer but the file has been read completly
    else if(sig < bufflen)
    {
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
        close(file->ib_left);
        close(file->ib_position);
        close(file->ib_size);
        close(file->position);
        free(file->internal_buffer);
        free(file);
        
    }
}