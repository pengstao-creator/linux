#include "common.hpp"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

/**
 * 主函数 - 演示使用固定长度处理粘性数据
 * 
 * 该函数创建一个TCP客户端，连接到指定的服务器，
 * 发送一个固定长度的消息，然后使用固定大小的缓冲区
 * 分两次读取服务器的响应，演示如何使用固定长度处理粘性数据
 */
int main() {
    // 创建IO上下文，用于处理IO操作
    io_context io;
    
    // 创建socket对象，用于与服务器通信
    tcp::socket socket(io);
    // 创建服务器端点
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), PORT);
    // 连接到服务器
    socket.connect(endpoint);

    // 准备要发送的消息，长度为10个字符
    std::string message = "HelloWorld";
    // 发送消息给服务器
    write(socket, buffer(message));

    // 创建一个固定大小的缓冲区，大小为5个字符
    std::array<char, 5> buf;
    
    // 读取5个字符
    read(socket, buffer(buf));
    // 打印接收到的前5个字符
    std::cout << "接收到: " << std::string(buf.data(), buf.size()) << std::endl;

    // 读取接下来的5个字符
    read(socket, buffer(buf));
    // 打印接收到的后5个字符
    std::cout << "接收到: " << std::string(buf.data(), buf.size()) << std::endl;

    return 0;
}
