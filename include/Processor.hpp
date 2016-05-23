

#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <opencv2/core/core.hpp>

#include "WQueue.hpp"

class Processor {
    
public:
    Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue);
    
    void startProcessing();
    
private:
    
    WQueue<cv::Mat> &m_inQueue;
    WQueue<cv::Mat> &m_outQueue;
    
};

#endif