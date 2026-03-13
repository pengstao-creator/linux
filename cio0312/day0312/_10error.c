#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>

// 定义errno来接收错误码
extern int errno;

int login(char* username,char* pwd)
{
    //1 先做校验
    if(username == NULL || pwd == NULL)
    {
        // 给errno设置i值，s表示不同 的错误信息
        errno = EINVAL;
        return -1;
    }
    if(strcmp(username,"admin") !=0 || strcmp(pwd,"123") != 0)
    {
        // 如果错误a码没有，就给一个i自定义
        errno = 35;
        return -1;
    }
    return 1;
}

int main(int argc, char const *argv[])
{

    int res = login("admin","123456");
    if(res == -1)
    {
        if(errno == EINVAL)
        {
            perror("登录失败!");
        }
        else if(errno == 35)
        {
            fprintf(stderr,"登录失败!%s\n","用户名或密码输入错误!");
        }else{
            fprintf(stderr,"登录失败,原因未知!\n");
        }
    }
    else
    {
        printf("登录成功!\n");
    }
    return 0;
}
