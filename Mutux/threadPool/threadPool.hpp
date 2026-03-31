#include <iostream>
#include <queue>
#include <pthread.h>
#include <vector>
class threadPool
{
    typedef void*(Task)(void *);
public:
    threadPool(int n)
        :_threads(n)
    {
        for(int i=0;i<n;i++)
        {
            pthread_create(&_threads[i],NULL,threadFunc,this);
        }
        pthread_mutex_init(&_mutex,NULL);
        pthread_cond_init(&_pcond,NULL);
        pthread_cond_init(&_ccond,NULL);
    }
    ~threadPool();
    void push(Task task)
    {
        pthread_mutex_lock(&_mutex);
        _tasks.push(task);
        pthread_mutex_unlock(&_mutex);
        pthread_cond_signal(&_pcond);
    }
private:
    static void * threadFunc(void * arg)
    {
        threadPool * pool = (threadPool *)arg;
        while(true)
        {
            pthread_mutex_lock(&_pool->_mutex);
            while(pool->_tasks.empty())
            {
                pthread_cond_wait(&_pool->_pcond,&_pool->_mutex);
            }
            void * task = pool->_tasks.front();
            pool->_tasks.pop();
            pthread_mutex_unlock(&_pool->_mutex);
            task();
        }
    }

private:
    std::vector<pthread_t> _threads;
    std::queue<void *> _tasks;
    pthread_mutex_t _mutex;
    pthread_cond_t _pcond;
    pthread_cond_t _ccond;
   };
