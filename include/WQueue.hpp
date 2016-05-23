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
    
    int getNumItems();
    
private:
    
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condv;
    
    static const int MAX_QUEUE_SIZE = 20;
    
};

#endif /* WQueue_hpp */

#include "WQueue.tpp"
