// #include <thread>
// #include <mutex>
// #include <iostream>
// #include <chrono>
// #include <future>
// using namespace std;

// int iTotal = 0;

// mutex m;
// timed_mutex tm;
// recursive_mutex rm;


// void func(int iID){
//     for (int i = 0; i < 10000; i++)
//     {   
//         //1
//         // m.lock();
//         // iTotal ++;    
//         // m.unlock();

//         //2
//         // if (m.try_lock())
//         // {
//         //     iTotal ++;
//         //     m.unlock();            
//         // }
//         // else
//         // {
//         //     i --;
//         // }

//         // 3
//         // if (tm.try_lock_for(chrono::duration<int,milli>(1)))
//         // {
//         //     iTotal ++;
//         //     tm.unlock();
//         // }
//         // else
//         // {
//         //     i --;
//         // }

//         lock_guard<mutex> lm(m);
//         iTotal ++;
//     }
// }
// std::mutex foo,bar;

// void task_a () {
//   std::lock (foo,bar);         // simultaneous lock (prevents deadlock)
//   std::unique_lock<std::mutex> lck1 (foo,std::adopt_lock);
//   std::unique_lock<std::mutex> lck2 (bar,std::adopt_lock);
//   std::cout << "task a\n";
//   // (unlocked automatically on destruction of lck1 and lck2)
// }

// void task_b () {
//   // foo.lock(); bar.lock(); // replaced by:
//   std::unique_lock<std::mutex> lck1, lck2;
//   lck1 = std::unique_lock<std::mutex>(bar,std::defer_lock);
//   lck2 = std::unique_lock<std::mutex>(foo,std::defer_lock);
//   std::lock (lck1,lck2);       // simultaneous lock (prevents deadlock)
//   std::cout << "task b\n";
//   // (unlocked automatically on destruction of lck1 and lck2)
// }
// int main()
// {
//     thread t[10];;
    
//     for (size_t i = 0; i < 10; i++)
//     {   
//         t[i] = thread(func, i);
//     }

//     for (size_t i = 0; i < 10; i++)
//     {
//         t[i].join();
//     }
    
//     cout << iTotal << endl;


//   std::thread th1 (task_a);
//   std::thread th2 (task_b);

//   th1.join();
//   th2.join();


//     return 0;
// }


#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

std::promise<int> prom;

void print_global_promise (int ID) {
    for (size_t i = 0; i < 5; i++)
    {
    std::future<int> fut = prom.get_future();
    int x = fut.get();
    std::cout << ID << std::endl;
    std::cout << "value: " << x << '\n';
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        /* code */
    }
    
}

int main ()
{
    std::thread th1(print_global_promise, 1);
    prom.set_value(10);
    th1.join();

    prom = std::promise<int>();    // prom 被move赋值为一个新的 promise 对象.

    std::thread th2 (print_global_promise,2);
    prom.set_value (20);
    th2.join();

  return 0;
}