#include <future>
#include <iostream>

template <class T>
T Func(T a){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << a << std::endl;
    return a;
}



int main(){
    std::packaged_task<int(int)> task(Func<int>);
    std::future<int> f = task.get_future();

    std::thread t(std::move(task), 1);//thread(_Callable&& __f, _Args&&... __args)//std::thread t1(task); //err
    
    std::cout << f.get() << std::endl;
    t.join();

    return 0;
}