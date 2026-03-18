#include "../include/Socket.h"
#include <sys/epoll.h>
#include <math.h>
void Description()
{
    printf("运行服务器: ./EpollService [prot]\n");
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
    int epollFd = epoll_create(1024);
    SimpleErrorHandler(epollFd,"epoll_create");
    
    struct epoll_event event;
    struct epoll_event events[1024];
    
    // 添加监听文件描述符
    event.events = EPOLLIN;
    event.data.fd = listenFd;
    SimpleErrorHandler(epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd, &event),"epoll_ctl");
    
    while(1)
    {
        int nfds = epoll_wait(epollFd, events, 1024, -1);
        SimpleErrorHandler(nfds,"epoll_wait");
        
        // 检查所有文件描述符
        for(int i = 0; i < nfds; i++)
        {
            if(events[i].data.fd == listenFd)
            {
                // 新连接
                struct sockaddr_in clientAddr;
                int clientFd = Accept(listenFd,&clientAddr);
                SetNonBlocking(clientFd);
                
                // 添加到epoll
                event.events = EPOLLIN;
                event.data.fd = clientFd;
                SimpleErrorHandler(epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event),"epoll_ctl");
                
                printf("新客户端连接: %d\n", clientFd);
            }
            else
            {
                // 客户端数据
                char buffer[1024] = {0};
                int recvLen = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                if(recvLen <= 0)
                {
                    // 客户端断开连接
                    printf("客户端 %d 断开连接\n", events[i].data.fd);
                    close(events[i].data.fd);
                    
                    // 从epoll中移除
                    epoll_ctl(epollFd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                }
                else
                {
                    // 处理接收到的数据
                    printf("收到客户端 %d 的数据: %s\n", events[i].data.fd, buffer);
                    // 回显数据
                    send(events[i].data.fd, buffer, recvLen, 0);
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
