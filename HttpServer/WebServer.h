#pragma once
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

/*
这个类用来创建服务器(实例化io 实例化acceptor)，和客户端建立连接
服务器的实例对象只需要1份，所以这个类应该是一个单例类
*/
class WebServer
{
private:
	WebServer();

	// 定义属性
	io_context io;	// 上下文对象
	tcp::acceptor acceptor;
	std::string webRoot;

	// 连接操作，和客户端建立连接
	void doAccept();
public:
	WebServer(const WebServer& obj) = delete;
	void operator=(const WebServer& obj) = delete;
	static WebServer& getInstance();

	// 定义一个start()，先做好准备工作
	void start(int port = 8888, std::string webRoot = "D:/html");
};

