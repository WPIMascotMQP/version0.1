/**
 @file VisualProcessor.h
 @class VisualProcessor
 @brief The VisualProcessor class
 @details This VisualProcessor class will handle the processing of visual
 data using OpenCV and be able to identify human hands, faces, and bodies

 @author Jonathan Chang
 @version 0.0.1
 @date 08/1/2020
*/

#ifndef VISUALPROCESSOR_H
#define VISUALPROCESSOR_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class VisualProcessor{
public:
	VisualProcessor(int camera_device);
	VisualProcessor() : VisualProcessor(0){};
	~VisualProcessor();

	void startThread();
	void killThread();
	void processSnapshot();

	void deepCopyRect(std::vector<cv::Rect*> global, std::vector<cv::Rect> local);

protected:
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	cv::VideoCapture capture;
	cv::Mat frame;

	std::mutex kill_lock;
	bool kill;

	std::thread vpthread;
};
#endif
