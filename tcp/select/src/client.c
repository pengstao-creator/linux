#include "../include/Socket.h"

void Description()
{
    printf("运行客户端: ./client [ip] [port]\n");
}

int main(int num,char** argv)
{
    if(num != 3)
    {
        Description();
        exit(0);
    }

    const char* ip = argv[1];
    uint16_t port;
    if(str_to_uint16(argv[2],&port) == -1)
    {
        Description();
        exit(0);
    }

    // 创建客户端
    int clientFd = socket(AF_INET,SOCK_STREAM,0);
    SimpleErrorHandler(clientFd,"socket");

    // 连接服务器
    struct sockaddr_in serverAddr;
    HostToNetwork(&serverAddr,ip,port,AF_INET,SOCK_STREAM);
    Connect(clientFd,&serverAddr);
    printf("连接服务器成功: %s:%d\n",ip,port);

    // 发送和接收数据
    char buffer[1024] = {0};
    while(1)
    {
        printf("请输入消息: ");
        fgets(buffer,sizeof(buffer),stdin);
        
        // 发送数据
        send(clientFd,buffer,strlen(buffer),0);
        
        // 接收数据
        memset(buffer,0,sizeof(buffer));
        int recvLen = recv(clientFd,buffer,sizeof(buffer),0);
        if(recvLen <= 0)
        {
            printf("服务器断开连接\n");
            break;
        }
        printf("收到服务器的响应: %s\n",buffer);
    }

    // 关闭连接
    close(clientFd);
    return 0;
}