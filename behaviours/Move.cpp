#include "Move.h"

/**
 CONSTUCTOR
*/
Move::Move(double ny, double np, double hy, double hp) {
	neck_yaw = ny;
	neck_pitch = np;
	head_yaw = hy;
	head_pitch = hp;
}

/**
 DECONSTRUCTOR
*/
Move::~Move() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts Move into controller
 @return The status
*/
Status* Move::executeC() {
	logger::log("Move Called as Child");
	status.setRunning();

	Position* pos = cal::calculator.getDeltaPosition(
		neck_yaw, neck_pitch, head_yaw, head_pitch);
	coms::controller.addPosition(pos);
	coms::current_behaviours.push_back(this);

	logger::log("Move", "Calculated Position", pos->toString(), "Position to Move To");
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* Move::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}
