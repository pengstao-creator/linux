#include "../include/Socket.h"

void HostToNetwork(struct sockaddr_in * addr,const char * ip,uint16_t prot,int domain, int type)
{
    //构造_addr
    addr->sin_family = domain;//ipv4
    addr->sin_port = htons(prot);
    inet_pton(domain,ip,&(addr->sin_addr));
}

void NetworkToHost(struct sockaddr_in * addr,char ** ip,uint16_t* prot)
{
    *ip = inet_ntoa(addr->sin_addr);
    *prot = ntohs(addr->sin_port);
}

int SetNonBlocking(int fd)
 {
    int flags = fcntl(fd,F_GETFL,0);
    if(flags == -1)
    {
        perror("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    if(fcntl(fd,F_SETFL,flags) == -1)
    {
        perror("fcntl");
        return -1;
    }
    return 0;
 }

 void SimpleErrorHandler(int ReturnValue,const char * name)
 {
    if(ReturnValue < 0)
    {
        printf("[%s 错误原因:%s][错误码:%d]\n",name,strerror(errno),errno);
        exit(errno);
    }
 }

 int str_to_uint16(const char *str, uint16_t *value) {
    if (str == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    char *endptr;
    errno = 0;  // 必须清零 errno 以检测 strtoul 是否溢出

    unsigned long result = strtoul(str, &endptr, 0);  // base=0 自动识别 0x 前缀

    // 检查转换错误
    if (errno == ERANGE && result == ULONG_MAX) {
        // 溢出（超过 unsigned long 范围）
        return -1;
    }
    if (errno != 0 && result == 0) {
        // 其他错误（例如字符串为空）
        return -1;
    }
    if (endptr == str) {
        // 没有字符被转换
        errno = ECANCELED;  // 可以自定义错误码
        return -1;
    }
    if (*endptr != '\0') {
        // 字符串末尾还有非法字符（例如 "123abc"）
        errno = EINVAL;
        return -1;
    }

    // 检查是否超出 uint16_t 范围
    if (result > UINT16_MAX) {
        errno = ERANGE;
        return -1;
    }

    *value = (uint16_t)result;
    return 0;
}

void Bind(int fd,struct sockaddr_in * addr)
{
    SimpleErrorHandler(bind(fd,(struct sockaddr *)addr,sizeof(struct sockaddr_in)),"bind");
}
int Accept(int fd,struct sockaddr_in * addr)
{
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int clientFd = accept(fd,(struct sockaddr *)addr,&addrlen);
    SimpleErrorHandler(clientFd,"accept");
    return clientFd;
}
void Connect(int fd,struct sockaddr_in * addr)
{
    SimpleErrorHandler(connect(fd,(struct sockaddr *)addr,sizeof(struct sockaddr_in)),"connect");
}
