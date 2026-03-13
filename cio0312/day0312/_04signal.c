#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//自定义一个信号处理函数
void handleSignal(int sigId)
{
    if(sigId == SIGINT)
    {
        printf("处理ctrl+co操作......\n");
        exit(EXIT_SUCCESS);
    }else if(sigId == SIGUSR1)
    {
        printf("自定义信号.....\n");
    }else{
        printf("其他信号.....\n");
    }
}

int main(int argc, char const *argv[])
{
    printf("main()正在运行........\n");

    // 将信号和信号处理函数做绑定
    // SIGINT捕获ctrl+c
    signal(SIGINT,handleSignal);
    signal(SIGUSR1,handleSignal);

    // 自定义信号，需要由我们手动发送信号
    // 发信号:有两种方式，kill(进程id,信号):可以跨进程发信号   raise():默认在本进程中发信号
    raise(SIGUSR1);

    // 绑定ng完成， 信号处理函数不会被自动触发
    // SIGINT 是由ctrl+c触发,所以e这个地方手动触发
    while (1)
    {
        // 如果这个地方没有死循环，那么main就会直接结束，所以要想可以触发SIGINT信号，需要让程序不要直接结束
    }
    
    printf("main()运行完毕\n");
    
    return 0;
}
