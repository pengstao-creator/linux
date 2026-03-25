#include <iostream>
#include "../include/WebServer.h"

int main(int argc, char* argv[]) {
    try {
        if(argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
            return 1;
        }
        uint16_t port = std::stoi(argv[1]);
        
        // 使用绝对路径或相对于可执行文件的路径
        WebServer::getInstance().start(port, "../html");
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
