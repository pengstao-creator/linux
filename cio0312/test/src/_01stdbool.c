#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    // C语言中通常用非0表示真，0表示假
    // C11标准引入了bool类型来更清晰地表示真假
    // 注意：C11中的bool本质上是宏定义，底层仍然是0和1
    bool flag = false;
    
    if(flag)
    {
        printf("这是真\n");
    }else{
        printf("这是假\n");
    }

    // 扩展知识：对于指针，NULL表示假，非NULL表示真
    char *message = "";
    if(message)
    {
        printf("msg这是真\n");
    }else{
        printf("msg这是假\n");
    }
    
    return 0;
}