#include "InteractionHeadUtilityDec.h"

InteractionHeadUtilityDec::InteractionHeadUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionHeadUtilityDec::~InteractionHeadUtilityDec() {

}

double InteractionHeadUtilityDec::getPriority() {
	int visual_width = data::sensorData.getVisualWidth();
	int visual_height = data::sensorData.getVisualHeight();
	int mid_x = (int) visual_width / 2 + 0.5;
	int mid_y = (int) visual_height / 2 + 0.5;	

	std::vector<cv::Rect*>* faces = data::sensorData.getFaces();
	if(faces->size() == 0) {
		return 0.0;
	}

	double min_distance = distance(visual_height, visual_width, 0, 0);
	std::vector<cv::Rect*>::iterator itr = faces->begin();
	while(itr < faces->end()) {
		cv::Rect_<int>* rect = *itr;
		double rect_distance = distance(getMidX(rect), getMidY(rect), mid_x, mid_y);
		if(rect_distance < min_distance) {
			min_distance = rect_distance;
		}
		delete(rect);
		itr = faces->erase(itr);
	}
	delete(faces);
	return min_distance / std::min(visual_height, visual_width);
}

double InteractionHeadUtilityDec::distance(int x1, int y1, int x2, int y2) {
	return std::sqrt(std::pow(std::abs(x1-x2), 2) + std::pow(std::abs(y1-y2), 2));
}

/**
 Returns the x midpoint of the given rect
 @param The rect to get the x mdpoint
 @return The x midpoint
 */
int InteractionHeadUtilityDec::getMidX(cv::Rect* rect) {
	return (int) rect->x + rect->width/2 + 0.5;
}

/**
 Returns the y midpoint of the given rect
 @param The rect to get the y mdpoint
 @return The y midpoint
 */
int InteractionHeadUtilityDec::getMidY(cv::Rect* rect) {
	return (int) rect->y + rect->height/2 + 0.5;
}