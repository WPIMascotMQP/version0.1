#include "PhysicalMoveHead.h"

/**
 CONSTUCTOR
*/
PhysicalMoveHead::PhysicalMoveHead() {
	
}

/**
 DECONSTRUCTOR
*/
PhysicalMoveHead::~PhysicalMoveHead() {
	actions.clear();
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
