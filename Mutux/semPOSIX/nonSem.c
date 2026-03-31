#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
//有名信号量，进行抢票操作
typedef void*(HandlerFunc)(void*);  

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
    sem_t * semt = _tdata->semt;    
    while(1)
    {
        sem_post(semt);
        pthread_mutex_lock(_tdata->lock);
        if(k >= maxk)
        {
            pthread_mutex_unlock(_tdata->lock);
            break;
        }
        num++;
        k++;
       
        pthread_mutex_unlock(_tdata->lock);
    }
    return NULL;
}
void * consumer(void * tdata)
{
    threadData * _tdata = (threadData*)tdata;
    sem_t * semt = _tdata->semt;    
    while(1)
    {
        sem_wait(semt);
        pthread_mutex_lock(_tdata->lock);
        if(num == 0)
        {
            pthread_mutex_unlock(_tdata->lock);
            break;
        }    
        if(num > 0)
        {
            num--;
            printf("num:%d\n",num);
        }
        pthread_mutex_unlock(_tdata->lock);
    }
    return NULL;
}
int main()
{
    pthread_mutex_t lock;
    pthread_mutex_init(&lock,NULL);
    //创建无名信号量，初始值为0
    sem_t semt;
    sem_init(&semt,0,num);

    int n = 5;
    threadData ptdatas[n];
    for(int i = 0;i < n;i++)
    {
        ptdatas[i].lock = &lock;
        ptdatas[i].semt = &semt;
        pthread_create(&ptdatas[i].tid,NULL,producer,&ptdatas[i]);
    }

    threadData ctdatas[n];
    for(int i = 0;i < n;i++)
    {
        ctdatas[i].lock = &lock;
        ctdatas[i].semt = &semt;
        pthread_create(&ctdatas[i].tid,NULL,consumer,&ctdatas[i]);
    }

    //等待生产者完成
    for(int i = 0;i < n;i++)
    {
        pthread_join(ptdatas[i].tid,NULL);
    }
    //等待消费者完成
    for(int i = 0;i < n;i++)
    {
        pthread_join(ctdatas[i].tid,NULL);
    }
    
    sem_close(&semt);
    return 0;
}
