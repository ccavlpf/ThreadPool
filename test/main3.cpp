#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
 
// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) 
{
        std::cout << "f " << std::this_thread::get_id() << std::endl;

    return std::pow(x,y); 
}
 
void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) 
    {
        std::cout << "lamda " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return std::pow(a, b); 
    });

    std::future<int> result = task.get_future();
    std::cout << "future" << std::endl;

    task(2, 9);
 
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
 
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
    std::packaged_task<int(int,int)> task1(f);
    std::future<int> result = task1.get_future();
 
    std::thread task_td(std::move(task1), 2, 10);
    task_td.join();
 
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main()
{
        std::cout << "main " << std::this_thread::get_id() << std::endl;
    task_lambda();
    // task_bind();
    //task_thread();

    auto fff = std::bind(f, 2, 11);
    
}