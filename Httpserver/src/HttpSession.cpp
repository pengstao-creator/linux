#include "../include/HttpSession.h"
#include "../include/HttpParser.hpp"
#include "../include/HttpResponse.hpp"
#include "../include/Router.h"
#include "../include/HandlerFactory.h"
#include <iostream>
#include <memory>

HttpSession::HttpSession(Ip::tcp::socket socket, const std::string& web_root)
    : _socket(std::move(socket)), _web_root(web_root)
{
}

void HttpSession::start()
{
    doRead();
}

void HttpSession::doRead()
{
    auto self = shared_from_this();
    boost::asio::async_read_until(_socket, _request_buf, "\r\n\r\n",
        [this, self](const Sys::error_code& ec, std::size_t bytes_transferred)
        {
            onRead(ec, bytes_transferred);
        });
}

void HttpSession::onRead(const Sys::error_code& ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        // 解析HTTP请求
        HttpRequest req;
        if (HttpParser::parse(_request_buf, req))
        {
            std::cout << "收到请求: " << req.method << " " << req.path << " " << req.version << std::endl;
            
            try
            {
                // 使用路由判断处理器类型
                HandlerType type = Router::route(req.path);
                
                // 使用工厂创建处理器
                auto handler = HandlerFactory::create(type, _web_root);
                
                std::string response;
                if (handler)
                {
                    response = handler->handle(req);
                }
                else
                {
                    response = HttpResponse::not_found();
                }
                
                doWrite(response);
            }
            catch (const std::exception& e)
            {
                std::cerr << "处理请求异常: " << e.what() << std::endl;
                std::string response = HttpResponse::not_found();
                doWrite(response);
            }
        }
        else
        {
            std::cerr << "解析请求失败" << std::endl;
            std::string response = HttpResponse::bad_request();
            doWrite(response);
        }
    }
    else
    {
        std::cerr << "Read error: " << ec.message() << std::endl;
    }
}

void HttpSession::doWrite(const std::string& response)
{
    auto self = shared_from_this();
    auto response_ptr = std::make_shared<std::string>(response);
    
    boost::asio::async_write(_socket, boost::asio::buffer(*response_ptr),
        [this, self, response_ptr](const Sys::error_code& ec, std::size_t bytes_transferred)
        {
            onWrite(ec, bytes_transferred);
        });
}

void HttpSession::onWrite(const Sys::error_code& ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        // 写入成功，关闭连接
        Sys::error_code close_ec;
        _socket.shutdown(Ip::tcp::socket::shutdown_both, close_ec);
        _socket.close(close_ec);
    }
    else
    {
        std::cerr << "Write error: " << ec.message() << std::endl;
    }
}
