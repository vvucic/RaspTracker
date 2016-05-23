
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

#include "WQueue.hpp"
#include "CameraHandler.hpp"

WQueue<cv::Mat> rawQueue;
bool capture = true;

void startCapture(CameraHandler&);

int main(int argc, const char* argv[]) {
    
    CameraHandler camHandler;
    cv::Mat frame, cannyFrame;
    
    if (!camHandler.openCamera(0)) {
        std::cerr << "Could not open camera\n";
        return -1;
    }
    
    camHandler.setResolution(640,480);
    
    std::thread capThread(startCapture, std::ref(camHandler));
    
    while(capture) {
		
		rawQueue.popItem(frame);
		
		cv::Canny(frame, cannyFrame, 100, 200);
		
        cv::putText(cannyFrame,
                    "RQueue: " + std::to_string(rawQueue.numItems()),
                    cv::Point(5,20),
                    CV_FONT_HERSHEY_DUPLEX,
                    0.7,
                    cv::Scalar(255,0,0));
        
		cv::imshow("Camera", cannyFrame);
		
		switch(cv::waitKey(10)) {
			case 27:
				capture = false;
				break;
			default:
				break;
		}
	}
	
	capThread.join();
    
    return 0;
}

void startCapture(CameraHandler &ch) {
	cv::Mat capFrame;
	while(capture) {
		ch >> capFrame;
		rawQueue.pushItem(capFrame);
	}
}
