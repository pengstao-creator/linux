#include "../include/Socket.h"
#include <sys/poll.h>
#include <math.h>
void Description()
{
    printf("运行服务器: ./PollService [prot]\n");
}

void PrepareConnection(struct sockaddr_in * serviceAddr,int * serviceFd,
    int * listenFd,uint16_t prot,const char * ip,int domain,int type)
{
    HostToNetwork(serviceAddr,ip,prot,domain,type);
    *serviceFd = socket(domain,type,0);
    SimpleErrorHandler(*serviceFd,"socket");
    SetNonBlocking(*serviceFd);
    Bind(*serviceFd,serviceAddr);
    *listenFd = listen(*serviceFd,10);
    SimpleErrorHandler(*listenFd,"listen");
}

void ConnectionManager(int listenFd)
{
    struct pollfd fds[1024];
    int nfds = 1;
    
    // 初始化pollfd结构
    fds[0].fd = listenFd;
    fds[0].events = POLLIN;
    
    while(1)
    {
        int ret = poll(fds, nfds, -1);
        SimpleErrorHandler(ret,"poll");
        
        // 检查所有文件描述符
        for(int i = 0; i < nfds; i++)
        {
            if(fds[i].revents & POLLIN)
            {
                if(fds[i].fd == listenFd)
                {
                    // 新连接
                    struct sockaddr_in clientAddr;
                    int clientFd = Accept(listenFd,&clientAddr);
                    SetNonBlocking(clientFd);
                    
                    // 添加到pollfd数组
                    fds[nfds].fd = clientFd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                    
                    printf("新客户端连接: %d\n", clientFd);
                }
                else
                {
                    // 客户端数据
                    char buffer[1024] = {0};
                    int recvLen = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if(recvLen <= 0)
                    {
                        // 客户端断开连接
                        printf("客户端 %d 断开连接\n", fds[i].fd);
                        close(fds[i].fd);
                        
                        // 从pollfd数组中移除
                        for(int j = i; j < nfds - 1; j++)
                        {
                            fds[j] = fds[j + 1];
                        }
                        nfds--;
                        i--; // 调整索引
                    }
                    else
                    {
                        // 处理接收到的数据
                        printf("收到客户端 %d 的数据: %s\n", fds[i].fd, buffer);
                        // 回显数据
                        send(fds[i].fd, buffer, recvLen, 0);
                    }
                }
            }
        }
    }
}

int main(int num,char** argv)
{
    uint16_t prot;
    if(num != 2 || str_to_uint16(argv[1],&prot) == -1)
    {
        Description();
        exit(0);
    }

    //创建服务端
    struct sockaddr_in serviceAddr;
    int serviceFd,listenFd;

    //链接准备
    PrepareConnection(&serviceAddr,&serviceFd,
        &listenFd,prot,"0.0.0.0",AF_INET,SOCK_STREAM);

    //开始监听
    printf("服务器正在监听端口: %d\n",prot);
    
    ConnectionManager(listenFd);

}
