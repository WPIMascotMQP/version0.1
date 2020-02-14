#include "InteractionUtilityDec.h"

namespace interactionUtilityDec {
	double max_priority = 0.9;
}

InteractionUtilityDec::InteractionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionUtilityDec::~InteractionUtilityDec() {

}

double InteractionUtilityDec::getPriority() {
	int visual_width = processor::vp.getVisualWidth();
	int visual_height = processor::vp.getVisualHeight();

	// Get max ratio of face size to visual size
	double max_ratio = 0.0;
	std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> faces = processor::vp.getFaceRects();
	std::vector<std::shared_ptr<cv::Rect>>::iterator itr = faces->begin();
	while(itr < faces->end()) {
		std::shared_ptr<cv::Rect_<int>> rect = *itr;
		double ratio = (0.0 + std::max(rect->width, rect->height))
			/ std::min(visual_width, visual_height);
		if(ratio > max_ratio) {
			max_ratio = ratio;
		}
		itr = faces->erase(itr);
	}

	// Limit to max priority
	if(max_ratio > interactionUtilityDec::max_priority) {
		max_ratio = interactionUtilityDec::max_priority;
	}

	logger::log("InteractionUtilityDec", "Priority:", max_ratio,
		"Ratio of Largest Face to Total Vision");

	return max_ratio;
}
