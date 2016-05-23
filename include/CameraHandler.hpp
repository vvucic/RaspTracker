
#ifndef CameraHandler_hpp
#define CameraHandler_hpp

#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

class CameraHandler {
    
public:
    CameraHandler(int width = 640, int height = 480);
    ~CameraHandler();
    
    bool setResolution(int width, int height);
    bool openCamera(int id = 1);
    void operator>>(cv::Mat &frame);
    
private:
    
    int m_camID;
    int m_width;
    int m_height;
    
    cv::VideoCapture cap;
};

#endif /* CameraHandler_hpp */
