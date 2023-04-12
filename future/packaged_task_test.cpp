#include <future>
#include <iostream>

template <class T>
T Func(T & a){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return a;
}



int main(){
    std::packaged_task<int(int &)> task(Func<int &>);
    std::future<int> f = task.get_future();

    int i = 1;
    std::thread t(std::move(task), std::ref(i));
    std::cout << f.get() << std::endl;
    t.join();

    return 0;
}