#include "SeekingBodyUtilityDec.h"

SeekingBodyUtilityDec::SeekingBodyUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingBodyUtilityDec::~SeekingBodyUtilityDec() {

}

double SeekingBodyUtilityDec::getPriority() {
	int visual_width = processor::vp.getVisualWidth();
	int visual_height = processor::vp.getVisualHeight();
	int mid_x = data::centerVisualWidth;
	int mid_y = data::centerVisualHeight;

	// Get bodies currently seen
	std::vector<cv::Rect*>* bodies = processor::vp.getBodyRects();
	if(bodies->size() == 0) {
		return 0.0;
	}

	// Get minimum distance between body and center of vision
	double min_distance = processor::vp.distance(visual_height, visual_width, 0, 0);
	std::vector<cv::Rect*>::iterator itr = bodies->begin();
	while(itr < bodies->end()) {
		cv::Rect_<int>* rect = *itr;
		double rect_distance = processor::vp.distance(processor::vp.getMidX(rect),
			processor::vp.getMidY(rect), mid_x, mid_y);
		if(rect_distance < min_distance) {
			min_distance = rect_distance;
		}
		delete(rect);
		itr = bodies->erase(itr);
	}
	delete(bodies);

	// Priority is ratio of minimum distance to size of vision
	double priority = min_distance / std::min(visual_height, visual_width);

	std::ostringstream strs;
	strs << "SeekingBodyUtilityDec Priority: " << priority
		<< " - Ratio of Distance of Closest Body To Center Of Vision";
	logger::log(strs.str());

	return priority;
}
