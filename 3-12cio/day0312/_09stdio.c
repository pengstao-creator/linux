#include <stdio.h>

/**
 * 文件IO流：是对文件做输入输出操作
 * 标准输入输出流： 对键盘 屏幕做输入输出 操作的
 * c中有提供三种标准IO流：三种标准输入输出流
 * stdin: 获取键盘输入的数据  scanf()底层其实就是从stdin流获取数据  getc() getchar()他们e都可以通过stdin标准输入
 *         来获取键盘输入
 * stdout: 将数据输出给屏幕做展示 printf()就是通过stdout流将数据h展示给g屏幕 putc() putchar()他们y都可以通过stdout
 *          将输出给屏幕做展示
 * stderr: 将数据输出给屏幕做展示 perror
 */
int main(int argc, char const *argv[])
{
    // 输入
    // char *msg;
    // scanf("%s",msg);
    // printf("输入的是:%s\n",msg);

    // 通过getc() getchar()来输入
    // int c = getc(stdin);
    // printf("%c\n",c);

    // getchar() 其实和getc()o差不读，h都是读取 按char做读取，只是说getchar()不用传参数，默认i就是g从stdin来获取的
    // int c = getchar();
    // printf("%c\n",c);

    // putc('A',stdout);
    // putchar('B');

    // 按格式输出字符串到屏幕
    printf("msg:%s\n","xxxxx");

    // fprintf()可以格式化字符串输出  fprintf()需要显示指定将数据输出到哪儿去
    fprintf(stdout,"姓名:%s,年龄:%d\n","zhangsan",30);
    fprintf(stderr,"姓名:%s,年龄:%d\n","zhangsan",30);

    // 可以格式化字符串
    char *str1 = "姓名:%s,年龄:%d,性别:%s";
    char buff[128];
    // 将str1字符串格式化以后，交给buff来接收
    sprintf(buff,str1,"李四",20,"男");
    printf("%s\n",buff);
    return 0;
}
