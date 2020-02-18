#include "SeekingMotionUtilityDec.h"

SeekingMotionUtilityDec::SeekingMotionUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingMotionUtilityDec::~SeekingMotionUtilityDec() {

}

double SeekingMotionUtilityDec::getPriority() {
	int visual_width = processor::vp.getVisualWidth();
	int visual_height = processor::vp.getVisualHeight();
	int mid_x = data::centerVisualWidth;
	int mid_y = data::centerVisualHeight;

	// Get bodies currently seen
	std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> bodies = processor::vp.getBodyRects();
	if(bodies->size() == 0) {
		logger::log("SeekingMotionUtilityDec", "Priority:", 0.0, "No Bodies Found");
		return 0.0;
	}

	// Get minimum distance between body and center of vision
	double min_distance = processor::vp.distance(visual_height, visual_width, 0, 0);
	std::vector<std::shared_ptr<cv::Rect>>::iterator itr = bodies->begin();
	while(itr < bodies->end()) {
		std::shared_ptr<cv::Rect_<int>> rect = *itr;
		double rect_distance = processor::vp.distance(processor::vp.getMidX(rect),
			processor::vp.getMidY(rect), mid_x, mid_y);
		if(rect_distance < min_distance) {
			min_distance = rect_distance;
		}
		itr = bodies->erase(itr);
	}

	// Priority is ratio of minimum distance to size of vision
	double priority = (std::min(visual_height, visual_width) - min_distance) / std::min(visual_height, visual_width);

	logger::log("SeekingMotionUtilityDec", "Priority:", priority,
		"Ratio of Distance of Closest Body To Center Of Vision");

	return 0.3;
}
