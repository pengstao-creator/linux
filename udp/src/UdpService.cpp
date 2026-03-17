#include "../include/UdpService.hpp"

void Description()
{
    printf("请输入端口,格式为 ./service [prot]\n");
}
int main(int num,char* argv[])
{

    if(num != 2)
    {
        Description();
    }
    UdpService service(std::stoi(argv[1]));
    service.Start();
    
    return 0;
}