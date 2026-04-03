#include "WebServer.h"

// 初始化列表
WebServer::WebServer():acceptor(io)
{
}

// 这个函数是专门来异步连接客户端的
void WebServer::doAccept()
{
    auto socket = std::make_shared<tcp::socket>(this->io);
    this->acceptor.async_accept(*socket, [this,socket](const boost::system::error_code& ec) {
           
            if (!ec)
            {
                std::cout << "客户端连接成功!" << std::endl;
                // 连接成功后，接收客户端信息，解析并做处理 @TODO
            }
            // 递归调用doAccept()，因为客户端不止连接一次
            doAccept(); // 相当于this->doAccept()
        });
}

WebServer& WebServer::getInstance()
{
    static WebServer obj;
    return obj;
}

void WebServer::start(int port, std::string webRoot)
{
    this->webRoot = webRoot;
    // acceptor()绑定端口和ipv4 
    this->acceptor.open(tcp::v4());
    // 绑定
    this->acceptor.bind(tcp::endpoint(tcp::v4(), port));
    // 监听
    this->acceptor.listen();
    std::cout << "服务端正在监听客户端连接....." << std::endl;

    // 开始准备接收客户端连接
    this->doAccept();
    
    // 开启事件循环
    this->io.run();
}
