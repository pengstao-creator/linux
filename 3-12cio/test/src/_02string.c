#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *message = "helloworld!!";
    
    // strlen: 获取字符串的实际长度（不包括结束符）
    printf("message的长度为: %ld\n", strlen(message));

    // strcpy: 将一个字符串复制到另一个字符串
    char str1[20];
    strcpy(str1, message);
    printf("str1: %s\n", str1);

    // strcmp 和 strncmp: 比较字符串
    char *str2 = "hellolinuxc...";
    // strcmp返回值: <0 表示s1<s2, =0 表示s1=s2, >0 表示s1>s2
    if(strcmp(message, str2) == 0)
    {
        printf("两个字符串相等\n");
    }else{
        printf("两个字符串不相等\n");
    }
    
    // strncmp: 比较两个字符串的前N个字符
    if(strncmp(message, str1, 5) == 0)
    {
        printf("两个字符串前5个字符相等\n");
    }else{
        printf("两个字符串前5个字符不相等\n");
    }

    // strcat: 拼接字符串
    // 注意：第一个参数应该是字符数组，有足够的空间
    strcat(str1, "aaaaa");
    printf("拼接后: %s\n", str1);

    // strtok: 按指定分隔符拆分字符串
    // 注意：strtok是有状态的函数，会修改原字符串
    char str3[] = "111111:22222:33333:444444";
    char* delimiter = ":";
    
    // 第一次调用时传入字符串和分隔符
    char* token = strtok(str3, delimiter);
    while (token != NULL)
    {
        printf("%s\n", token);
        // 后续调用传入NULL，继续解析
        token = strtok(NULL, delimiter);
    }
    
    printf("分割后的字符串内容: %s\n", str3);
    
    return 0;
}