#include <stdio.h>
#include <curl/curl.h>

// 当要使用三方链接库得时候，在编译时，要去指定链接库得名字才可以
// -l链接库的名字  加载链接库
// -l后面只用写名字y就可以了，在加载的时候，会去默认路径 /usr/local/lib下自己拼接i前缀和后缀去找到对应的链接库
// 如果是命令，a那就用a下面这个l命令就 e可以了
//gcc ./main.c -lcurl -o ./main

// 回调函数：处理服务器返回的数据
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    char* content  =  (char*)ptr;
    printf("%s\r\n",content);
    return size * nmemb;
}

int main(int argc, char const *argv[])
{
    // 通过liburl向n三方发起一个http请求
    //1 全局初始化
    curl_global_init(CURL_GLOBAL_DEFAULT);

    //2 获取curl句柄
    CURL *curl = curl_easy_init();
    if(curl)
    {
        //3 给curl设置请求参数，比如设置url地址，和获取响应的回调函数
        curl_easy_setopt(curl,CURLOPT_URL,"http://www.baidu.com");  //设置url
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);

        //4 发起请求
        CURLcode code = curl_easy_perform(curl);
        if(code != CURLE_OK)
        {
            perror("发起请求失败!");
        }
        // 请求结束要释放
        curl_easy_cleanup(curl);
    }

    // 还可以释放全局
    curl_global_cleanup();
    return 0;
}
