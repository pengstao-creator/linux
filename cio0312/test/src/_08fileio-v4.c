#include <stdio.h>
#include <string.h>

// 按字符串读写文件
// fputs(): 向文件写入字符串
// fgets(): 从文件读取字符串
int main(int argc, char const *argv[])
{
    // 打开文件（w+模式：读写模式）
    FILE *file = fopen("./test.txt", "w+");
    if(file == NULL)
    {
        perror("文件打开失败!");
        return -1;
    }

    // 按字符串写入数据
    char* writeStr = "helloworld!!aaaaabbbbcccc\n";
    printf("开始写入字符串...\n");
    for(int i = 0; i < 10; i++)
    {
        fputs(writeStr, file);
    }
    printf("写入完成\n");

    // 将文件指针移动到文件开头
    fseek(file, 0, SEEK_SET);

    // 按字符串读取数据
    printf("\n开始读取字符串...\n");
    char buffer[64] = {0};
    char *readStr;
    
    // fgets()在文件结束时返回NULL
    while( (readStr = fgets(buffer, 64, file)) != NULL)
    {
        printf("缓冲区内容: %s", buffer);
        printf("返回指针内容: %s", readStr);
        // 清空缓冲区
        memset(buffer, 0, 64);
    }
    printf("读取完成\n");

    // 关闭文件
    fclose(file);

    return 0;
}