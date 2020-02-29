#include "Move.h"

/**
 CONSTUCTOR
*/
Move::Move(double ny, double np, double hy, double hp) {
	neck_yaw = ny;
	neck_pitch = np;
	head_yaw = hy;
	head_pitch = hp;
	neck_v = math::PI;
	head_v = math::PI;
}

/**
 DECONSTRUCTOR
*/
Move::~Move() {

}

/**
 The Node execute as child function
 Puts Move into controller
 @return The status
*/
Status* Move::executeC() {
	logger::log("Move Called as Child");
	status.setRunning();

	std::shared_ptr<Movement> mov = cal::calculator.getDeltaMovement(
		neck_yaw, neck_pitch, head_yaw, head_pitch, neck_v, head_v);
	coms::controller.addMovement(mov);
	coms::controller.addBehaviour(this);

	logger::log("Move", "Calculated Movement", mov->toString(), "Movement to do");
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

std::string Move::toString() {
	return "Move";
}
