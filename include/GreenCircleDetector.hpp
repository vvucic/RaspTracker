//  Created by Vladimir Vucic

#ifndef GreenCircleDetector_hpp
#define GreenCircleDetector_hpp

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <memory>
using namespace cv;
using namespace std;

class GreenCircleDetector {
public:
	GreenCircleDetector();
	~GreenCircleDetector();
	
	void setImage(cv::Mat& input);
	void getMarkedImage(cv::Mat& marked);

private:
	std::unique_ptr<cv::Mat> image;

};


#endif