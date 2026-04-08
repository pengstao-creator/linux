#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "log.h"
#include "msgQueue.h"
#include "sendconfig.h"
#include "data.h"
void* handleMessage(void * msg)
{
    //从信号管道读取消息
    char inipath[SIZE128] = {0};
    int msgid = get_msg_id();
    if(msgid < 0) return NULL;
    while(1)
    {
        MLOG_D("开始等待消息");
        recv_data(msgid,CONFIG_DONE,inipath,SIZE128);
        MLOG_D("从管道中获取的配置文件路径为:%s",inipath);
        sendConfigRequest(inipath);
    }
}


int main()
{
    //全局初始化,避免局部调用curl_easy_init自动调用curl_global_init,造成可能的线程安全问题
    curl_global_init(CURL_GLOBAL_DEFAULT);

    //这是主进程用来接收消息队列的消息,然后发送到后端服务器
    pthread_t tid;
    pthread_create(&tid,NULL,handleMessage,NULL);
    pthread_detach(tid);

    while(1)
    {
        //发送心跳请求
        MLOG_D("发送一次心跳请求");
        sleep(5);
    }
    curl_global_cleanup();  
    return 0;
}
