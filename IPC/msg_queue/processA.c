#include "msgQueue.h"

int main()
{
    int msg_id = get_msg_id();
    char str[MSG_SIZE];
    recv_data(msg_id,1,str,sizeof(str));
    printf("read data from message queue:%s\n",str);
    int ret = msgctl(msg_id,IPC_RMID,NULL);
    if(ret < 0)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    return 0;
}
