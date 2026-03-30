#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
//有名信号量，进行抢票操作

typedef void*(HandlerFunc)(void*);  

#define SEM_NAME "/name"
int num = 10;
int k = 0;
int maxk = 10;
typedef struct threadData
{
    pthread_t tid;
    pthread_mutex_t * lock;
    sem_t * semt;
}threadData;

void * producer(void * tdata)
{
    threadData * _tdata = (threadData*)tdata;
    // sem_t * semt = sem_open(SEM_NAME,0);
    // printf("producer:%p\n",&semt);
    // if(semt == SEM_FAILED)
    // {
    //     perror("sem_open");
    //     exit(EXIT_FAILURE);
    // }

    sem_t * semt = _tdata->semt;
    printf("producer:%p\n",semt);
    while(1)
    {
        sem_post(semt);
        pthread_mutex_lock(_tdata->lock);
        num++;
        if(k > maxk)
        {
            pthread_mutex_unlock(_tdata->lock);
            break;
        }
        k++;
        pthread_mutex_unlock(_tdata->lock);
    }
  
} 

void * consumer(void * tdata)
{
    threadData * _tdata = (threadData*)tdata;
    // sem_t * semt = sem_open(SEM_NAME,0);
    // printf("consumer:%p\n",&semt);
    // if(semt == SEM_FAILED)
    // {
    //     perror("sem_open");
    //     exit(EXIT_FAILURE);
    // }
      sem_t * semt = _tdata->semt;
    printf("consumer:%p\n",semt);
    while(1)
    {
        sem_wait(semt);
        pthread_mutex_lock(_tdata->lock);
        if(num == 0)
        {
            pthread_mutex_unlock(_tdata->lock);
            break;
        }
        num--;
        printf("num:%d\n",num);
       
        pthread_mutex_unlock(_tdata->lock);
    }
}


int main()
{
    pthread_mutex_t lock;
    pthread_mutex_init(&lock,NULL);
    //创建命名信号量
    sem_t * semt = sem_open(SEM_NAME,0666,O_CREAT,num);
    if(semt == SEM_FAILED)
    {
        perror("sem_open");
        //存在则打开
        semt = sem_open(SEM_NAME,0);
        if(semt == SEM_FAILED)
        {
            perror("sem_open");
            // exit(EXIT_FAILURE);
        }
    }
    printf("main:%p\n",semt);
    //创建多个线程,进行生产和消费
    int n = 1;
    threadData ptdatas[n];
    for(int i = 0;i < n;i++)
    {
        ptdatas[i].lock = &lock;
        ptdatas[i].semt = semt;
        pthread_create(&ptdatas[i].tid,NULL,producer,&ptdatas[i]);
    }

    threadData ctdatas[n];
    for(int i = 0;i < n;i++)
    {
        ctdatas[i].lock = &lock;
        pthread_create(&ctdatas[i].tid,NULL,consumer,&ctdatas[i]);
    }

    for(int i = 0;i < n;i++)
    {
        pthread_join(ptdatas[i].tid,NULL);
        pthread_join(ctdatas[i].tid,NULL);
    }
    sem_close(semt);
    sem_unlink(SEM_NAME);
    return 0;
}
