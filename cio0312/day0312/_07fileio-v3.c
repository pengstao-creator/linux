#include <stdio.h>

// 按字符读写:
// fputc()  向文件写入
// fgetc() 从文件读取
int main(int argc, char const *argv[])
{
    FILE *file = fopen("./test.txt","w+");
    if(file == NULL)
    {
        perror("文件打开失败!");
        return -1;
    }

    // 按字符写入
    int arr[5] = {10,20,30,40,60};
    for(int i=0;i<5;i++)
    {
        fputc(arr[i],file);
    }

    // 把指针移动到头
    fseek(file,0,SEEK_SET);

    // 按u字符读取
    int res;
    // fgetc()读取 的时候，如果到了结尾，那么会返回EOF
    while( (res = fgetc(file)) != EOF )
    {
        printf("%d\n",res);
    }

    fclose(file);

    return 0;
}
