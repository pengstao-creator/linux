#include <stdio.h>

/**
 * 文件IO流：用于对文件进行输入输出操作
 * 标准输入输出流：用于对键盘和屏幕进行输入输出操作
 * C语言提供了三种标准IO流：
 * stdin: 标准输入流，从键盘获取数据（scanf()、getc()、getchar()等底层使用）
 * stdout: 标准输出流，将数据输出到屏幕（printf()、putc()、putchar()等底层使用）
 * stderr: 标准错误流，将错误信息输出到屏幕（perror()等使用）
 */
int main(int argc, char const *argv[])
{
    // 标准输出示例
    // 直接使用printf输出
    printf("使用printf输出: %s\n", "Hello World!");
    
    // 使用fprintf输出到stdout
    fprintf(stdout, "使用fprintf输出到stdout: 姓名:%s, 年龄:%d\n", "zhangsan", 30);
    
    // 使用fprintf输出到stderr
    fprintf(stderr, "使用fprintf输出到stderr: 姓名:%s, 年龄:%d\n", "zhangsan", 30);
    
    // 使用sprintf格式化字符串
    char formatStr[] = "姓名:%s, 年龄:%d, 性别:%s";
    char buffer[128] = {0};
    
    // 将格式化后的字符串存储到buffer中
    sprintf(buffer, formatStr, "李四", 20, "男");
    printf("使用sprintf格式化后的结果: %s\n", buffer);
    
    // 以下是注释掉的输入示例
    /*
    // 使用scanf输入
    char inputStr[100];
    printf("请输入一个字符串: ");
    scanf("%s", inputStr);
    printf("输入的是: %s\n", inputStr);
    
    // 使用getc从stdin获取输入
    printf("请输入一个字符: ");
    int charInput = getc(stdin);
    printf("输入的字符是: %c\n", charInput);
    
    // 使用getchar获取输入（默认从stdin）
    printf("请输入另一个字符: ");
    int charInput2 = getchar();
    printf("输入的字符是: %c\n", charInput2);
    
    // 使用putc输出到stdout
    putc('A', stdout);
    printf(" ");
    // 使用putchar输出（默认到stdout）
    putchar('B');
    printf("\n");
    */
    
    return 0;
}