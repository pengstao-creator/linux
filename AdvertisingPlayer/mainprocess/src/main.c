#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include "log.h"
#include "msgQueue.h"
#include "sendconfig.h"
#include "data.h"
#include "tool.h"

static atomic_int g_config_update_pending = 1;

void* handleMessage(void * msg)
{
    char inipath[SIZE128] = {0};
    int msgid = get_msg_id();
    if(msgid < 0) return NULL;
    ConfigInfo info;
    initConfigInfo(&info);
    while(1)
    {
        MLOG_D("开始等待消息");
        recv_data(msgid,CONFIG_DONE,inipath,SIZE128);
        MLOG_D("从管道中获取的配置文件路径为:%s",inipath);
        loadConfigInfo(&info,inipath);
        sendConfigRequest(&info);
        clearConfigInfo(&info);
        atomic_store(&g_config_update_pending,1);
    }
}


int main()
{
    //全局初始化,避免局部调用curl_easy_init自动调用curl_global_init,造成可能的线程安全问题
    curl_global_init(CURL_GLOBAL_DEFAULT);

    ConfigInfo info;
    initConfigInfo(&info);
    //这是主进程用来接收消息队列的消息,然后发送到后端服务器
    pthread_t tid;
    pthread_create(&tid,NULL,handleMessage,NULL);
    pthread_detach(tid);

    MQTTClient mqttClient = NULL;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 60;
    int mqttConnected = 0;
    while(1)
    {
        if(atomic_exchange(&g_config_update_pending,0))
        {
            gchar * configpath = getConfigPath();
            if(configpath)
            {
                loadConfigInfo(&info,configpath);
                g_free(configpath);
            }
            if(mqttClient)
            {
                disconnectMQTTClient(&mqttClient);
                mqttClient = NULL;
            }
            mqttConnected = 0;
        }
        if(info._init && !mqttConnected)
        {
            conn_opts.username = info._mqttUsername;
            conn_opts.password = info._mqttPassword;
            if(mqttClient || createMQTTClient(&mqttClient,info._mqttUrl,"linux-client"))
            {
                mqttConnected = connectMQTTClient(&mqttClient,&conn_opts);
                if(mqttConnected)
                {
                    subscribeMQTTClient(&mqttClient,info._commandTopic,0);
                    subscribeMQTTClient(&mqttClient,info._advertTopic,0);
                }
            }
        }
        if(info._init && mqttConnected)
        {
            sendHearRequest(&mqttClient,&info);
            MLOG_D("发送一次心跳请求"); 
        }
        sleep(5);
    }
    clearConfigInfo(&info);
    destroyMQTTClient(&mqttClient);
    curl_global_cleanup();  
    return 0;
}
