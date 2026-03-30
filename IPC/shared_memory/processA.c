#include "shareMemory.h"

int main()
{
    int shm_id = get_shm_id();
    struct shm_buffer * shm_ptr = attach_shm(shm_id);
    while(shm_ptr->ready == 0)
    {
        usleep(100000);
    }
    printf("read data from shared memory:%s\n",shm_ptr->data);
    shm_ptr->ready = 0;
    detach_shm(shm_ptr);
    int ret = shmctl(shm_id,IPC_RMID,NULL);
    if(ret < 0)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    return 0;
}
