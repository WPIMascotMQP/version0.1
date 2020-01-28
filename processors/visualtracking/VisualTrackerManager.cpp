#include "VisualTrackerManager.h"

namespace trackerManager {
	unsigned int error_frame = 3;
}

VisualTrackerManager::VisualTrackerManager() {

}

VisualTrackerManager::~VisualTrackerManager() {

}

void VisualTrackerManager::addRects(std::vector<cv::Rect> rects) {
	std::vector<VisualTracker*>::iterator itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		VisualTracker* vt = *itr_tracker;
		vt->missedCount++;
		itr_tracker++;
	}

	std::vector<cv::Rect>::iterator itr = rects.begin();
	while(itr < rects.end()) {
		cv::Rect_<int> rec = *itr;
		bool found = false;
		itr_tracker = trackers.begin();
		while(itr_tracker < trackers.end()) {
			VisualTracker* vt = *itr_tracker;
			if(vt->belongs(&rec)) {
				vt->add(rec);
				vt->missedCount = 0;
				found = true;
				break;
			}
			itr_tracker++;
		}
		if(!found) {
			VisualTracker* tracker = new VisualTracker();
			trackers.push_back(tracker);
			tracker->add(rec);
		}
		itr++;
	}

	// Remove Old Trackers
	itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		VisualTracker* vt = *itr_tracker;
		std::cout << vt->missedCount << std::endl;
		if(vt->missedCount >= trackerManager::error_frame) {
			delete(vt);
			itr_tracker = trackers.erase(itr_tracker);
		} else {
			itr_tracker++;
		}
	}
	std::cout << "---" << std::endl;
}

std::vector<cv::Rect*>* VisualTrackerManager::getRects() {
	std::vector<cv::Rect*>* rects = new std::vector<cv::Rect*>;
	std::vector<VisualTracker*>::iterator itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		VisualTracker* vt = *itr_tracker;
		if(vt->history.size() >= trackerManager::error_frame) {
			rects->push_back(vt->getAverage());
		}
		itr_tracker++;
	}
	return rects;
}