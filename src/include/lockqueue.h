#pragma once
#include <queue>
#include <thread>
#include <mutex> //线程安全：互斥锁 pthread_mutex_t
#include <condition_variable> //线程间的通信 pthread_condition_t

// 异步写日志的日志队列模板(可以用kafka消息队列中间件改进)
// 注：写模板类不可以将头文件和源文件分开写
template<typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue 
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);//lock_guard自动实现加锁和释放锁：在lock_guard对象构造的时候获得锁，对象析构的时候释放锁
        m_queue.push(data);
        m_condvariable.notify_one();//只通知一个线程，因为只用一个线程在不停地往日志文件写日志
    }

    // 一个线程读日志queue，写日志文件
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);//若得不到锁则线程阻塞在该行
        while (m_queue.empty())
        {
            // 日志队列为空，线程释放锁，并进入wait状态
            m_condvariable.wait(lock);
        }

        T data = m_queue.front();
        m_queue.pop();
        return data;
    }//出了函数作用域后，锁自动释放
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;//消息入队和出队用的同一把锁,用于控制同一个进程中的不同线程的互斥
    std::condition_variable m_condvariable;
};