#include "InteractionUtilityDec.h"

namespace interactionUtilityDec {
		int max_priority = 0.9;
}

InteractionUtilityDec::InteractionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionUtilityDec::~InteractionUtilityDec() {

}

double InteractionUtilityDec::getPriority() {
	int visual_width = data::sensorData.getVisualWidth();
	int visual_height = data::sensorData.getVisualHeight();

	// Get max ratio of face size to visual size
	double max_ratio = 0.0;
	std::vector<cv::Rect*>* faces = data::sensorData.getFaces();
	std::vector<cv::Rect*>::iterator itr = faces->begin();
	while(itr < faces->end()) {
		cv::Rect_<int>* rect = *itr;
		double ratio = rect->height / std::min(visual_height, visual_width);
		if(ratio > max_ratio) {
			max_ratio = ratio;
		}
		delete(rect);
		itr = faces->erase(itr);
	}
	delete(faces);

	// Limit to max priority
	if(max_ratio > interactionUtilityDec::max_priority) {
		max_ratio = interactionUtilityDec::max_priority;
	}

	std::ostringstream strs;
	strs << "InteractionUtilityDec Priority: " << max_ratio
		<< " - Ratio of Largest Face to Total Vision";
	logger::log(strs.str());

	return max_ratio;
}
