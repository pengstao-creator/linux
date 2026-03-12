#include <stdio.h>

// 按字符读写文件
// fputc(): 向文件写入单个字符
// fgetc(): 从文件读取单个字符
int main(int argc, char const *argv[])
{
    // 打开文件（w+模式：读写模式）
    FILE *file = fopen("./test.txt", "w+");
    if(file == NULL)
    {
        perror("文件打开失败!");
        return -1;
    }

    // 按字符写入数据
    int numbers[5] = {10, 20, 30, 40, 60};
    printf("写入的字符值:");
    for(int i = 0; i < 5; i++)
    {
        fputc(numbers[i], file);
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // 将文件指针移动到文件开头
    fseek(file, 0, SEEK_SET);

    // 按字符读取数据
    printf("读取的字符值:");
    int character;
    // fgetc()在文件结束时返回EOF
    while( (character = fgetc(file)) != EOF )
    {
        printf("%d ", character);
    }
    printf("\n");

    // 关闭文件
    fclose(file);

    return 0;
}