#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 128


#define CONFIG_DONE 1


typedef struct msg_buffer
{
    long msg_type;
    char msg_text[MSG_SIZE];
}msg_buffer;
int get_msg_id();
void send_data(int msg_id,long msg_type,const char * data);
void recv_data(int msg_id,long msg_type,char * out,size_t out_size);
#endif
