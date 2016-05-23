
#include "Processor.hpp"

Processor::Processor(WQueue<cv::Mat> &inQueue, WQueue<cv::Mat> &outqueue)
: m_inQueue(inQueue), m_outQueue(outqueue)
{
    
}
