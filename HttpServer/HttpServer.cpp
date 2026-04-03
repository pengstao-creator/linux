#include <iostream>
#include "WebServer.h"

int main()
{
    try
    {
        WebServer& server = WebServer::getInstance();
        server.start();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
