
#include "../include/Socket.h"
#include <sys/select.h>
#include <math.h>
void Description()
{
    printf("运行服务器: ./SlectService [prot]\n");
}

void PrepareConnection(struct sockaddr_in * serviceAddr,int * serviceFd,\
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
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(listenFd,&readfds);
    int maxFd = listenFd;
    while(1)
    {
        // 每次循环都需要重新设置readfds
        fd_set tempFds = readfds;
        int ret = select(maxFd+1,&tempFds,NULL,NULL,NULL);
        SimpleErrorHandler(ret,"select");
        
        // 检查所有文件描述符
        for(int i = 0; i <= maxFd; i++)
        {
            if(FD_ISSET(i,&tempFds))
            {
                if(i == listenFd)
                {
                    // 新连接
                    struct sockaddr_in clientAddr;
                    int clientFd = Accept(listenFd,&clientAddr);
                    SetNonBlocking(clientFd);
                    FD_SET(clientFd,&readfds);
                    maxFd = (maxFd > clientFd) ? maxFd : clientFd;
                    printf("新客户端连接: %d\n", clientFd);
                }
                else
                {
                    // 客户端数据
                    char buffer[1024] = {0};
                    int recvLen = recv(i, buffer, sizeof(buffer), 0);
                    if(recvLen <= 0)
                    {
                        // 客户端断开连接
                        printf("客户端 %d 断开连接\n", i);
                        close(i);
                        FD_CLR(i,&readfds);
                        // 更新maxFd
                        if(i == maxFd)
                        {
                            while(maxFd > 0 && !FD_ISSET(maxFd,&readfds))
                                maxFd--;
                        }
                    }
                    else
                    {
                        // 处理接收到的数据
                        printf("收到客户端 %d 的数据: %s\n", i, buffer);
                        // 回显数据
                        send(i, buffer, recvLen, 0);
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
    PrepareConnection(&serviceAddr,&serviceFd,\
        &listenFd,prot,"0.0.0.0",AF_INET,SOCK_STREAM);

    //开始监听
    printf("服务器正在监听端口: %d\n",prot);
    
    ConnectionManager(listenFd);


}