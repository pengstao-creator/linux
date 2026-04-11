#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H
#include "MQTTClient.h"
int createMQTTClient(MQTTClient * client,const char* url,const char * clientid);
int connectMQTTClient(MQTTClient * client,MQTTClient_connectOptions * conn_opts);
void publishMessage(MQTTClient * client, const char * topic, const char * payload,int qos, int retained);
void subscribeMQTTClient(MQTTClient * client, const char * topic, int qos);
void disconnectMQTTClient(MQTTClient * client);
void destroyMQTTClient(MQTTClient * client);

#endif
