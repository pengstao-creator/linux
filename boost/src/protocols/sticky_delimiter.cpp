#include "common.hpp"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

/**
 * 主函数 - 演示使用分隔符处理粘性数据
 * 
 * 该函数创建一个TCP客户端，连接到指定的服务器，
 * 发送带有换行符分隔的消息，然后使用read_until函数
 * 按换行符读取服务器的响应，演示如何处理粘性数据
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

    // 准备要发送的消息，包含两个以换行符分隔的消息
    std::string message = "Hello\nWorld\n";
    // 发送消息给服务器
    write(socket, buffer(message));

    // 创建一个streambuf，用于存储从服务器读取的数据
    streambuf buf;
    
    // 读取直到遇到第一个换行符
    read_until(socket, buf, "\n");
    // 从streambuf中读取数据
    std::istream is(&buf);
    std::string line;
    std::getline(is, line);
    // 打印接收到的第一行数据
    std::cout << "接收到: " << line << std::endl;

    // 读取直到遇到第二个换行符
    read_until(socket, buf, "\n");
    std::getline(is, line);
    // 打印接收到的第二行数据
    std::cout << "接收到: " << line << std::endl;

    return 0;
}
