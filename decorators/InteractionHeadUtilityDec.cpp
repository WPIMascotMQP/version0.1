#include "InteractionHeadUtilityDec.h"

InteractionHeadUtilityDec::InteractionHeadUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionHeadUtilityDec::~InteractionHeadUtilityDec() {

}

double InteractionHeadUtilityDec::getPriority() {
	int visual_width = processor::vp.getVisualWidth();
	int visual_height = processor::vp.getVisualHeight();
	int mid_x = (int) visual_width / 2 + 0.5;
	int mid_y = (int) visual_height / 2 + 0.5;

	// Get faces that currently in vision
	std::vector<cv::Rect*>* faces = processor::vp.getFaceRects();
	if(faces->size() == 0) {
		return 0.0;
	}

	// Get minimum distance from head to center of vision
	double min_distance = processor::vp.distance(visual_height, visual_width, 0, 0);
	std::vector<cv::Rect*>::iterator itr = faces->begin();
	while(itr < faces->end()) {
		cv::Rect_<int>* rect = *itr;
		double rect_distance = processor::vp.distance(processor::vp.getMidX(rect),
			processor::vp.getMidY(rect), mid_x, mid_y);
		if(rect_distance < min_distance) {
			min_distance = rect_distance;
		}
		delete(rect);
		itr = faces->erase(itr);
	}
	delete(faces);

	// Priority is minimum distance to size of vision
	double priority = min_distance / std::min(visual_height, visual_width);

	std::ostringstream strs;
	strs << "InteractionHeadUtilityDec Priority: " << priority
		<< " - Ratio of Distance of Closest Face To Center Of Vision";
	logger::log(strs.str());

	return priority;
}
