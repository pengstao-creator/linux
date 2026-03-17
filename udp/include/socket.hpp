#ifndef HEADER_SOCKET_H
#define HEADER_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <myh/socket.hpp>
#include <memory>
//简单封装udp网络套接字接口

class UdpSocket
{
public:
    UdpSocket(uint16_t prot,const std::string& ip,int domain = AF_INET, int type = SOCK_DGRAM)
        :_prot(prot),_ip(ip)
    {
        //获取套接字fd
        _sockfd = socket(domain,type,0);
        ErrorHandler("socket",_sockfd);
        HostToNetwork(&_addr,_ip,_prot,domain,type);
    }

    void Bind()
    {
        int ret = bind(_sockfd,(const sockaddr*)(&_addr),(sizeof(_addr)));
        ErrorHandler("bind",ret);
    }
    
    void Sendto(const std::string& returns,const std::string& ip,uint16_t prot)
    {
        sockaddr_in addr;
        HostToNetwork(&addr,ip,prot);
        int ret = sendto(_sockfd,returns.c_str(),returns.size(),0,(const sockaddr*)&addr,sizeof(addr));
        ErrorHandler("sendto",ret);
    }
    void Sendto(const std::string& mag)
    {
        int ret = sendto(_sockfd,mag.c_str(),mag.size(),0,(const sockaddr*)(&_addr),sizeof(_addr));
        ErrorHandler("sendto",ret);
    }
    void Recvfrom(sockaddr_in * addr,std::string& message)
    {
        char buffur[128];
        socklen_t len = sizeof(*addr);
        buffur[0] = '\0';
        int ret = recvfrom(_sockfd,buffur,sizeof(buffur) - 1,0,(sockaddr *)addr,&len);
        ErrorHandler("recvfrom",ret);
        buffur[ret] = '\0';
        message += buffur;
       
    }

    void Close() {close(_sockfd);}

    void NetworkToHost(sockaddr_in * addr,std::string& ip,uint16_t& prot)
    {
        ip = inet_ntoa(addr->sin_addr);
        prot = ntohs(addr->sin_port);
    }
private:
    void HostToNetwork(sockaddr_in * addr,const std::string& ip,uint16_t prot,int domain = AF_INET, int type = SOCK_DGRAM)
    {
        //构造_addr
        addr->sin_family = domain;//ipv4
        addr->sin_port = htons(prot);
        inet_pton(domain,ip.c_str(),&(addr->sin_addr));
    }

    void ErrorHandler(const std::string& name,int Errno)
    {
        if(Errno < 0)
        {
            fprintf(stderr, "%s : %s (errno=%d)\n", 
                name.c_str(),strerror(errno), errno);
            exit(errno);
        }
        
    }
private:
    uint16_t _prot;
    std::string _ip;
    int _sockfd;
    sockaddr_in _addr;
    
};



#endif /* HEADER_NAME_H */
