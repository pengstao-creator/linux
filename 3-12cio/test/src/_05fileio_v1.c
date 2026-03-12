#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 1. 向test.txt文件中写入内容
    // 1.1 打开文件（w+模式：读写模式，如果文件不存在则创建）
    FILE* file = fopen("./test.txt", "w+");
    if(file == NULL)
    {
        perror("文件打开失败");
        return -1;
    }

    // 1.2 向文件写入数据
    char* message = "hello world!!!!";
    size_t writeLen = fwrite(message, sizeof(char), strlen(message), file);
    if(writeLen != strlen(message))
    {
        perror("写入失败!");
        fclose(file);
        return -1;
    }
    printf("写入成功!写入了 %zu 个字符\n", writeLen);

    // 1.3 将文件指针移动到文件开头
    fseek(file, 0, SEEK_SET);

    // 2. 从test.txt文件中读取内容
    char buffer[128] = {0}; // 初始化缓冲区
    size_t readLen = fread(buffer, sizeof(char), 128, file);
    if(readLen == 0)
    {
        perror("读取失败!");
        fclose(file);
        return -1;
    }
    printf("读取成功!内容: %s\n", buffer);

    // 3. 关闭文件
    fclose(file);
    return 0;
}