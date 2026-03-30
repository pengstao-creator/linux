#include "pipeFile.h"


int main()
{
    int pipe_fd = get_pipe_fd(O_RDONLY);
    char str[PIPE_SIZE];
    read_data(pipe_fd,str,PIPE_SIZE);
    printf("read data from pipe:%s\n",str);
    close(pipe_fd);
    return 0;
}
