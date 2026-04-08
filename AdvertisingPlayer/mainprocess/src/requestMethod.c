#include "requestMethod.h"
#include "log.h"

void Request(const char * url,const char * msg , curl_write_callback fn)
{
    CURL * curl = curl_easy_init();
    CURLcode res;
    if(curl)
    {
        //设置请求设置
        curl_easy_setopt(curl,CURLOPT_URL,url);
        curl_easy_setopt(curl,CURLOPT_WILDCARDMATCH,fn);
        if(msg)
        {
            //指定post请求
            curl_easy_setopt(curl,CURLOPT_POST,1L);
            //设置post请求数据,CURLOPT_COPYPOSTFIELDS会复制数据,msg可直接释放
            //CURLOPT_POSTFIELDS 不会复制数据,msg不能立即释放
            curl_easy_setopt(curl,CURLOPT_COPYPOSTFIELDS,msg);
        }
         // 可选设置：超时
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L); // 连接超时10秒
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);        // 请求总超时30秒

        //执行请求
        res = curl_easy_perform(curl);

        //请求结果分析
        if(res != CURLE_OK)
        {
            MLOG_W("get请求失败,%s",curl_easy_strerror(res));
        }
    }
    curl_easy_cleanup(curl);
}


void sendGetRequest(const char * url,curl_write_callback fn)
{
    Request(url,NULL,fn);
}

void sendPostRequest(const char * url,const char * msg , curl_write_callback fn)
{
    Request(url,msg,fn);
}