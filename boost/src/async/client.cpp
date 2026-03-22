#include "common.hpp"
#include <array>

/**
 * 向服务器发送消息
 * @param socket 与服务器连接的socket智能指针
 * 
 * 该函数从标准输入读取用户输入的消息，
 * 然后异步发送给服务器，发送完成后递归调用自己，
 * 继续等待用户输入
 */
void sendMsgToServer(std::shared_ptr<tcp::socket> socket)
{
    std::cout << "请输入要发送的数据:" << std::endl;
    std::string msg;
    std::cin >> msg;

    // 异步发送消息给服务器
    socket->async_write_some(buffer(msg.c_str(), msg.size()),
        [socket, msg](boost::system::error_code ec2, size_t) {
            if (!ec2)
            {
                std::cout << "给服务端发送消息成功!" << std::endl;
            }
            // 递归调用自己，继续等待用户输入
            sendMsgToServer(socket);
        });
}

/**
 * 从服务器读取消息
 * @param socket 与服务器连接的socket智能指针
 * 
 * 该函数异步从服务器读取消息，
 * 当读取到消息后，打印消息内容，然后递归调用自己，
 * 继续等待服务器的消息
 */
void readMsgFromServer(std::shared_ptr<tcp::socket> socket)
{
    // 创建一个共享的缓冲区，用于存储从服务器读取的数据
    auto buff = std::make_shared<std::array<char, 128>>();
    
    // 异步读取服务器数据
    socket->async_read_some(buffer(*buff),
        [socket, buff](boost::system::error_code ec1, size_t length) {
            if (!ec1)
            {
                // 打印接收到的消息
                std::cout << "接收到服务端发送的消息:"
                    << std::string(buff->data(), length) << std::endl;
                // 递归调用自己，继续等待服务器的消息
                readMsgFromServer(socket);
            }
            else { 
                // 处理错误情况
                if (ec1 == boost::asio::error::eof)
                    std::cout << "服务端断开连接" << std::endl;
                else
                    std::cout << "读取错误: " << ec1.message() << std::endl;
            }
        });
}

/**
 * 主函数 - 启动异步TCP客户端
 * 
 * 该函数创建一个异步TCP客户端，连接到指定的服务器，
 * 然后开始发送和接收消息
 */
int main() {
    try {
        // 创建IO上下文，用于处理异步操作
        boost::asio::io_context io;

        // 创建TCP解析器，用于解析服务器地址
        tcp::resolver resolver(io);
        boost::system::error_code ec;
        // 解析服务器地址和端口
        auto endpoints = resolver.resolve("127.0.0.1", std::to_string(PORT), ec);
        if (ec) throw boost::system::system_error(ec);

        // 创建socket对象，用于与服务器通信
        auto socket = std::make_shared<tcp::socket>(io);
        
        // 异步连接到服务器
        boost::asio::async_connect(*socket, endpoints,
            [socket](const boost::system::error_code& ec,
                const tcp::endpoint& endpoint) {
                    if (ec) {
                        std::cerr << "连接失败：" << ec.message() << std::endl;
                        return;
                    }
                    // 连接成功后，开始发送和接收消息
                    sendMsgToServer(socket);
                    readMsgFromServer(socket);
            });

        // 运行IO上下文，处理所有异步操作
        io.run();
    }
    catch (const std::exception& e) {
        // 处理异常
        std::cerr << "客户端错误：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
