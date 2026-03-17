#pragma once
#include "socket.hpp"

class Client
{
private:
     typedef std::shared_ptr<UdpSocket> UdpSockPtr;
public:
    Client(const std::string& ip,uint16_t prot)
        :_sockptr(std::make_shared<UdpSocket>(prot,ip,AF_INET,SOCK_DGRAM))
    {}

    void Start()
    {   
        //创建一个线程接受信息
        CreateThread(1);
        std::string message;
        while(true)
        {
            message.clear();
            std::cout << "请发送消息:";
            std::cin >> message;
            if(message == "exit")break;
            _sockptr->Sendto(message);
        }
    }
private:
    static void * MessageHandler(void * arg)
    {
        Client * _this = static_cast<Client*>(arg);
        sockaddr_in serviceAddr;
        std::string mag;
        while (true)
        {
            mag.clear();
            _this->_sockptr->Recvfrom(&serviceAddr,mag);
            std::cout << "\n" << mag << std::endl;
        }
        
    }

    void CreateThread(int num)
    {
        for(int i = 0;i < num;i++)
        {
            pthread_t tid;
            pthread_create(&tid,nullptr,MessageHandler,this);
            pthread_detach(tid);
        }
    }
private:
    UdpSockPtr _sockptr;
};