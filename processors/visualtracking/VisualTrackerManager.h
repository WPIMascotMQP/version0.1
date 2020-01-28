#ifndef VISUALTRACKERMANAGER_H
#define VISUALTRACKERMANAGER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <iostream>
#include <vector>

#include "VisualTracker.h"

class VisualTrackerManager {
public:
	VisualTrackerManager();
	~VisualTrackerManager();

	void addRects(std::vector<cv::Rect> rects);
	std::vector<cv::Rect*>* getRects();

private:
	std::vector<VisualTracker*> trackers;
};
#endif