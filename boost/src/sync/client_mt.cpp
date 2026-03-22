#include "common.hpp"
#include <thread>

// 全局变量，用于控制主线程的运行状态
bool g_running = true;

/**
 * 从服务器接收消息的线程函数
 * @param socket 与服务器连接的socket引用
 * 
 * 该函数在一个单独的线程中运行，
 * 不断从服务器读取消息并打印，
 * 当服务器断开连接时，设置g_running为false，通知主线程退出
 */
void recvMsgFromServer(tcp::socket& socket)
{
    // 创建一个缓冲区，用于存储从服务器读取的数据
    char buff[BUFFER_SIZE];
    
    while (1)
    {
        // 同步读取服务器数据
        boost::system::error_code error;
        size_t len = socket.read_some(buffer(buff), error);

        // 处理错误情况
        if (error == boost::asio::error::eof) {
            std::cout << "客户端断开连接" << std::endl;
            g_running = false;
            break;
        }

        // 打印接收到的消息
        if (len > 0)
        {
            std::cout << "接收服务端数据成功，数据为:" << std::string(buff, len) << std::endl;
        }
    }
}

/**
 * 主函数 - 启动同步多线程TCP客户端
 * 
 * 该函数创建一个同步TCP客户端，连接到指定的服务器，
 * 然后创建一个线程用于接收服务器消息，
 * 主线程用于从标准输入读取消息并发送给服务器
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

        // 创建一个线程，用于从服务器接收消息
        std::thread send_thread(recvMsgFromServer, std::ref(socket));

        // 主线程循环从标准输入读取消息并发送给服务器
        std::string msg;
        while (g_running)
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
