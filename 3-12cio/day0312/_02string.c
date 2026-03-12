#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char * msg = "helloworld!!";
    //strlen:获取字符串内容的长度
    printf("msg的长度为:%ld\n",strlen(msg));

    //strcpy  复制，将一个字符串的g内容复制到另一个iu字符串
    char str1[20];
    strcpy(str1,msg);
    printf("str1:%s\n",str1);

    //strcmp strncmp : 可以用来判断两个字符串的值是否一致
    char * str2 = "hellolinuxc...";
    // strcmp()的返回值说明: <0 说明s1<s2  =0 s1=s2  >0 s1>s2
    if(strcmp(msg,str2) == 0)
    {
        printf("两个字符串相等\n");
    }else{
        printf("两个字符串不相等\n");
    }
    //strncmp  用来比较两个i字符串的前N个字符是否相等
    if(strncmp(msg,str1,5) == 0)
    {
        printf("两个字符串前N个字符相等\n");
    }else{
        printf("两个字符串前N个字符不相等\n");
    }

    //strcat  拼接i字符串
    // 想在str1后面，拼接一个任意字符串
    // 如果要做拼接，第一个 参数尽量使用[]
    strcat(str1,"aaaaa");
    printf("拼接后:%s\n",str1);

    //strtok - 按格式a拆分字符串
    //strtok() 是一个有状态的函数，它会在内部保存一个静态指针来跟踪当前解析的位置。
    // strtok() 会修改原字符串，它会把分隔符 : 替换成 \0（字符串结束符）。
    char str3[] = "111111:22222:33333:444444";
    char* splitter = ":";
    // 分割后，会是一个数组，strtok()的返回值是指向数组中第一个u元素位置的
    char* res = strtok(str3,splitter);
    while (res != NULL)
    {
        printf("%s\n",res);
        // 获取后续的字符串
        //第一次调用时，strtok() 初始化内部指针，开始解析字符串

        //后续传入 NULL，告诉 strtok()："继续从上一次结束的位置开始解析"
        res = strtok(NULL,splitter);
    }
    printf("分割以后得字符串i内容:%s\n",str3);
    
    return 0;
}
