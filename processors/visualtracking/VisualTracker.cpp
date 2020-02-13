#include "VisualTracker.h"

// Tracker Global constants
namespace trackers {
	int center_error = 100;
	int size_error = 200;

	unsigned int history_length = 5;
}

/**
 CONSTRUCTOR
*/
VisualTracker::VisualTracker() {
	missedCount = 0;
}

/**
 DECONSTRUCTOR
 */
VisualTracker::~VisualTracker() {
	std::vector<cv::Rect*>::iterator itr = history.begin();
	if(itr < history.end()) {
	    cv::Rect_<int>* rec = *itr;
		delete(rec);
		itr = history.erase(itr);
	}
}

/**
 Returns whether the given rect is closer enough to be considered the object that this object is
 tracking
 @param rect The new rect to compare
 @return Whether the rect is part of this tracker of not
 */
bool VisualTracker::belongs(cv::Rect* rect, std::shared_ptr<Position> position) {
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

/**
 Adds the given rect to the history in this object
 Deletes old history
 @param rect The rect to add
 */
void VisualTracker::add(cv::Rect rect, std::shared_ptr<Position> position) {
	cv::Rect_<int>* new_rect = new cv::Rect(rect.x, rect.y, rect.width, rect.height);
	history.push_back(new_rect);
	if(history.size() > trackers::history_length) {
		std::vector<cv::Rect*>::iterator itr = history.begin();
        cv::Rect_<int>* rec = *itr;
        delete(rec);
        history.erase(itr);
	}
}

/**
 Creates a new rect which is the average position of the previous captured rects
 @return The average rect for this object
 */
cv::Rect* VisualTracker::getAverage() {
	int sum_weight = 0;
	int current_weight = 1;

	int sum_x = 0;
	int sum_y = 0;

	int sum_width = 0;
	int sum_height = 0;

	std::vector<cv::Rect*>::iterator itr = history.begin();
	while(itr < history.end()) {
		cv::Rect_<int>* rec = *itr;
		sum_x += rec->x * current_weight;
		sum_y += rec->y * current_weight;
		sum_width += rec->width * current_weight;
		sum_height += rec->height * current_weight;
		sum_weight += current_weight;
		current_weight++;
		itr++;
	}

	cv::Rect* rect = new cv::Rect((int) sum_x/sum_weight + 0.5,
								(int) sum_y/sum_weight + 0.5,
								(int) sum_width/sum_weight + 0.5,
								(int) sum_height/sum_weight + 0.5);
	return rect;
}

/**
 Returns the x midpoint of the given rect
 @param The rect to get the x mdpoint
 @return The x midpoint
 */
int VisualTracker::getMidX(cv::Rect* rect) {
	return (int) rect->x + rect->width/2 + 0.5;
}

/**
 Returns the y midpoint of the given rect
 @param The rect to get the y mdpoint
 @return The y midpoint
 */
int VisualTracker::getMidY(cv::Rect* rect) {
	return (int) rect->y + rect->height/2 + 0.5;
}
