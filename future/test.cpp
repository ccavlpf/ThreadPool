#include<thread>
#include<future>
#include<chrono>
#include <stdio.h>
#include <iostream>

int test()
{
    for (size_t i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "~~" << std::endl;
    }
    
    return 3;
}

int main()
{
    std::future<int> a = std::async(std::launch::async, test);
    std::chrono::seconds t(5);//std::async用的deferr这里不管几秒都没用
    switch (a.wait_for(t))
    {
    case std::future_status::timeout:
        std::cout << "timeout" << std::endl;
        break;
    case std::future_status::ready:
        std::cout << "ready" << std::endl;
        break;
    case std::future_status::deferred:
        std::cout << "deferred" << std::endl;
        break;    
    default:
        break;
    }

    std::cout << a.get() << std::endl;
    
    return 0;
}