#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    // 在c中如何表示真非0 假0，在c11标准i时，就推出了bool类型，用来表示真  和  假
    // c11中的bool其实是假装实现了bool，他底层其实还是0 1,bool其实一个宏
    bool i = false;
    if(i)
    {
        printf("这是真\n");
    }else{
        printf("这是假\n");
    }

    // 扩展：c中对于指针而言，NULL是假   非NULL就是真
    char *msg = "";
    if(msg)
    {
        printf("msg这是真\n");
    }else{
        printf("msg这是假\n");
    }
    return 0;
}
