
#include <iostream>             // std::cout
#include <thread>               // std::chrono::milliseconds
#include <unistd.h>
using namespace std;

void f1(int n)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "thread " << n << " running" << endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }    
}

void f2(int & n)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "thread 2 running" << endl;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        n ++;
    }    
}

int main()
{
    thread t1(f1, 1);
    int i = 3;
    thread t2(f2, std::ref(i));
    
    cout << "t2 joinable ? " << t2.joinable() << "1111" << endl;
    thread t4(std::move(t2));

// (1). move 赋值操作，如果当前对象不可 joinable，需要传递一个右值引用(rhs)给 move 赋值操作；如果当前对象可被 joinable，则 terminate() 报错。
// (2). 拷贝赋值操作被禁用，thread 对象不可被拷贝。

    t1.join();
    t4.join();

    std::cout << "final i value " << i << endl;
    
    //std::chrono::seconds(2)
    return 0;
}
