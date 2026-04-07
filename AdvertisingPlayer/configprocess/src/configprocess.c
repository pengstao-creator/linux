#include <glib-2.0/glib.h>
#include <string.h>
#include "configprocess.h"

void parseConfig(struct mg_connection *c,struct mg_http_message *hm)
{
    //读取配置
    char backendUrl[256] = {0};
    char mqttUrl[256] = {0};
    char wifiName[128] = {0};
    char wifiPwd[128] = {0};
    char chip[64] = {0};
    char detailAddr[256] = {0};
    mg_http_get_var(&hm->body, "backendUrl", backendUrl, sizeof(backendUrl));
    mg_http_get_var(&hm->body, "mqttUrl", mqttUrl, sizeof(mqttUrl));
    mg_http_get_var(&hm->body, "wifiName", wifiName, sizeof(wifiName));
    mg_http_get_var(&hm->body, "wifiPwd", wifiPwd, sizeof(wifiPwd));
    mg_http_get_var(&hm->body, "chip", chip, sizeof(chip));
    mg_http_get_var(&hm->body, "detailAddr", detailAddr, sizeof(detailAddr));
    printf("提交配置: backendUrl=%s mqttUrl=%s wifiName=%s chip=%s detailAddr=%s\n",
            backendUrl, mqttUrl, wifiName, chip, detailAddr);
    mg_http_reply(c, 200, "Content-Type: application/json; charset=utf-8\r\n",
                    "{\"ok\":1,\"message\":\"received\"}\n");
    
    //将配置写入文件


    
}