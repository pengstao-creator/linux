#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 128

struct shm_buffer
{
    int ready;
    char data[SHM_SIZE];
};

int get_shm_id()
{
    key_t key = ftok(".",77);
    if(key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shm_id = shmget(key,sizeof(struct shm_buffer),IPC_CREAT | 0666);
    if(shm_id < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    return shm_id;
}

struct shm_buffer * attach_shm(int shm_id)
{
    void * addr = shmat(shm_id,NULL,0);
    if(addr == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    return (struct shm_buffer *)addr;
}

void detach_shm(void * addr)
{
    int ret = shmdt(addr);
    if(ret < 0)
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
}
