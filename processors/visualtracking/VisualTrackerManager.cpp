#include "VisualTrackerManager.h"

// Tracker Manager Globals
namespace trackerManager {
	unsigned int minimum_frame = 3;
	unsigned int error_frame = 3;
}

/**
 CONSTRUCTOR
 */
VisualTrackerManager::VisualTrackerManager() {

}

/**
 DECONSTRUCTOR
 */
VisualTrackerManager::~VisualTrackerManager() {

}

/**
 Adds the given vector of rects to be tracked
 Adds single rects to the apporiate tracker
 Deletes old trackers
 */
void VisualTrackerManager::addRects(std::vector<cv::Rect> rects, std::shared_ptr<Position> position) {
	// Add a missed count to all trackers
	std::vector<std::shared_ptr<VisualTracker>>::iterator itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		std::shared_ptr<VisualTracker> vt = *itr_tracker;
		vt->missedCount++;
		itr_tracker++;
	}

	// Find or create a new tracker for all rects
	std::vector<cv::Rect>::iterator itr = rects.begin();
	while(itr < rects.end()) {
		cv::Rect_<int> rec = *itr;
		bool found = false;

		// Search trackers for a match
		itr_tracker = trackers.begin();
		while(itr_tracker < trackers.end()) {
			std::shared_ptr<VisualTracker> vt = *itr_tracker;
			if(vt->belongs(&rec, position)) {
				vt->add(rec, position);
				vt->missedCount = 0;
				found = true;
				break;
			}
			itr_tracker++;
		}

		// If none found, create new tracker
		if(!found) {
			std::shared_ptr<VisualTracker> tracker(new VisualTracker());
			trackers.push_back(tracker);
			tracker->add(rec, position);
		}
		itr++;
	}

	// Remove Old Trackers
	itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		std::shared_ptr<VisualTracker> vt = *itr_tracker;
		if(vt->missedCount >= trackerManager::error_frame) {
			itr_tracker = trackers.erase(itr_tracker);
		} else {
			itr_tracker++;
		}
	}
}

/**
 Returns a vector of the averages of all the VisualTrackers
 @return The list of Rects, one for each tracked object
 */
std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> VisualTrackerManager::getRects() {
	std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> rects(new std::vector<std::shared_ptr<cv::Rect>>);
	std::vector<std::shared_ptr<VisualTracker>>::iterator itr_tracker = trackers.begin();
	while(itr_tracker < trackers.end()) {
		std::shared_ptr<VisualTracker> vt = *itr_tracker;
		if(vt->history.size() >= trackerManager::minimum_frame) {
			rects->push_back(vt->getAverage());
		}
		itr_tracker++;
	}
	return rects;
}
