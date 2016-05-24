
#include "Processor.hpp"
#include "GreenCircleDetector.hpp"

Processor::Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue)
: m_inQueue(inQueue), m_outQueue(outqueue)
{
    m_process = true;
}

void Processor::startProcessing() {
    
    cv::Mat frame;
	cv::Mat frame_processed;
	GreenCircleDetector detector;
    while (shouldProcess()) {
        
        // Grab frame from incoming frames queue
        m_inQueue.popItem(frame);
        
		// Do what ever you want with the frame here

		detector.setImage(frame);
		detector.getMarkedImage(frame_processed);
         
        
        // Push processed frame to outgoing queue
        m_outQueue.pushItem(frame_processed);
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