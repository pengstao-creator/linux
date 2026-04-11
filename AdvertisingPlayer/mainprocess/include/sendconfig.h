#ifndef SEND_CONFIG_H
#define SEND_CONFIG_H
#include "requestMethod.h"
#include "configinfo.h"
#include "mqttclient.h"
//发送配置请求
void sendConfigRequest(ConfigInfo * info);

//发送心跳请求
void sendHearRequest(MQTTClient * client,ConfigInfo * info);


#endif