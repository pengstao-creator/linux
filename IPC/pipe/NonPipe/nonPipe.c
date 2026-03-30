#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
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


int main()
{
    int pipefd[2];
    //获取匿名管道文件读写fd
    int  ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if(pid == 0)
    {
        //子进程写
        //关闭读
        close(pipefd[0]);
        int count = 0;
        while(count < 5)
        {
            write_data(pipefd[1],"我是子进程");
            sleep(1);
            count++;
        }
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipefd[1]);
        char buff[128];
        while(1)
        {
            int ret = read_data(pipefd[0],buff,sizeof(buff));
            if(ret == 0)
            {
                // 子进程已关闭管道，退出循环
                break;
            }
            printf("%s\n",buff);
        }
        close(pipefd[0]);
       
    }

    int ret1 = waitpid(pid,NULL,0);
    if(ret1 < 0)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    return 0;
}