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
    pthread_rwlock_t * lock;
}threadData;
void * producer(void * tdata)
{
    threadData * _tdata = (threadData*)tdata;
    pthread_rwlock_t * lock = _tdata->lock;    
    while(1)
    {
        pthread_rwlock_wrlock(_tdata->lock);
        if(k >= maxk)
        {
            pthread_rwlock_unlock(_tdata->lock);
            break;
        }
        num++;
        k++;
       
        pthread_rwlock_unlock(_tdata->lock);
    }
    return NULL;
}
void * consumer(void * tdata)
{
    threadData * _tdata = (threadData*)tdata;
    pthread_rwlock_t * lock = _tdata->lock;    
    while(1)
    {
        pthread_rwlock_rdlock(_tdata->lock);
        if(num == 0)
        {
            pthread_rwlock_unlock(_tdata->lock);
            break;
        }    
        if(num > 0)
        {
            num--;
            printf("num:%d\n",num);
        }
        pthread_rwlock_unlock(_tdata->lock);
    }
    return NULL;
}
int main()
{
    pthread_rwlock_t lock;
    pthread_rwlock_init(&lock,NULL);
    int n = 5;
    threadData ptdatas[n];
    for(int i = 0;i < n;i++)
    {
        ptdatas[i].lock = &lock;
        pthread_create(&ptdatas[i].tid,NULL,producer,&ptdatas[i]);
    }

    threadData ctdatas[n];
    for(int i = 0;i < n;i++)
    {
        ctdatas[i].lock = &lock;
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
    pthread_rwlock_destroy(&lock);
    
    return 0;
}
