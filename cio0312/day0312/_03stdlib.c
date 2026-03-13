#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 内存管理：malloc calloc relloc n释放:free
    //malloc 开辟指定大小空间
    //calloc  开辟num*sizeof()大小的空间
    // 比如开辟10块intg类型j空间
    int* p1 = (int*)malloc(10*sizeof(int));
    for(int i=0;i<10;i++)
    {
        p1[i] = i;
        printf("%d\t",p1[i]);
    }
    printf("\n");

    int *p2 = (int*)calloc(10,sizeof(int));
    for(int i=0;i<10;i++)
    {
        p2[i] = i+100;
        printf("%d\t",p2[i]);
    }
    printf("\n");

    // a释放i空间
    free(p1);
    free(p2);

    // 字符串转数字
    // char* str1 = "103.1432";
    char *str1 = "10a1";
    // 转为int
    int a = atoi(str1);
    printf("int:%d\n",a);
    // 转为double
    double b = atof(str1);
    printf("double:%lf\n",b);
    // 转为long
    long c = atol(str1);
    printf("long:%ld\n",c);

    // 退出&运行
    // 退出当前程序
    // exit(EXIT_SUCCESS);
    printf("1111111111111111111\n");

    // 运行一个i指令  ifconfig
    system("ifconfig");

    return 0;
}
