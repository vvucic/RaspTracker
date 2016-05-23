
#include "CameraHandler.hpp"


CameraHandler::CameraHandler(int width, int height)
: m_width(width), m_height(height)
{
    
}

CameraHandler::~CameraHandler() {
    
}

bool CameraHandler::setResolution(int width, int height) {
    
    bool res = true;
    
    if (!cap.set(cv::CAP_PROP_FRAME_WIDTH, width)) res = false;
    if (!cap.set(cv::CAP_PROP_FRAME_HEIGHT, height)) res = false;
    
    if (res) {
        m_height = height;
        m_width = width;
    }
    
    return res;
}

bool CameraHandler::openCamera(int id) {
    return cap.open(id) ? true : false;
}

void CameraHandler::operator>>(cv::Mat &frame) {
    cap >> frame;
}