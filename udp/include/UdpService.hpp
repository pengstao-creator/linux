#pragma once
#include "socket.hpp"
#include <memory>
#include <map>
#include <pthread.h>
#include <queue>
#include <myh/pthreadpool.hpp>
class UdpService
{
private:
    typedef std::shared_ptr<UdpSocket> UdpSockPtr;
    typedef std::shared_ptr<std::map<std::string,uint16_t>> UserData; 
private:
    struct ClientMessage
    {
        ClientMessage(uint16_t prot,const std::string& message,const std::string& ip)
            :_prot(prot)
            ,_message(message)
            ,_ip(ip)
        {}
        uint16_t _prot;
        std::string _message;
        std::string _ip;
    };
    
public:
    UdpService(uint16_t prot)
        :_sockptr(std::make_shared<UdpSocket>(prot,"0.0.0.0",AF_INET,SOCK_DGRAM))
        ,_udata(std::make_shared<std::map<std::string,uint16_t>>())
    {
    }
    ~UdpService(){_sockptr->Close();}
    void Start()
    {
        //创建一个消息处理线程进行消息处理
        CreateThread(1);//创建多个线程用队列处理则需要加锁
        pthread_t tid;
        std::string message,ip;
        sockaddr_in clientaddr;
        uint16_t prot;
        
        //只绑定一次端口
        _sockptr->Bind();
        std::cout << "服务器启动成功...\n";
        while (true)
        {
            //阻塞的接受消息
            message.clear();
            _sockptr->Recvfrom(&clientaddr,message);
            //保存用户信息
            ip.clear();
            _sockptr->NetworkToHost(&clientaddr,ip,prot);
            
            _udata->insert({ip,prot});
            //处理消息,创建线程处理/或者线程池
            ClientMessage cm(prot,message,ip);
            //加入任务队列
            _QMessage.push(cm);
        }
        
    }
private:
    static void * MessageHandler(void * arg)
    {
        UdpService * _this = static_cast<UdpService*>(arg);
        while (true)
        {
            if(!_this->_QMessage.empty())
            {
                //将消息打印到屏幕,实现一个简易聊天室
                ClientMessage cm = _this->_QMessage.front();
                _this->_QMessage.pop();
                //将消息同步到其他客户端
                _this->Send(cm);
            }
        }
    }
    void Send(const ClientMessage& cm)
    {
        std::string mag;
        //格式化消息保存
        addmessage(cm,mag);
        printf("%s\n",mag.c_str());
        for(auto ud : *_udata)
        {
            if(ud.first != cm._ip)
            {
                _sockptr->Sendto(mag,cm._ip,cm._prot);
            }
        }
    }
    void addmessage(const ClientMessage& cm,std::string& mag)
    {
        mag += cm._ip;
        mag += ":";
        mag += std::to_string(cm._prot);
        mag += ":";
        mag += cm._message;
        _Allmessage.push_back(mag);
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
    UserData _udata;
    std::queue<ClientMessage> _QMessage;
    std::vector<std::string> _Allmessage;//聊天记录
};
