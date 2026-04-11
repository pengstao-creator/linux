#ifndef CONFIG_INFO
#define CONFIG_INFO
#include <glib-2.0/glib.h>
#include "mongoose.h"
#include "data.h"
#include "tool.h"
typedef struct ConfigInfo
{
    int _init;
    int _updateConfig;//标准是否更改配置
    gchar * _backendUrl;
    gchar * _mqttUrl;
    gchar * _mqttUsername;
    gchar * _mqttPassword;
    gchar * _heartbeatTopic;
    gchar * _commandTopic;
    gchar * _advertTopic;
    gchar * _wifiName;
    gchar * _wifiPwd;
    gchar * _chip;
    gchar * _detailAddr;
}ConfigInfo;
void loadConfigInfo(ConfigInfo * info, const char * inipath);
void saveConfigInfo(ConfigInfo * info, const char * inipath);
void loadNetworkInfo(ConfigInfo * info,struct mg_http_message *hm);
void initConfigInfo(ConfigInfo * info);
void clearConfigInfo(ConfigInfo * info);


#endif
