#include "msgQueue.h"
#include "log.h"
#include <fcntl.h>
#include <unistd.h>

#define MSGQ_KEY_PATH "/tmp/advertising_player_msgq.key"
int get_msg_id()
{
    int fd = open(MSGQ_KEY_PATH, O_CREAT | O_RDWR, 0666);
    if(fd >= 0) close(fd);
    key_t key = ftok(MSGQ_KEY_PATH,66);
    if(key == -1)
    {
        MLOG_W("获取key失败 errno=%d", errno);
        return -1;
    }

    int msg_id = msgget(key,IPC_CREAT | 0666);
    if(msg_id < 0)
    {
        MLOG_W("获取信道id失败 errno=%d", errno);
        return -1;
    }
    MLOG_D("msg_id=%d key=%d", msg_id, key);
    return msg_id;
}

void send_data(int msg_id,long msg_type,const char * data)
{
    msg_buffer buff;
    buff.msg_type = msg_type;
    memset(buff.msg_text,0,sizeof(buff.msg_text));
    strncpy(buff.msg_text,data,MSG_SIZE - 1);
    int ret = msgsnd(msg_id,&buff,sizeof(buff.msg_text),0);
    if(ret < 0)
    {
        MLOG_W("向管道投放消息失败 errno=%d msg_type=%ld", errno, msg_type);
        return;
    }
}

void recv_data(int msg_id,long msg_type,char * out,size_t out_size)
{
    msg_buffer buff;
    int ret = msgrcv(msg_id,&buff,sizeof(buff.msg_text),msg_type,0);
    if(ret < 0)
    {
        MLOG_W("向管道获取消息失败 errno=%d msg_type=%ld", errno, msg_type);
        return;
    }

    size_t copy_size = out_size - 1;
    if(copy_size > (size_t)ret)
    {
        copy_size = (size_t)ret;
    }
    memcpy(out,buff.msg_text,copy_size);
    out[copy_size] = '\0';
}
