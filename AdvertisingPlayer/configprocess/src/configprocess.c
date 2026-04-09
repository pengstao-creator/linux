#include <glib-2.0/glib.h>
#include <string.h>
#include "configprocess.h"
#include "log.h"
#include "tool.h"
#include "msgQueue.h"
#include "data.h"
void parseConfig(struct mg_connection *c,struct mg_http_message *hm)
{
    //读取配置
    char backendUrl[SIZE256] = {0};
    char mqttUrl[SIZE256] = {0};
    char wifiName[SIZE128] = {0};
    char wifiPwd[SIZE128] = {0};
    char chip[SIZE64] = {0};
    char detailAddr[SIZE256] = {0};
    char mqttAccount[SIZE128] = {0};
    char mqttPassword[SIZE128] = {0};
    mg_http_get_var(&hm->body, "backendUrl", backendUrl, sizeof(backendUrl));
    mg_http_get_var(&hm->body, "mqttUrl", mqttUrl, sizeof(mqttUrl));
    mg_http_get_var(&hm->body, "wifiName", wifiName, sizeof(wifiName));
    mg_http_get_var(&hm->body, "wifiPwd", wifiPwd, sizeof(wifiPwd));
    mg_http_get_var(&hm->body, "chip", chip, sizeof(chip));
    mg_http_get_var(&hm->body, "detailAddr", detailAddr, sizeof(detailAddr));
    mg_http_get_var(&hm->body, "mqttAccount", mqttAccount, sizeof(mqttAccount));
    mg_http_get_var(&hm->body, "mqttPassword", mqttPassword, sizeof(mqttPassword));

    MLOG_D("提交配置: backendUrl=%s mqttUrl=%s wifiName=%s chip=%s detailAddr=%s\n",
            backendUrl, mqttUrl, wifiName, chip, detailAddr,mqttAccount);

    mg_http_reply(c, 200, "Content-Type: application/json; charset=utf-8\r\n",
                    "{\"ok\":1,\"message\":\"received\"}\n");
    
    //将配置写入文件
    gchar * configpath = getConfigPath();
    MLOG_D("配置文件路径:%s",configpath ? configpath : "(null)");
    if(!configpath) return;
    //将文件配置写入
    GKeyFile * newfile = g_key_file_new();
    GError * gerror = NULL;
    g_key_file_set_string(newfile,"serverAddress","backendUrl",backendUrl);
    g_key_file_set_string(newfile,"mqtt","mqttUrl",mqttUrl);
    g_key_file_set_string(newfile,"mqtt","mqttAccount",mqttAccount);
    g_key_file_set_string(newfile,"mqtt","mqttPassword",mqttPassword);
    g_key_file_set_string(newfile,"wifi","wifiName",wifiName);
    g_key_file_set_string(newfile,"wifi","wifiPwd",wifiPwd);
    g_key_file_set_string(newfile,"Address","chip",chip);
    g_key_file_set_string(newfile,"Address","detailAddr",detailAddr);

    if(!g_key_file_save_to_file(newfile,configpath,&gerror))
    {
        handleError("配置写入文件失败",gerror);
        g_key_file_free(newfile);
        g_free(configpath);
        return;
    }
    g_key_file_free(newfile);

    MLOG_D("配置写入文件成功");
    
    //将配置写入完成的消息投入到消息队列
    int msgid = get_msg_id();
    if(msgid)
    {
        send_data(msgid,CONFIG_DONE,configpath);
        MLOG_D("消息队列写入完成");
    }
    
    g_free(configpath);
}
