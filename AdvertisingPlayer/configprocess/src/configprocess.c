#include <glib-2.0/glib.h>
#include <string.h>
#include "configprocess.h"
#include "log.h"
#include "tool.h"
#include "msgQueue.h"
#include "data.h"
void parseConfig(struct mg_connection *c,struct mg_http_message *hm)
{
    ConfigInfo info;
    initConfigInfo(&info);
    loadNetworkInfo(&info, hm);
   
    MLOG_D("提交配置: backendUrl=%s mqttUrl=%s wifiName=%s chip=%s detailAddr=%s mqttUsername=%s heartbeatTopic=%s commandTopic=%s advertTopic=%s\n",
            info._backendUrl, info._mqttUrl, info._wifiName, info._chip, info._detailAddr, info._mqttUsername, info._heartbeatTopic, info._commandTopic, info._advertTopic);

    mg_http_reply(c, 200, "Content-Type: application/json; charset=utf-8\r\n",
                    "{\"ok\":true}");

    
    //将配置写入文件
    gchar * configpath = getConfigPath();
    MLOG_D("配置文件路径:%s",configpath ? configpath : "(null)");
    if(!configpath)
    {
        clearConfigInfo(&info);
        return;
    }
    saveConfigInfo(&info,configpath);
    MLOG_D("配置写入文件成功");
    //将配置写入完成的消息投入到消息队列
    int msgid = get_msg_id();
    if(msgid >= 0)
    {
        send_data(msgid,CONFIG_DONE,configpath);
        MLOG_D("消息队列写入完成");
    }
    else
    {
        MLOG_E("获取消息队列失败，msgid=%d",msgid);
    }
    
    g_free(configpath);
    clearConfigInfo(&info);
}
