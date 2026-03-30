#include "msgQueue.h"

int main()
{
    int msg_id = get_msg_id();
    send_data(msg_id,1,"我是消息队列发送进程");
    return 0;
}
