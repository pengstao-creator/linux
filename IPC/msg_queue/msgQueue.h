#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 128

struct msg_buffer
{
    long msg_type;
    char msg_text[MSG_SIZE];
};

int get_msg_id()
{
    key_t key = ftok(".",66);
    if(key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int msg_id = msgget(key,IPC_CREAT | 0666);
    if(msg_id < 0)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return msg_id;
}

void send_data(int msg_id,long msg_type,const char * data)
{
    struct msg_buffer buff;
    buff.msg_type = msg_type;
    memset(buff.msg_text,0,sizeof(buff.msg_text));
    strncpy(buff.msg_text,data,MSG_SIZE - 1);
    int ret = msgsnd(msg_id,&buff,sizeof(buff.msg_text),0);
    if(ret < 0)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

void recv_data(int msg_id,long msg_type,char * out,size_t out_size)
{
    struct msg_buffer buff;
    int ret = msgrcv(msg_id,&buff,sizeof(buff.msg_text),msg_type,0);
    if(ret < 0)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    size_t copy_size = out_size - 1;
    if(copy_size > (size_t)ret)
    {
        copy_size = (size_t)ret;
    }
    memcpy(out,buff.msg_text,copy_size);
    out[copy_size] = '\0';
}
