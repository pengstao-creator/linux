#include "configinfo.h"
#include "log.h"
void loadConfigInfo(ConfigInfo * info, const char * inipath)
{
    if(info == NULL)
    {
        MLOG_E("info is NULL");
        return;
    }
    if(inipath == NULL)
    {
        MLOG_E("inipath is NULL");
        return;
    }
    clearConfigInfo(info);
    info->_init = 1;
    info->_updateConfig = 1;
    GKeyFile * newfile = g_key_file_new();
    GError * gerror = NULL;
    if(newfile)
    {
        if (!g_key_file_load_from_file(newfile, inipath, G_KEY_FILE_NONE, &gerror))
        {
            info->_init = 0;
            handleError("文件读取失败", gerror);
        }
        else
        {
            info->_backendUrl = g_key_file_get_string(newfile, "serverAddress", "backendUrl", &gerror);
            if (!info->_backendUrl)
            {
                info->_init = 0;
                handleError("读取backendUrl失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_mqttUrl = g_key_file_get_string(newfile, "mqtt", "mqttUrl", &gerror);
            if (!info->_mqttUrl)
            {
                info->_init = 0;
                handleError("读取mqttUrl失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_mqttUsername = g_key_file_get_string(newfile, "mqtt", "mqttUsername", &gerror);
            if (!info->_mqttUsername)
            {
                info->_init = 0;
                handleError("读取mqttUsername失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_mqttPassword = g_key_file_get_string(newfile, "mqtt", "mqttPassword", &gerror);
            if (!info->_mqttPassword)
            {
                info->_init = 0;
                handleError("读取mqttPassword失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_heartbeatTopic = g_key_file_get_string(newfile, "mqtt", "heartbeatTopic", &gerror);
            if (!info->_heartbeatTopic)
            {
                info->_init = 0;
                handleError("读取heartbeatTopic失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_commandTopic = g_key_file_get_string(newfile, "mqtt", "commandTopic", &gerror);
            if (!info->_commandTopic)
            {
                info->_init = 0;
                handleError("读取commandTopic失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_advertTopic = g_key_file_get_string(newfile, "mqtt", "advertTopic", &gerror);
            if (!info->_advertTopic)
            {
                info->_init = 0;
                handleError("读取advertTopic失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_wifiName = g_key_file_get_string(newfile, "wifi", "wifiName", &gerror);
            if (!info->_wifiName)
            {
                info->_init = 0;
                handleError("读取wifiName失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_wifiPwd = g_key_file_get_string(newfile, "wifi", "wifiPwd", &gerror);
            if (!info->_wifiPwd)
            {
                info->_init = 0;
                handleError("读取wifiPwd失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_chip = g_key_file_get_string(newfile, "Address", "chip", &gerror);
            if (!info->_chip)
            {
                info->_init = 0;
                handleError("读取chip失败", gerror);
                g_key_file_free(newfile);
                return;
            }
            info->_detailAddr = g_key_file_get_string(newfile, "Address", "detailAddr", &gerror);
            if (!info->_detailAddr)
            {
                info->_init = 0;
                handleError("读取detailAddr失败", gerror);
                g_key_file_free(newfile);
                return;
            }
        }
    }
    g_key_file_free(newfile);
}

void clearConfigInfo(ConfigInfo * info)
{
    if(info == NULL)
    {
        MLOG_E("info is NULL");
        return;
    }
    if(info->_backendUrl)
    {
        g_free(info->_backendUrl);
    }
  
    if(info->_mqttUrl)
    {
        g_free(info->_mqttUrl);
    }
    if(info->_mqttUsername)
    {
        g_free(info->_mqttUsername);
    }
    if(info->_mqttPassword)
    {
        g_free(info->_mqttPassword);
    }
    if(info->_heartbeatTopic)
    {
        g_free(info->_heartbeatTopic);
    }
    if(info->_commandTopic)
    {
        g_free(info->_commandTopic);
    }
    if(info->_advertTopic)
    {
        g_free(info->_advertTopic);
    }
    if(info->_wifiName)
    {
        g_free(info->_wifiName);
    }
    if(info->_wifiPwd)
    {
        g_free(info->_wifiPwd);
    }
    if(info->_chip)
    {
        g_free(info->_chip);
    }
    if(info->_detailAddr)
    {
        g_free(info->_detailAddr);
    }
    initConfigInfo(info);
}

void initConfigInfo(ConfigInfo * info)
{
    if(info == NULL)
    {
        MLOG_E("info is NULL");
        return;
    }
    info->_init = 0;
    info->_updateConfig = 0;
    info->_backendUrl = NULL;
    info->_mqttUrl = NULL;
    info->_mqttUsername = NULL;
    info->_mqttPassword = NULL;
    info->_heartbeatTopic = NULL;
    info->_commandTopic = NULL;
    info->_advertTopic = NULL;
    info->_wifiName = NULL;
    info->_wifiPwd = NULL;
    info->_chip = NULL;
    info->_detailAddr = NULL;
}


void saveConfigInfo(ConfigInfo * info, const char * inipath)
{
    if(info == NULL || !info->_init)
    {
        MLOG_E("info is NULL or data");
        return;
    }
    GKeyFile * newfile = g_key_file_new();
    GError * gerror = NULL;
    g_key_file_set_string(newfile, "serverAddress", "backendUrl", info->_backendUrl);
    g_key_file_set_string(newfile, "mqtt", "mqttUrl", info->_mqttUrl);
    g_key_file_set_string(newfile, "mqtt", "mqttUsername", info->_mqttUsername);
    g_key_file_set_string(newfile, "mqtt", "mqttPassword", info->_mqttPassword);
    g_key_file_remove_key(newfile, "mqtt", "mqttClientId", NULL);
    g_key_file_set_string(newfile, "mqtt", "heartbeatTopic", info->_heartbeatTopic);
    g_key_file_set_string(newfile, "mqtt", "commandTopic", info->_commandTopic);
    g_key_file_set_string(newfile, "mqtt", "advertTopic", info->_advertTopic);
    g_key_file_set_string(newfile, "wifi", "wifiName", info->_wifiName);
    g_key_file_set_string(newfile, "wifi", "wifiPwd", info->_wifiPwd);
    g_key_file_set_string(newfile, "Address", "chip", info->_chip);
    g_key_file_set_string(newfile, "Address", "detailAddr", info->_detailAddr);
    if(!g_key_file_save_to_file(newfile, inipath, &gerror))
    {
        handleError("保存配置文件失败", gerror);
    }
    g_key_file_free(newfile);
}
void loadNetworkInfo(ConfigInfo * info,struct mg_http_message *hm)
{
    if(info == NULL)
    {
        MLOG_E("info is NULL");
        return;
    }
    initConfigInfo(info);
    info->_init = 1;
    info->_updateConfig = 1;
    info->_backendUrl = g_malloc(SIZE64);
    info->_mqttUrl = g_malloc(SIZE64);
    info->_mqttUsername = g_malloc(SIZE64);
    info->_mqttPassword = g_malloc(SIZE64);
    info->_heartbeatTopic = g_malloc(SIZE64);
    info->_commandTopic = g_malloc(SIZE64);
    info->_advertTopic = g_malloc(SIZE64);
    info->_wifiName = g_malloc(SIZE64);
    info->_wifiPwd = g_malloc(SIZE64);
    info->_chip = g_malloc(SIZE64);
    info->_detailAddr = g_malloc(SIZE64);
    mg_http_get_var(&hm->body, "backendUrl", info->_backendUrl, SIZE64);
    mg_http_get_var(&hm->body, "mqttUrl", info->_mqttUrl, SIZE64);
    mg_http_get_var(&hm->body, "wifiName", info->_wifiName, SIZE64);
    mg_http_get_var(&hm->body, "wifiPwd", info->_wifiPwd, SIZE64);
    mg_http_get_var(&hm->body, "chip", info->_chip, SIZE64);
    mg_http_get_var(&hm->body, "detailAddr", info->_detailAddr, SIZE64);
    mg_http_get_var(&hm->body, "mqttUsername", info->_mqttUsername, SIZE64);
    mg_http_get_var(&hm->body, "mqttPassword", info->_mqttPassword, SIZE64);
    mg_http_get_var(&hm->body, "heartbeatTopic", info->_heartbeatTopic, SIZE64);
    mg_http_get_var(&hm->body, "commandTopic", info->_commandTopic, SIZE64);
    mg_http_get_var(&hm->body, "advertTopic", info->_advertTopic, SIZE64);
}
