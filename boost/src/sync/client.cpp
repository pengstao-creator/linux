#include "common.hpp"

/**
 * 主函数 - 启动同步TCP客户端
 * 
 * 该函数创建一个同步TCP客户端，连接到指定的服务器，
 * 然后从标准输入读取消息并发送给服务器
 */
int main() {
    try {
        // 创建IO上下文，用于处理IO操作
        boost::asio::io_context io;

        // 创建TCP解析器，用于解析服务器地址
        tcp::resolver resolver(io);
        boost::system::error_code ec;
        // 解析服务器地址和端口
        auto endpoints = resolver.resolve("127.0.0.1", std::to_string(PORT), ec);
        if (ec) throw boost::system::system_error(ec);

        // 创建socket对象，用于与服务器通信
        tcp::socket socket(io);
        // 同步连接到服务器
        boost::asio::connect(socket, endpoints);
        std::cout << "成功连接到服务器！" << std::endl;

        // 循环从标准输入读取消息并发送给服务器
        std::string msg;
        while (1)
        {
            std::cout << "请输入要发送的消息:" << std::endl;
            std::cin >> msg;
            // 同步发送消息给服务器
            socket.write_some(buffer(msg, msg.size()));
        }
    }
    catch (const std::exception& e) {
        // 处理异常
        std::cerr << "客户端错误：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
