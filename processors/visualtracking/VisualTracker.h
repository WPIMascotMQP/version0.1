/**
 @file VisualTracker.h
 @class VisualTracker
 @brief The VisualTracker class
 @details This VisualTracker class will handle the tracking of a single
 object rect. It is able to return the moving average posiiton and keep
 track of the number of times this object is missing

 @author Jonathan Chang
 @version 0.0.1
 @date 28/1/2020
*/

#ifndef VISUALTRACKER_H
#define VISUALTRACKER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <cmath>

#include "../../kinematics/Position.h"

class VisualTracker {
public:
	VisualTracker();
	~VisualTracker();

	bool belongs(cv::Rect* rect, Position* position);
	void add(cv::Rect rect, Position* position);
	int getMissedCount();

	cv::Rect* getAverage();
	int getMidX(cv::Rect* rect);
	int getMidY(cv::Rect* rect);

	unsigned int missedCount;
	std::vector<cv::Rect*> history;
	std::vector<Position*> positions;
	
};
#endif