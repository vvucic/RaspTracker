//
//  WQueue.hpp
//  CameraMulti
//
//  Created by Toni Axelsson on 2016-05-20.
//  Copyright © 2016 Toni. All rights reserved.
//

#ifndef WQueue_hpp
#define WQueue_hpp

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class WQueue {
    
public:
    WQueue();
    ~WQueue();
    
    void pushItem(T item);
    void popItem(T& item);
    
    int numItems();
    
private:
    
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condv;
    
    static const int MAX_QUEUE_SIZE = 20;
    
};

#endif /* WQueue_hpp */

template<typename T>
WQueue<T>::WQueue() {
    
}

template<typename T>
WQueue<T>::~WQueue() {
    
}

template<typename T>
void WQueue<T>::pushItem(T item) {
    
    std::unique_lock<std::mutex> mlock(m_mutex);
    m_queue.push(item);
    mlock.unlock();
    m_condv.notify_one();
    
}

template<typename T>
void WQueue<T>::popItem(T& item) {
    std::unique_lock<std::mutex> mlock(m_mutex);
    
    while (m_queue.empty()) {
        m_condv.wait(mlock);
    }
    
    item = m_queue.front();
    m_queue.pop();
    mlock.unlock();
}

template<typename T>
int WQueue<T>::numItems() {
    
    std::unique_lock<std::mutex> lk(m_mutex);
    int numItems = m_queue.size();
    lk.unlock();
    return numItems;
}

