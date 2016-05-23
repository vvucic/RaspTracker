
#include <iostream>

#include "Processor.hpp"

Processor::Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue)
: m_inQueue(inQueue), m_outQueue(outqueue)
{
    
}

void Processor::startProcessing() {
    
    cv::Mat frame;
    
    while (true) {
        
        // Grab frame from incoming frames queue
        m_inQueue.popItem(frame);
        
        
        // Process frame here
        
        
        // Push procesed frame to outgoing queue
        m_outQueue.pushItem(frame);
    }
}

void Processor::detectMovingObjects(cv::Mat &frame) {

}