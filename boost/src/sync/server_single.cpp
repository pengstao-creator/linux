#include "common.hpp"

/**
 * 主函数 - 启动同步单线程TCP服务器
 * 
 * 该函数创建一个同步单线程TCP服务器，监听指定端口，
 * 一次只能处理一个客户端连接，
 * 当客户端连接后，处理该客户端的所有请求，
 * 直到客户端断开连接，然后继续等待下一个连接
 */
int main()
{
    try
    {
        // 创建IO上下文，用于处理IO操作
        io_context io;
        
        // 创建TCP接受器，监听IPv4地址和指定端口
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), PORT));
        std::cout << "服务端开始监听，准备接收连接请求" << std::endl;

        // 主循环，不断接受新的客户端连接
        while (1)
        {
            // 创建一个新的socket对象，用于与客户端通信
            tcp::socket socket(io);
            // 同步接受客户端连接
            acceptor.accept(socket);

            // 获取客户端地址信息并打印
            tcp::endpoint remote_ep = socket.remote_endpoint();
            std::string client_ip = remote_ep.address().to_string();
            unsigned short client_port = remote_ep.port();

            std::cout << "客户端连接成功!" << std::endl;
            std::cout << "客户端地址: " << client_ip << ":" << client_port << std::endl;

            // 处理客户端请求的循环
            char buff[BUFFER_SIZE];
            while (1)
            {
                // 同步读取客户端数据
                boost::system::error_code error;
                size_t len = socket.read_some(buffer(buff), error);

                // 处理错误情况
                if (error) {
                    if (error == boost::asio::error::eof) {
                        std::cout << "客户端正常断开连接" << std::endl;
                    }
                    else {
                        std::cout << "客户端读取错误: " << error.message() << std::endl;
                    }
                    break;
                }

                // 打印接收到的消息并回显给客户端
                if (len > 0)
                {
                    std::cout << "接收客户端数据成功，数据为:" << std::string(buff, len) << std::endl;
                    // 同步发送数据回客户端（回显）
                    socket.write_some(buffer(buff, len));
                }
            }
        }
    }
    catch (std::exception& e)
    {
        // 处理异常
        std::cout << e.what() << std::endl;
    }
    return 1;
}
