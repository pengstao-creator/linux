#include "mqttclient.h"
#include "log.h"
#include <string.h>
int createMQTTClient(MQTTClient * client,const char* url,const char * clientid)
{
    if(client == NULL)
    {
        MLOG_E("client is NULL");
        return 0;
    }
    if(*client) return 1;
    int rc = MQTTClient_create(client,url,clientid,MQTTCLIENT_PERSISTENCE_NONE,NULL);
    if(rc != MQTTCLIENT_SUCCESS)
    {
        MLOG_W("创建客户端失败,rc码:%d,错误信息：%s",rc,MQTTClient_strerror(rc));
        return 0;
    }
    return 1;
}
int connectMQTTClient(MQTTClient * client,MQTTClient_connectOptions * conn_opts)
{
    if(!client || !(*client))
    {
        MLOG_E("client is NULL");
        return 0;
    }
    int rc = MQTTClient_connect(*client,conn_opts);
    if(rc != MQTTCLIENT_SUCCESS)
    {
        MLOG_W("mqtt服务器连接失败,rc码:%d,错误信息：%s",rc,MQTTClient_strerror(rc));
        return 0;
    }
    MLOG_I("mqtt服务器连接成功");
    return 1;
}
void publishMessage(MQTTClient * client, const char * topic, const char * payload,int qos, int retained)
{
    if(!client || !(*client))
    {
        MLOG_D("未连接服务器");
        return;
    }
    // 消息结构体
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    // 设置消息内容
    pubmsg.payload = (void*)payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = qos;
    pubmsg.retained = retained; 
    // 消息令牌
    MQTTClient_deliveryToken token;
    // 发布消息
    // 参数1: 客户端句柄
    // 参数2: 主题名称
    // 参数3: 消息结构体
    // 参数4: 消息令牌
    int rc = MQTTClient_publishMessage(*client, topic, &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        MLOG_W("发送消息失败,rc码:%d,错误信息：%s",rc,MQTTClient_strerror(rc));
        return;
    }
    MLOG_D("成功发布消息到主题 '%s': %s\n", topic, payload);
}

int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
    MLOG_D("收到消息: 主题='%s', 内容='%.*s'\n", 
           topicName, (int)message->payloadlen, (char*)message->payload);
    // 返回 1 表示由库自动释放 message 和 topicName，用户不再手动调用 free
    return 1;
}
void subscribeMQTTClient(MQTTClient * client, const char * topic, int qos)
{
    if(!client || !(*client))
    {
        MLOG_D("未连接服务器");
        return;
    }
    // 设置消息回调函数
    MQTTClient_setCallbacks(*client, NULL, NULL, messageArrived, NULL);
    // 订阅主题
    // 参数1: 客户端句柄
    // 参数2: 主题名称
    // 参数3: 服务质量
    int rc = MQTTClient_subscribe(*client, topic, qos);
    if (rc != MQTTCLIENT_SUCCESS) {
        MLOG_W("订阅主题失败,rc码:%d,错误信息：%s",rc,MQTTClient_strerror(rc));
        return;
    }
    MLOG_D("成功订阅主题: %s (QoS=%d)\n", topic, qos);
}
void disconnectMQTTClient(MQTTClient * client)
{
    if(!client || !(*client))
    {
        MLOG_D("client is NULL");
        return;
    }
    MQTTClient_disconnect(*client, 10000);
    MLOG_D("已断开与MQTT服务器的连接");
}
void destroyMQTTClient(MQTTClient * client)
{
    if(!client || !(*client))
    {
        MLOG_D("client is NULL");
        return;
    }
    MQTTClient_destroy(client);
    MLOG_D("已销毁MQTT客户端");
}
