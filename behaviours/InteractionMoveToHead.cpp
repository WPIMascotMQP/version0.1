#include "InteractionMoveToHead.h"

/**
 CONSTUCTOR
*/
InteractionMoveToHead::InteractionMoveToHead() {

}

/**
 DECONSTRUCTOR
*/
InteractionMoveToHead::~InteractionMoveToHead() {
	actions.clear();
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
	std::shared_ptr<Position> pos = cal::calculator.getDeltaPosition(delta_x, delta_y);
	coms::controller.addPosition(pos);
	coms::controller.addBehaviour(std::shared_ptr<Behaviour>(this));

	itr_face = faces->begin();
	while(itr_face < faces->end()) {
		std::shared_ptr<cv::Rect_<int>> face = *itr_face;
		itr_face = faces->erase(itr_face);
	}

	logger::log("InteractionMoveToHead", "Calculated Position", pos->toString(), "Position to Move To");
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
