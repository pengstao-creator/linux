#include <stdio.h>
#include <string.h>

// 文件复制函数：将源文件内容拷贝到目标文件
void copyFile(char* sourcePath, char* targetPath)
{
    // 打开源文件（r+模式：读写模式）
    FILE *sourceFile = fopen(sourcePath, "r+");
    // 打开目标文件（w+模式：读写模式，如果不存在则创建）
    FILE *targetFile = fopen(targetPath, "w+");
    
    // 检查文件是否打开成功
    if(sourceFile == NULL || targetFile == NULL)
    {
        perror("文件打开失败!");
        return;
    }
    
    char buffer[128];
    size_t readLength;
    
    // 循环读取源文件内容并写入目标文件
    while ( (readLength = fread(buffer, 1, 128, sourceFile)) > 0)
    {
        // 读取到内容后立即写入目标文件
        fwrite(buffer, 1, readLength, targetFile);
        // 清空缓冲区
        memset(buffer, 0, 128);
    }

    // 关闭文件
    fclose(targetFile);
    fclose(sourceFile);
    
    printf("文件复制完成：%s -> %s\n", sourcePath, targetPath);
}

int main(int argc, char const *argv[])
{
    // 调用文件复制函数，将1.txt内容复制到2.txt
    copyFile("./1.txt", "./2.txt");
    return 0;
}