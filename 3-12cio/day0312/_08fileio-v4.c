#include <stdio.h>
#include <strings.h>

// 按字符串读写:
// fputs()
// fgets()
int main(int argc, char const *argv[])
{
    FILE *file = fopen("./test.txt","w+");
    if(file == NULL)
    {
        perror("文件打开失败!");
        return -1;
    }

    // 按字符串写入
    for(int i=0;i<10;i++)
    {
        fputs("helloworld!!aaaaabbbbcccc\n",file);
    }

    // 把指针移动到头
    fseek(file,0,SEEK_SET);

    // 按字符串读取
    char buff[64];
    int len;
    char *msg;
    // fgetc()读取 的时候，如果到了结尾，那么会返回EOF
    while( (msg = fgets(buff,64,file)) != NULL)
    {
        printf("%s\n",buff);
        printf("msg:%s\n",msg);
        bzero(buff,64);
    }

    fclose(file);

    return 0;
}
