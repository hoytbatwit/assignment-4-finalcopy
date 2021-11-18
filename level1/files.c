#include "files.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct files_t* files_open(char* path) {
    //create struct
    struct files_t *open_des;
    int fd = open(path, O_RDONLY);
    //if error in open we return null
    if(fd == -1)
    {
        return NULL;
    }
    open_des = malloc(sizeof(struct files_t));
    open_des->fd = fd;
    return open_des;
}

enum files_status files_read(struct files_t* file, char* buffer, int bufflen) {
    //store signal from read to determine what we return
    int sig = read(file->fd, buffer, bufflen);
    //no problem just reached end of file
    if(sig == 0)
    {
        return FILES_EOF;
    }
    //no problem at all
    else if(sig == bufflen)
    {
        return FILES_OK;
    }
    //Improper arguments passed in
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
    }
    free(file);
}

