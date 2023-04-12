#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <functional>

std::condition_variable c;
std::thread t[3];
std::mutex m;
std::unique_lock<std::mutex> u(m);



bool bReady = false;

int iTotal = 0;


void func(){
    iTotal ++;
    std::cout << "thread id "<< std::this_thread::get_id() << " total: " << iTotal << std::endl;
}

std::queue<std::function<void()>> tasks;

void thread_func()
{
    for (;;)
    {
        c.wait(u, [](){return !tasks.empty();}); 
        
        std::function<void()> task= std::move(tasks.front());
        tasks.pop();
        task();
    }  
}
  


int main()
{
    for (size_t i = 0; i < 3; i++)
    {
        t[i] = std::thread(thread_func);
    }
    
    for (size_t i = 0; i < 10000; i++)
    {        
        {
            std::unique_lock<std::mutex> lock(m);
            tasks.emplace(func);        
        }                
        c.notify_one();
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }      

    for (size_t i = 0; i < 3; i++)
    {
        t[i].join();
    }
}