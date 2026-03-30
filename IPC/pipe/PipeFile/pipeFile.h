#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define PIPE_SIZE 128
#define PATH_NAME "./pipe.fifo"


int get_pipe_fd(int flags)
{
    int mkfifo_ret = mkfifo(PATH_NAME,0666);
    if(mkfifo_ret < 0 && errno != EEXIST)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    int pipe_ret = open(PATH_NAME,flags);
    if(pipe_ret < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    return pipe_ret;
}

void write_data(int fd,const char * s)
{
    int ret = write(fd,s,strlen(s));
    if(ret == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
}


int read_data(int fd,char * str,size_t size)
{
    int ret = read(fd,str,size -1);
    if(ret < 0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    if(ret > 0)
    {
        str[ret] = '\0';
    }
    return ret;
}
