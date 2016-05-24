
#include "Processor.hpp"

Processor::Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue)
: m_inQueue(inQueue), m_outQueue(outqueue)
{
    m_process = true;
}

void Processor::startProcessing() {
    
    cv::Mat frame;
    while (shouldProcess()) {
        
        // Grab frame from incoming frames queue
        m_inQueue.popItem(frame);
        
        
        // Do what ever you want with the frame here
        
        
        // Push processed frame to outgoing queue
        m_outQueue.pushItem(frame);
    }
}

void Processor::detectMovingObjects(cv::Mat &frame) {

}

bool Processor::shouldProcess() {
    bool res;
    std::unique_lock<std::mutex> mlock(m_mutex);
    res = m_process ? true : false;
    mlock.unlock();
    return res;
}

void Processor::stopProcessing() {
    std::unique_lock<std::mutex> mlock(m_mutex);
    m_process = false;
    mlock.unlock();
}