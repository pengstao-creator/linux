#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// 自定义信号处理函数
void signalHandler(int signalId)
{
    if(signalId == SIGINT)
    {
        printf("处理Ctrl+C操作......\n");
        exit(EXIT_SUCCESS);
    }else if(signalId == SIGUSR1)
    {
        printf("接收到自定义信号SIGUSR1.....\n");
    }else{
        printf("接收到其他信号.....\n");
    }
}

int main(int argc, char const *argv[])
{
    printf("main()函数正在运行........\n");

    // 绑定信号与处理函数
    // SIGINT：捕获Ctrl+C信号
    signal(SIGINT, signalHandler);
    // SIGUSR1：自定义信号
    signal(SIGUSR1, signalHandler);

    // 发送自定义信号
    // raise()函数在当前进程中发送信号
    printf("发送SIGUSR1信号...\n");
    raise(SIGUSR1);

    // 进入死循环，以便能够捕获Ctrl+C信号
    // 如果没有死循环，程序会直接结束，无法捕获SIGINT信号
    printf("程序进入循环，按Ctrl+C退出...\n");
    while (1)
    {
        // 空循环，等待信号
    }
    
    printf("main()运行完毕\n");
    
    return 0;
}