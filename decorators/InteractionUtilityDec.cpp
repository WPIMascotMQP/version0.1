#include "InteractionUtilityDec.h"

InteractionUtilityDec::InteractionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionUtilityDec::~InteractionUtilityDec() {

}

double InteractionUtilityDec::getPriority() {
	int visual_height = data::sensorData.getVisualHeight();
	std::vector<cv::Rect*>* faces = data::sensorData.getFaces();
	std::vector<cv::Rect*>::iterator itr = faces->begin();
	double max_ratio = 0;
	while(itr < faces->end()) {
		cv::Rect_<int>* rect = *itr;
		if(rect->height / visual_height > max_ratio) {
			max_ratio = rect->height / visual_height;
		}
		delete(rect);
		itr = faces->erase(itr);
	}
	delete(faces);
	if(max_ratio > 0.9) {
		max_ratio = 0.9;
	}
	return max_ratio;
}