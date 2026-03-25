#ifndef WEBSERVER_H_
#define WEBSERVER_H_

// TODO: 添加必要的头文件引用和类声明
#include "common.h"
#include <iostream>
#include <string>
#include <memory>
// 直接包含日志头文件
class WebServer
{
public:
    static WebServer& getInstance();
    void start(uint16_t port,const std::string& root_dir );
    void stop();
private:
    void doAccept();

    WebServer();
    WebServer(const WebServer&) = delete;
    WebServer& operator=(const WebServer&) = delete;

    std::shared_ptr<Asio::io_context> _io_context;
    std::shared_ptr<Ip::tcp::acceptor> _acceptor;
    std::string _root_dir = "./html";
};

#endif // WEBSERVER_H_
