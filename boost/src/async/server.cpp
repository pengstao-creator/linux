#include "common.hpp"
#include <array>

/**
 * 开始从客户端读取数据
 * @param socket 客户端socket连接的智能指针
 * 
 * 该函数使用Boost.Asio的异步读取操作从客户端读取数据，
 * 当读取到数据后，将数据回显给客户端，然后继续等待下一次数据
 */
void start_read(std::shared_ptr<tcp::socket> socket)
{
    // 创建一个共享的缓冲区，用于存储从客户端读取的数据
    // 使用std::array作为固定大小的缓冲区，大小为128字节
    auto buff = std::make_shared<std::array<char, 128>>();
    
    // 异步读取客户端数据
    socket->async_read_some(buffer(*buff),
        [socket, buff](boost::system::error_code ec1, size_t length) {
            // 检查是否有错误发生
            if (!ec1)
            {
                // 打印接收到的消息
                std::cout << "接收到客户端发送的消息:"
                    << std::string(buff->data(), length) << std::endl;

                // 异步写回数据给客户端（回显）
                socket->async_write_some(buffer(*buff),
                    [socket, buff](boost::system::error_code ec2, size_t) {
                        if (!ec2)
                        {
                            std::cout << "给客户端发送消息成功!" << std::endl;
                        }
                    });

                // 递归调用自己，继续等待下一次数据
                start_read(socket);
            }
            else { 
                // 处理错误情况
                if (ec1 == boost::asio::error::eof)
                    std::cout << "客户端断开连接" << std::endl;
                else
                    std::cout << "读取错误: " << ec1.message() << std::endl;
            }
        });
}

/**
 * 主函数 - 启动异步TCP服务器
 * 
 * 该函数创建一个异步TCP服务器，监听指定端口，
 * 当有客户端连接时，创建一个新的socket连接并开始处理数据
 */
int main()
{
    try
    {
        // 创建IO上下文，用于处理异步操作
        io_context io;
        
        // 创建TCP接受器，监听IPv4地址和指定端口
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), PORT));
        std::cout << "服务端开始监听，准备接收连接请求" << std::endl;

        // 定义一个函数对象，用于处理新的连接请求
        std::function<void()> do_accept;
        do_accept = [&]() {
            // 创建一个新的socket对象，用于与客户端通信
            auto socket = std::make_shared<tcp::socket>(io);
            
            // 异步接受客户端连接
            acceptor.async_accept(*socket, [&, socket](const boost::system::error_code& ec) {
                // 检查是否有错误发生
                if (ec) {
                    std::cerr << "接受连接失败：" << ec.message() << std::endl;
                    return;
                }
                
                // 打印客户端连接信息
                std::cout << "客户端连接成功：" << socket->remote_endpoint() << std::endl;
                
                // 递归调用do_accept，继续接受下一个连接
                do_accept();
                
                // 开始从客户端读取数据
                start_read(socket);
            });
        };
        
        // 首次调用do_accept，开始接受连接
        do_accept();

        std::cout << "等待客户端连接..." << std::endl;
        
        // 运行IO上下文，处理所有异步操作
        io.run();
    }
    catch (std::exception& e)
    {
        // 处理异常
        std::cout << e.what() << std::endl;
    }
    return 1;
}
