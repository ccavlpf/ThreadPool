#include <future>
#include <thread>
#include <iostream>
#include <chrono>

void func(std::promise<int> & p, std::promise<int> & p1)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    p.set_value(44);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    p1.set_value(55);
}

int main(){
    std::promise<int> myPromise;
    std::promise<int> myPromise1;
    std::future<int> myFuture = myPromise.get_future();
    std::future<int> myFuture1 = myPromise1.get_future();

    //std::thread t(func, std::ref(myPromise), std::ref(myPromise1));
    std::thread t([&](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        myPromise.set_value(44);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    
        myPromise1.set_value(55);
    });

    std::cout << "~ " <<  myFuture1.get() << std::endl;
    std::cout << "~ " <<  myFuture.get() << std::endl;
    t.join();
    //std::this_thread::sleep_for(std::chrono::seconds(3)); core
    //t.detach()
    return 0;
}
