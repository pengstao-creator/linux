#include "threadPool.hpp"

void * task(void * arg)
{
    std::cout<<"task"<<std::endl;
}



int main()
{
    threadPool pool(4);
    pool.push(task);
    return 0;
}