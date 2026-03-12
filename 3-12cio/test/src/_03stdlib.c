#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 内存管理函数：malloc、calloc、realloc 和 free
    
    // malloc: 分配指定大小的内存空间
    int* ptr1 = (int*)malloc(10 * sizeof(int));
    printf("使用malloc分配的内存:");
    for(int i = 0; i < 10; i++)
    {
        ptr1[i] = i;
        printf("%d\t", ptr1[i]);
    }
    printf("\n");

    // calloc: 分配num个指定大小的内存空间，并初始化为0
    int* ptr2 = (int*)calloc(10, sizeof(int));
    printf("使用calloc分配的内存:");
    for(int i = 0; i < 10; i++)
    {
        ptr2[i] = i + 100;
        printf("%d\t", ptr2[i]);
    }
    printf("\n");

    // 释放内存
    free(ptr1);
    free(ptr2);

    // 字符串转数字函数
    char* str = "10a1";
    
    // atoi: 字符串转整数
    int intValue = atoi(str);
    printf("转为int: %d\n", intValue);
    
    // atof: 字符串转双精度浮点数
    double doubleValue = atof(str);
    printf("转为double: %lf\n", doubleValue);
    
    // atol: 字符串转长整数
    long longValue = atol(str);
    printf("转为long: %ld\n", longValue);

    // 程序控制函数
    // exit(EXIT_SUCCESS); // 退出程序
    printf("程序继续执行...\n");

    // system: 执行系统命令
    printf("执行ifconfig命令:\n");
    system("ifconfig");

    return 0;
}