#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //1 向一个1.txt文件中写入内容
    //1.1 打开文件
    FILE* file = fopen("./test.txt","w+");

    //1.2 向文件写数据
    char* msg = "hello world!!!!";
    size_t len = fwrite(msg,sizeof(char),strlen(msg),file);
    if(len == -1)
    {
        perror("写入失败!\n");
        return -1;
    }
    printf("写入成功!\n");

    // 把指针移动到开头去
    fseek(file,0,SEEK_SET);

    //2 从1.txt文件中读取内容
    char buff[128];
    len = fread(buff,sizeof(char),128,file);
    if(len == -1)
    {
        perror("读取失败!\n");
        return -1;
    }
    printf("u读取成功!内容:%s\n",buff);


    // 关闭文件
    fclose(file);
    return 0;
}
