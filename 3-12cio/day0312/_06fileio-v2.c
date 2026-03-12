#include <stdio.h>
#include <strings.h>

// 文件复制，将A文件的内容拷贝到B文件
void copyFile(char* srcPath,char* targetPath)
{
    FILE *srcFile = fopen(srcPath,"r+");
    FILE *targetFile = fopen(targetPath,"w+");
    if(srcFile == NULL || targetFile == NULL)
    {
        perror("文件打开失败!");
        return;
    }
    char buff[128];
    //1 先读取srcPath文件内容
    size_t len;
    while ( (len = fread(buff,1,128,srcFile)) > 0)
    {
        // len>0，说明本次读取到g内容，读到就要把内容写给target
        fwrite(buff,1,len,targetFile);
        //清空一下buff
        bzero(buff,128);
    }

    // 关闭文件
    fclose(targetFile);
    fclose(srcFile);
}

int main(int argc, char const *argv[])
{
    copyFile("./1.txt","./2.txt");
    return 0;
}
