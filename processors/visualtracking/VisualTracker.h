#ifndef VISUALTRACKER_H
#define VISUALTRACKER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <cmath>

class VisualTracker {
public:
	VisualTracker();
	~VisualTracker();

	bool belongs(cv::Rect* rect);
	void add(cv::Rect rect);
	int getMissedCount();

	cv::Rect* getAverage();
	int getMidX(cv::Rect* rect);
	int getMidY(cv::Rect* rect);

	unsigned int missedCount;
	std::vector<cv::Rect*> history;
	
};
#endif