#include "PhysicalMoveHead.h"

/**
 CONSTUCTOR
*/
PhysicalMoveHead::PhysicalMoveHead() {
	neck_v = math::PI;
	head_v = math::PI;
}

/**
 DECONSTRUCTOR
*/
PhysicalMoveHead::~PhysicalMoveHead() {

}

/**
 The Node execute as child function
 Puts PhysicalMoveHead into controller
 @return The status
*/
Status* PhysicalMoveHead::executeC() {
	status.setRunning();
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* PhysicalMoveHead::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}

std::string PhysicalMoveHead::toString() {
	return "PhysicalMoveHead";
}
