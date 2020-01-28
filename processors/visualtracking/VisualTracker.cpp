#include "VisualTracker.h"

namespace trackers {
	int center_error = 50;
	int size_error = 100;

	unsigned int history_length = 5;
}

VisualTracker::VisualTracker() {
	missedCount = 0;
}

VisualTracker::~VisualTracker() {
	std::vector<cv::Rect*>::iterator itr = history.begin();
	if(itr < history.end()) {
	    cv::Rect_<int>* rec = *itr;
		delete(rec);
		itr = history.erase(itr);
	}
}

bool VisualTracker::belongs(cv::Rect* rect) {
	cv::Rect* average = getAverage();
	int average_x = getMidX(average);
	int average_y = getMidY(average);

	int rect_x = getMidX(rect);
	int rect_y = getMidY(rect);

	if(std::abs(average_x - rect_x) >= trackers::center_error) {
		return false;
	}
	if(std::abs(average_y - rect_y) >= trackers::center_error) {
		return false;
	}
	if(std::abs(average->width - rect->width) >= trackers::size_error) {
		return false;
	}
	if(std::abs(average->height - rect->height) >= trackers::size_error) {
		return false;
	}
	return true;
}

void VisualTracker::add(cv::Rect rect) {
	cv::Rect_<int>* new_rect = new cv::Rect(rect.x, rect.y, rect.width, rect.height);
	history.push_back(new_rect);
	if(history.size() > trackers::history_length) {
		std::vector<cv::Rect*>::iterator itr = history.begin();
        cv::Rect_<int>* rec = *itr;
        delete(rec);
        history.erase(itr);
	}
}

cv::Rect* VisualTracker::getAverage() {
	int sum_x = 0;
	int sum_y = 0;

	int sum_width = 0;
	int sum_height = 0;

	std::vector<cv::Rect*>::iterator itr = history.begin();
	while(itr < history.end()) {
		cv::Rect_<int>* rec = *itr;
		sum_x += rec->x;
		sum_y += rec->y;
		sum_width += rec->width;
		sum_height += rec->height;
		itr++;
	}

	cv::Rect* rect = new cv::Rect((int) sum_x/history.size() + 0.5,
								(int) sum_y/history.size() + 0.5,
								(int) sum_width/history.size() + 0.5,
								(int) sum_height/history.size() + 0.5);
	return rect;
}

int VisualTracker::getMidX(cv::Rect* rect) {
	return (int) rect->x + rect->width/2 + 0.5;
}

int VisualTracker::getMidY(cv::Rect* rect) {
	return (int) rect->y + rect->height/2 + 0.5;
}