
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
int WQueue<T>::getNumItems() {
    
    std::unique_lock<std::mutex> lk(m_mutex);
    int numItems = m_queue.size();
    lk.unlock();
    return numItems;
}
