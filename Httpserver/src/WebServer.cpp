#include "../include/WebServer.h"
#include <iostream>
#include "../include/HttpSession.h"
#include <memory>

WebServer::WebServer() 
: _io_context(new Asio::io_context())
    , _acceptor(new Ip::tcp::acceptor(*_io_context))
{
}

WebServer& WebServer::getInstance()
{
    static WebServer instance;
    return instance;
}

void WebServer::start(uint16_t port,const std::string& root_dir)
{
    if(!root_dir.empty())
    {
        _root_dir = root_dir;
    }
    _acceptor->open(Ip::tcp::v4());
    _acceptor->set_option(Ip::tcp::no_delay());
    _acceptor->bind(Ip::tcp::endpoint(Ip::tcp::v4(), port));
    _acceptor->listen();
    std::cout << "服务端开启监听!准备接收客户端连接!" << std::endl;
    doAccept();
    _io_context->run();
}

void WebServer::doAccept()
{
    auto socket = std::make_shared<Ip::tcp::socket>(*_io_context);
    _acceptor->async_accept(*socket,
    [this, socket](const Sys::error_code& ec)
    {
        if (!ec)
        {
            // 处理连接 - 创建HttpSession
            std::cout << "客户端连接成功!" << std::endl;
            auto session = std::make_shared<HttpSession>(std::move(*socket), _root_dir);
            session->start();
        }
        else
        {
            // 处理错误
            std::cerr << "Accept a connection error: " << ec.message() << std::endl;
        }
        doAccept();
    });
}

void WebServer::stop()
{
    _io_context->stop();
}
