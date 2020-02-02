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

#include <tuple>

#include "MotorProcessor.h"
#include "SensorProcessor.h"
#include "visualtracking/VisualTrackerManager.h"

class VisualProcessor : public SensorProcessor {
public:
	VisualProcessor(int camera_device);
	VisualProcessor() : VisualProcessor(0){};
	~VisualProcessor();

	void startThread();
	void killThread();
	void process();
	void display(std::vector<cv::Rect*>* objects, cv::Scalar color, cv::Mat frame);
	void deleteVector(std::vector<cv::Rect*>* objects);

	std::vector<cv::Rect*>* getFaceRects();
	std::vector<cv::Rect*>* getBodyRects();

	void changePhase();
	std::string getMatType(cv::Mat mat);
	std::string getMatDepth(cv::Mat mat);
protected:
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier body_cascade;

	cv::VideoCapture capture;
	cv::Mat frame;

	double num_loops;
	double total_loop_time;
private:
	unsigned int currentPhase;
	cv::CascadeClassifier* currentClassifier;
	VisualTrackerManager* currentManager;
	std::tuple<cv::CascadeClassifier*, VisualTrackerManager*> phases[2];
};

namespace processor {
	extern VisualProcessor vp;
}
#endif
