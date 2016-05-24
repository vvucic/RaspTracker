
#include <iostream>

#include "Processor.hpp"
#include "CameraHandler.hpp"

WQueue<cv::Mat> rawQueue;
WQueue<cv::Mat> procQueue;
bool capture = true;

void startCapture(CameraHandler&);

int main(int argc, const char* argv[]) {
    
    CameraHandler camHandler;
    cv::Mat frame;
    
    // Open camera
    if (!camHandler.openCamera(0)) {
        std::cerr << "Could not open camera\n";
        return -1;
    }
    
    camHandler.setResolution(640,480);
    
    // Start capturing frames in a seperate thread
    std::thread capThread(startCapture, std::ref(camHandler));
    
    // Start processing frames in a seperate thread
    Processor processor(rawQueue, procQueue);
    std::thread procThread(&Processor::startProcessing, &processor);
    
    // Start GUI loop
    while(capture) {
		
        // Grab frame from processed frames queue
		procQueue.popItem(frame);
		
        // Add some text
        cv::putText(frame,
                    "RQueue: " + std::to_string(rawQueue.numItems()),
                    cv::Point(5,20),
                    CV_FONT_HERSHEY_DUPLEX,
                    0.6,
                    cv::Scalar(255,0,0));
        
        cv::putText(frame,
                    "RQueue: " + std::to_string(procQueue.numItems()),
                    cv::Point(5,40),
                    CV_FONT_HERSHEY_DUPLEX,
                    0.6,
                    cv::Scalar(255,0,0));
        
        // Show frame
		cv::imshow("Camera", frame);
		
        // Handle possible key event
		switch(cv::waitKey(10)) {
			case 27:
				capture = false;
				break;
			default:
				break;
		}
	}
    
    // Stop process
    processor.stopProcessing();
	
    // Join threads
	capThread.join();
    procThread.join();
    
    return 0;
}

void startCapture(CameraHandler &ch) {
	cv::Mat capFrame;
	while(capture) {
		ch >> capFrame;
		rawQueue.pushItem(capFrame);
	}
}
