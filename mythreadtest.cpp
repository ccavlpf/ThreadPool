#include "MyThreadPool.h"
#include <iostream>

int iTotal = 0;

int add(){
    iTotal ++;
    std::cout << "id " << std::this_thread::get_id() << "val : " << iTotal << std::endl;
    return 0;
}
int main(){
    ThreadPool pool(3);
    for (size_t i = 0; i < 10000; i++)
    {
        pool.AddTask(add);
        std::this_thread::sleep_for(std::chrono::microseconds(10));

    }
    
    std::cout << "total :" << iTotal << std::endl;

    return 0;
}






