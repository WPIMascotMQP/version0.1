/**
 @file VisualTrackerManager.h
 @class VisualTrackerManager
 @brief The VisualTrackerManager class
 @details This VisualTrackerManager class will handle the tracking of a single
 type of object using VisualTrackers. It will delete trackers that can no longer see
 their object and create trackers for objects that do not belong to any tracker

 @author Jonathan Chang
 @version 0.0.1
 @date 28/1/2020
*/

#ifndef VISUALTRACKERMANAGER_H
#define VISUALTRACKERMANAGER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <iostream>
#include <vector>

#include "../../kinematics/Position.h"
#include "VisualTracker.h"

class VisualTrackerManager {
public:
	VisualTrackerManager();
	~VisualTrackerManager();

	void addRects(std::vector<cv::Rect> rects, Position* position);
	std::vector<cv::Rect*>* getRects();

private:
	std::vector<VisualTracker*> trackers;
};
#endif