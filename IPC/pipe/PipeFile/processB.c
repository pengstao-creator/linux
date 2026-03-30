#include "pipeFile.h"

int main()
{
    int pipe_fd = get_pipe_fd(O_WRONLY);
    write_data(pipe_fd,"我是子进程");
    close(pipe_fd);
    return 0;
}