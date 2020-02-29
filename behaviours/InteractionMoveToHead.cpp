#include "InteractionMoveToHead.h"

/**
 CONSTUCTOR
*/
InteractionMoveToHead::InteractionMoveToHead() {
	neck_v = math::PI;
	head_v = math::PI;
}

/**
 DECONSTRUCTOR
*/
InteractionMoveToHead::~InteractionMoveToHead() {

}

/**
 The Node execute as child function
 Puts InteractionMoveToHead into controller
 @return The status
*/
Status* InteractionMoveToHead::executeC() {
	logger::log("InteractionMoveToHead Called as Child");
	status.setRunning();

	int mid_x = processor::vp.getVisualWidth() / 2;
	int max_y = processor::vp.getVisualHeight();

	// Get Closest Face to Center Bottom
	std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> faces = processor::vp.getFaceRects();
	std::vector<std::shared_ptr<cv::Rect>>::iterator itr_face = faces->begin();
	std::shared_ptr<cv::Rect_<int>> closest_face = *faces->begin();
	double closest_distance = processor::vp.distance(processor::vp.getMidX(closest_face),
		processor::vp.getMidY(closest_face), mid_x, max_y);
	while(itr_face < faces->end()) {
		std::shared_ptr<cv::Rect_<int>> face = *itr_face;
		double distance = processor::vp.distance(processor::vp.getMidX(face),
			processor::vp.getMidY(face), mid_x, max_y);
		if(distance < closest_distance) {
			closest_distance = distance;
			closest_face = face;
		}
		itr_face++;
	}

	// Calculate New Position
	double ratio_x = (0.0 + processor::vp.getMidX(closest_face) - mid_x) / mid_x;
	double ratio_y = (0.0 + processor::vp.getMidY(closest_face) - max_y) / max_y;
	double delta_x = ratio_x * processor::vp.getVisualWidthRads() / 2;
	double delta_y = ratio_y * processor::vp.getVisualHeightRads() / 2;
	std::shared_ptr<Movement> mov = cal::calculator.getDeltaMovement(delta_x, delta_y, neck_v, head_v);
	coms::controller.addMovement(mov);
	coms::controller.addBehaviour(this);

	itr_face = faces->begin();
	while(itr_face < faces->end()) {
		std::shared_ptr<cv::Rect_<int>> face = *itr_face;
		itr_face = faces->erase(itr_face);
	}

	logger::log("InteractionMoveToHead", "Calculated Movement", mov->toString(), "Movement to do");
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* InteractionMoveToHead::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}

std::string InteractionMoveToHead::toString() {
	return "InteractionMoveToHead";
}
