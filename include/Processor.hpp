

#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "WQueue.hpp"

class Processor {
    
public:
    Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue);
    
    void startProcessing();
    
private:
    
    void detectMovingObjects(cv::Mat &frame);
    
    WQueue<cv::Mat> &m_inQueue;
    WQueue<cv::Mat> &m_outQueue;
    
    cv::Mat detectFrame;
    std::vector<std::vector<cv::Point> > contours;
    
};

#endif /* Processor_hpp */