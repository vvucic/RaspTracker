#include "GreenCircleDetector.hpp"

GreenCircleDetector::GreenCircleDetector() {
	image.reset(new cv::Mat);
}

GreenCircleDetector::~GreenCircleDetector() {
	image = nullptr;
}

void GreenCircleDetector::setImage(cv::Mat& input) {
	image.reset(new cv::Mat(input));
}

void GreenCircleDetector::getMarkedImage(cv::Mat& output) {
	cv::Mat image_processed;
	image->copyTo(output);

	// Convert to HSV, extract green color, and do morphological opening operation
	cvtColor(output, image_processed, CV_BGR2HSV);
	GaussianBlur(image_processed, image_processed, Size(9, 9), 2, 2);
	inRange(image_processed, Scalar(30, 150, 10), Scalar(100, 255, 170), image_processed);
	morphologyEx(image_processed, image_processed, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(5, 5)));
	morphologyEx(image_processed, image_processed, MORPH_DILATE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));


	// Extract contours 
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(image_processed, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Draw contours 
	for (int i = 0; i < contours.size(); i++)
	{
		// Circle must be larger then specific area
		if (contourArea(contours[i]) > 150)
		{
			Point2f center;
			float radius;
			minEnclosingCircle(contours[i], center, radius);

			// Minimal enclosing circle should be similar size to area of detected circle
			if ((radius*radius*3.14 - contourArea(contours[i])) / contourArea(contours[i]) < 0.3) {
				circle(output, center, radius, Scalar(0, 255, 0), 2);
			}
		}
	}
}