#include "MQTTClient.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
//定义mqtt客户端，连接到mqtt服务器

// MQTT客户端句柄
MQTTClient client;
// 连接标志
int connected = 0;

/**
 * 连接到MQTT服务器
 * 0表示成功，非0表示失败
 */
int mqttClient()
{
    int rc;
    const char* server = "mqtt://115.159.78.192:1883";
    const char* clientId = "linux-client";
    // 初始化客户端
    // 参数1: 客户端句柄
    // 参数2: 服务器地址
    // 参数3: 客户端ID
    // 参数4: 持久性类型 (MQTTCLIENT_PERSISTENCE_NONE表示非持久化)
    // 参数5: 持久化文件路径 
    rc = MQTTClient_create(&client, server, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("创建客户端失败: %d\n", rc);
        return rc;
    }
    // 连接选项
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    // 设置连接选项
    conn_opts.username = "pst";
    conn_opts.password = "123456";
    conn_opts.keepAliveInterval = 60;       // 心跳间隔(秒)
    conn_opts.cleansession = 1;             // 清除会话
    // 连接到服务器
    // 参数1: 客户端句柄
    // 参数2: 连接选项
    // 参数3: 回调函数 (NULL表示同步连接)
    rc = MQTTClient_connect(client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("连接服务器失败: %d\n", rc);
        MQTTClient_destroy(&client);
        return rc;
    }
    printf("成功连接到MQTT服务器: %s\n", server);
    connected = 1;
    return MQTTCLIENT_SUCCESS;
}
int publishMessage(const char* topic, const char* payload, int qos, int retained)
{
    if (!connected) {
        printf("未连接到服务器\n");
        return MQTTCLIENT_FAILURE;
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
    int rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("发布消息失败: %d\n", rc);
        return rc;
    }
    // 等待消息发布完成 (最多等待10秒)
    // 参数1: 客户端句柄
    // 参数2: 消息令牌
    // 参数3: 超时时间(毫秒)
    rc = MQTTClient_waitForCompletion(client, token, 10000);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("等待发布完成失败: %d\n", rc);
        return rc;
    }
    printf("成功发布消息到主题 '%s': %s\n", topic, payload);
    return MQTTCLIENT_SUCCESS;
}

int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
    printf("收到消息: 主题='%s', 内容='%.*s'\n", 
           topicName, (int)message->payloadlen, (char*)message->payload);
    // 返回 1 表示由库自动释放 message 和 topicName，用户不再手动调用 free
    return 1;
}
int subscribeMessage(const char* topic, int qos)
{
    if (!connected) {
        printf("未连接到服务器\n");
        return MQTTCLIENT_FAILURE;
    }
    // 设置消息回调函数
    MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);
    // 订阅主题
    // 参数1: 客户端句柄
    // 参数2: 主题名称
    // 参数3: 服务质量
    int rc = MQTTClient_subscribe(client, topic, qos);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("订阅主题失败: %d\n", rc);
        return rc;
    }
    printf("成功订阅主题: %s (QoS=%d)\n", topic, qos);
    return MQTTCLIENT_SUCCESS;
}
/**
 * 断开连接并清理资源
 */
void disconnectClient()
{
    if (connected) {
        // 断开连接
        MQTTClient_disconnect(client, 10000);
        // 销毁客户端
        MQTTClient_destroy(&client);
        printf("已断开与MQTT服务器的连接\n");
        connected = 0;
    }
}

int main()
{
    // 连接到MQTT服务器
    if (mqttClient() != MQTTCLIENT_SUCCESS) {
        return 1;
    }
    // 发布测试消息
    publishMessage("testtopic/2", "Hello MQTT!", 1, 0);
    // 订阅测试主题
    subscribeMessage("testtopic/#", 1);
    // 等待30秒接收消息
    sleep(30);
    // 断开连接
    disconnectClient();
    return 0;
}