#include <glib-2.0/glib.h>
#include "sendconfig.h"
#include "data.h"
#include "log.h"
#include "tool.h"

#define MACHINE_CODE_PATH "/etc/machine-id"


// 返回新分配的字符串，调用者需使用 g_free() 释放
gchar* get_sn(void) 
{
    gchar *contents = NULL;
    size_t length = 0;
    GError *gerror = NULL;

    if (g_file_get_contents(MACHINE_CODE_PATH, &contents, &length, &gerror)) {
        return contents; // 调用者负责 g_free(contents)
    } else {
        handleError("读取机器码失败",gerror);
        return NULL;
    }
}

size_t on_response(char* buffer,size_t size,size_t nitems,void* userdata)
{
    MLOG_D("回掉函数执行");
    return 0;
}

void sendConfigRequest(ConfigInfo * info)
{
    if(info == NULL || !info->_init)
    {
        MLOG_E("info is NULL or data");
        return;
    }
    //构建后端服务器访问网址
    gchar * sn = get_sn();
    const char * urlform = "http://%s?chip=%s&detailAddr=%s&sn=%s";
    gchar url[SIZE256];
    sprintf(url,urlform,info->_backendUrl,info->_chip,info->_detailAddr,sn);
    g_free(sn);
    sendGetRequest(url,on_response);
}



void sendHearRequest(MQTTClient * client,ConfigInfo * info)
{
    if(!client || !info || !info->_init)
    {
        MLOG_E("mqttclient or info is NULL or data");
        return;
    }
    gchar payload[SIZE256];
    const char * chip = info->_chip ? info->_chip : "";
    const char * detailAddr = info->_detailAddr ? info->_detailAddr : "";
    const char * topic = info->_heartbeatTopic ? info->_heartbeatTopic : "heartbeat";
    g_snprintf(payload,sizeof(payload),"{\"chip\":\"%s\",\"detailAddr\":\"%s\"}",chip,detailAddr);
    publishMessage(client,topic,payload,0,0);
}
