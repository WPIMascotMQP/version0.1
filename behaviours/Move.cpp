#include "Move.h"

/**
 CONSTUCTOR
*/
Move::Move() {
	
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
	status.setRunning();
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
