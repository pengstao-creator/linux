#include "../include/client.hpp"

void Description()
{
    printf("请输入服务器ip,端口,格式为 ./service [ip] [prot]\n");
}
int main(int num,char* argv[])
{

    if(num != 3)
    {
        Description();
    }
    std::string ip = argv[1];
    uint16_t prot = std::stoi(argv[2]);

    Client c(ip,prot);
    c.Start();
    return 0;
}