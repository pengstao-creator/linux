#include "../../include/common.hpp"
#include <atomic>
#include <functional>
#include <chrono>

/**
 * 主函数 - 启动改进版异步TCP服务器
 * 
 * 该函数创建一个异步TCP服务器，监听指定端口，
 * 支持多客户端连接，添加了信号处理、连接统计和更完善的错误处理
 */
int main() {
    try {
        // 创建IO上下文，用于处理异步操作
        io_context io;
        
        // 创建TCP接受器，监听IPv4地址和指定端口
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), PORT));
        std::cout << "TCP异步服务器启动，监听端口" << PORT << "..." << std::endl;
        std::cout << "按 Ctrl+C 停止服务器" << std::endl;

        // 连接统计变量
        std::atomic<int> total_connections{0};  // 总连接数
        std::atomic<int> active_connections{0}; // 当前活动连接数

        // 设置信号处理，捕获Ctrl+C和终止信号
        boost::asio::signal_set signals(io, SIGINT, SIGTERM);
        signals.async_wait([&](const boost::system::error_code&, int) {
            std::cout << "\n收到关闭信号，停止服务器..." << std::endl;
            std::cout << "总连接数: " << total_connections 
                      << ", 活动连接: " << active_connections << std::endl;
            // 关闭接受器，停止接受新连接
            acceptor.close();
        });

        // 定义一个函数对象，用于从客户端读取数据
        std::function<void(std::shared_ptr<tcp::socket>)> do_read;
        do_read = [&active_connections, &do_read](std::shared_ptr<tcp::socket> socket) {
            // 创建一个共享的缓冲区，用于存储从客户端读取的数据
            auto buf = std::make_shared<std::array<char, BUFFER_SIZE>>();
            
            // 异步读取客户端数据
            socket->async_read_some(buffer(*buf),
                [socket, buf, &active_connections, &do_read](const boost::system::error_code& ec, size_t len) {
                    if (ec) {
                        // 处理错误情况
                        if (ec == boost::asio::error::eof) {
                            std::cout << "客户端正常断开连接" << std::endl;
                            active_connections--;
                        } else if (ec != boost::asio::error::operation_aborted) {
                            std::cerr << "读取错误: " << ec.message() << std::endl;
                            active_connections--;
                        }
                        return;
                    }
                    
                    if (len > 0 && len <= buf->size()) {
                        // 处理接收到的消息
                        std::string recv_msg(buf->data(), len);
                        if (!recv_msg.empty() && recv_msg.back() == '\n') {
                            recv_msg.pop_back();
                        }
                        std::cout << "收到消息: " << recv_msg << " (长度: " << len << ")" << std::endl;

                        // 生成响应消息
                        std::string response;
                        if (recv_msg == "quit" || recv_msg == "exit") {
                            response = "再见！连接即将关闭。\n";
                        } else {
                            response = "服务器回应 [" + recv_msg + "] 长度=" + std::to_string(len) + "\n";
                        }

                        // 异步发送响应给客户端
                        async_write(*socket, buffer(response),
                            [socket, response, recv_msg, &do_read](const boost::system::error_code& ec, size_t written_len) {
                                if (ec) {
                                    std::cerr << "写入错误: " << ec.message() << std::endl;
                                    return;
                                }
                                std::cout << "已发送响应，长度: " << written_len << std::endl;
                                // 如果客户端没有请求关闭连接，继续读取下一条消息
                                if (recv_msg != "quit" && recv_msg != "exit") {
                                    do_read(socket);
                                } else {
                                    std::cout << "客户端请求关闭连接" << std::endl;
                                }
                            });
                    } else {
                        // 如果没有读取到有效数据，继续读取
                        do_read(socket);
                    }
                });
        };

        // 定义一个函数对象，用于处理新的连接请求
        std::function<void()> do_accept;
        do_accept = [&, &do_read]() {
            // 创建一个新的socket对象，用于与客户端通信
            auto socket = std::make_shared<tcp::socket>(io);
            
            // 异步接受客户端连接
            acceptor.async_accept(*socket, 
                [&, socket, &do_read](const boost::system::error_code& ec) {
                    if (ec) {
                        // 处理接受连接失败的情况
                        if (ec != boost::asio::error::operation_aborted) {
                            std::cerr << "接受连接失败: " << ec.message() << std::endl;
                        }
                        return;
                    }
                    
                    // 更新连接统计
                    total_connections++;
                    active_connections++;

                    try {
                        // 获取客户端地址信息并打印
                        auto endpoint = socket->remote_endpoint();
                        std::cout << "\n新客户端连接: " << endpoint.address().to_string() 
                                  << ":" << endpoint.port() << std::endl;
                        std::cout << "活动连接数: " << active_connections 
                                  << ", 总连接数: " << total_connections << std::endl;

                        // 设置socket选项
                        socket->set_option(tcp::no_delay(true));  // 禁用Nagle算法
                        socket->set_option(socket_base::keep_alive(true));  // 启用TCP keep-alive

                        // 发送欢迎消息给客户端
                        std::string welcome = "欢迎连接到服务器！发送 'quit' 或 'exit' 断开连接。\n";
                        async_write(*socket, buffer(welcome),
                            [socket, &do_read](const boost::system::error_code& ec, size_t) {
                                if (ec) {
                                    std::cerr << "发送欢迎消息失败: " << ec.message() << std::endl;
                                    return;
                                }
                                // 开始从客户端读取数据
                                do_read(socket);
                            });
                    } catch (const boost::system::system_error& e) {
                        // 处理获取客户端地址时的错误
                        std::cerr << "处理连接时出错: " << e.what() << std::endl;
                        active_connections--;
                    }
                    
                    // 递归调用do_accept，继续接受下一个连接
                    do_accept();
                });
        };
        
        // 首次调用do_accept，开始接受连接
        do_accept();
        
        // 运行IO上下文，处理所有异步操作
        io.run();
        std::cout << "服务器已停止" << std::endl;
    } catch (const std::exception& e) {
        // 处理异常
        std::cerr << "服务器异常: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
