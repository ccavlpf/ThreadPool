#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H

#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool{
public:
    ThreadPool(size_t iCnt);
    template<class f, class... Args>
    auto AddTask(f && fn, Args &&... args);
        //-> std::future<typename std::result_of<f(Args...)>::type>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

};

template <class f, class... Args>
inline auto ThreadPool::AddTask(f &&fn, Args &&...args) 
    //-> std::future<typename std::result_of<f(Args...)>::type>
{
    using return_type = typename std::result_of<f(Args...)>::type;

    auto newTask = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<f>(fn), std::forward<Args>(args)...)
    );

    std::future<return_type> future_val = newTask->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
        {
            throw std::runtime_error("~~err");
        }
        
        tasks.emplace([newTask](){(*newTask)();});
    }


    condition.notify_one();

    return future_val;

}


ThreadPool::ThreadPool(size_t iCnt):stop(false)
{
    for (size_t i = 0; i < iCnt; i++)
    {
        workers.emplace_back([this](){
            for (;;)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, 
                        [this]{return !this->stop && !this->tasks.empty();});
                    if (this->stop && this->tasks.empty())
                    {
                        break;
                    }
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();             
            }
            
        });
    }    
}



#endif
