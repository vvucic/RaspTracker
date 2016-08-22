
#include <iostream>
#include <chrono>

#include "Processor.hpp"
#include "CameraHandler.hpp"

WQueue<cv::Mat> rawQueue;
WQueue<cv::Mat> procQueue;
bool capture = true;

double avgFPS = 0.0; // Holds the average FPS
int fps1sec = 0; // Counter for number of frames during previous second
std::chrono::system_clock::time_point start; // Time used when calculating FPS

// Function prototypes
void startCapture(CameraHandler&);
void updateAvgFPS();
std::string getFPSString(void);




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
    
    // Get start time
    start = std::chrono::system_clock::now();
    
    // Start GUI loop
    while(capture) {
		
        updateAvgFPS();
        
        // Grab frame from processed frames queue
		procQueue.popItem(frame);
		
        // Add some text
     /*   cv::putText(frame,
                    getFPSString(),
                    cv::Point(5,20),
                    cv::FONT_HERSHEY_DUPLEX,
                    0.5,
                    cv::Scalar(0,255,0));
        
        cv::putText(frame,
                    "RQueue: " + std::to_string(rawQueue.numItems()),
                    cv::Point(5,40),
                    CV_FONT_HERSHEY_DUPLEX,
                    0.6,
                    cv::Scalar(255,0,0));
        
        cv::putText(frame,
                    "PQueue: " + std::to_string(procQueue.numItems()),
                    cv::Point(5,60),
                    CV_FONT_HERSHEY_DUPLEX,
                    0.6,
                    cv::Scalar(255,255,0));
        */
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

// Calculates the average FPS
void updateAvgFPS()
{
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;
    if(diff.count() > 1.0)
    {
        start = std::chrono::system_clock::now();
        avgFPS=0.3*avgFPS+0.7*fps1sec;
        fps1sec=0;
    }
    fps1sec++;
}

// Returns a string containing the average FPS
std::string getFPSString()
{
    char buffer [20];
    sprintf(buffer, "FPS %4.1f", avgFPS);
    return std::string(buffer);
}

