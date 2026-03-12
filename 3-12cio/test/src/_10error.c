#include <stdio.h>
#include <string.h>
#include <errno.h>

// errno是全局变量，用于存储错误码
extern int errno;

// 登录函数
int login(char* username, char* password)
{
    // 参数校验
    if(username == NULL || password == NULL)
    {
        // 设置错误码为EINVAL（无效参数）
        errno = EINVAL;
        return -1;
    }
    
    // 用户名和密码验证
    if(strcmp(username, "admin") != 0 || strcmp(password, "123") != 0)
    {
        // 设置自定义错误码
        errno = 35;
        return -1;
    }
    
    return 1; // 登录成功
}

int main(int argc, char const *argv[])
{
    // 测试登录函数（使用错误的密码）
    int result = login("admin", "123456");
    
    if(result == -1)
    {
        // 根据错误码处理不同的错误情况
        if(errno == EINVAL)
        {
            perror("登录失败!");
        }
        else if(errno == 35)
        {
            fprintf(stderr, "登录失败! %s\n", "用户名或密码输入错误!");
        }
        else
        {
            fprintf(stderr, "登录失败,原因未知!\n");
        }
    }
    else
    {
        printf("登录成功!\n");
    }
    
    return 0;
}