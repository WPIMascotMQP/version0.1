#include "SeekingMoveToBody.h"

/**
 CONSTUCTOR
*/
SeekingMoveToBody::SeekingMoveToBody() {

}

/**
 DECONSTRUCTOR
*/
SeekingMoveToBody::~SeekingMoveToBody() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts SeekingMoveToBody into controller
 @return The status
*/
Status* SeekingMoveToBody::executeC() {
	logger::log("SeekingMoveToBody Called as Child");
	status.setRunning();

	int mid_x = processor::vp.getVisualWidth() / 2;
	int max_y = processor::vp.getVisualHeight();

	// Get Closest Body to Center Bottom
	std::shared_ptr<std::vector<std::shared_ptr<cv::Rect>>> bodies = processor::vp.getBodyRects();
	std::vector<std::shared_ptr<cv::Rect>>::iterator itr_body = bodies->begin();
	std::shared_ptr<cv::Rect_<int>> closest_body = *bodies->begin();
	double closest_distance = processor::vp.distance(processor::vp.getMidX(closest_body),
		processor::vp.getMidY(closest_body), mid_x, max_y);
	while(itr_body < bodies->end()) {
		std::shared_ptr<cv::Rect_<int>> body = *itr_body;
		double distance = processor::vp.distance(processor::vp.getMidX(body),
			processor::vp.getMidY(body), mid_x, max_y);
		if(distance < closest_distance) {
			closest_distance = distance;
			closest_body = body;
		}
		itr_body++;
	}

	// Calculate New Position
	int ratio_x = (int) (processor::vp.getMidX(closest_body) - mid_x) /
					mid_x + 0.5;
	int ratio_y = (int) (processor::vp.getMidY(closest_body) - max_y / 2) /
					(max_y / 2) + 0.5;
	double delta_x = ratio_x * processor::vp.getVisualWidthRads() / 2;
	double delta_y = ratio_y * processor::vp.getVisualHeightRads() / 2;
	std::shared_ptr<Position> pos = cal::calculator.getDeltaPosition(delta_x, delta_y);
	coms::controller.addPosition(pos);
	coms::controller.addBehaviour(std::shared_ptr<Behaviour>(this));

	itr_body = bodies->begin();
	while(itr_body < bodies->end()) {
		std::shared_ptr<cv::Rect_<int>> body = *itr_body;
		itr_body = bodies->erase(itr_body);
	}

	logger::log("SeekingMoveToBody", "Calculated Position", pos->toString(), "Position to Move To");
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* SeekingMoveToBody::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}
