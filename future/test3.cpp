#include <future>
#include <thread>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T> int add(T beg, T end){
    std::cout << "thread id " << std::this_thread::get_id() << std::endl;
    int len = end - beg;
    if (len < 100)
    {
        return std::accumulate(beg, end, 0);
    }
    
    T mid = beg + len/2;
    std::future<int> v1 = std::async(std::launch::async, add<T>, beg, mid);
    int v2 = add(mid, end);
    return v2 + v1.get();
}


int main()
{
    std::vector<int> vec(10000, 1);
    std::cout << "start" << std::endl;
    int iNum = add(vec.begin(), vec.end());

    std::cout << "end " << iNum << std::endl;
    return 0;    
}