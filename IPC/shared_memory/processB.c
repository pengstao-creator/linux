#include "shareMemory.h"

int main()
{
    int shm_id = get_shm_id();
    struct shm_buffer * shm_ptr = attach_shm(shm_id);
    shm_ptr->ready = 0;
    memset(shm_ptr->data,0,sizeof(shm_ptr->data));
    strncpy(shm_ptr->data,"我是共享内存写进程",SHM_SIZE - 1);
    shm_ptr->ready = 1;
    detach_shm(shm_ptr);
    return 0;
}
