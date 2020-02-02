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
	status.setRunning();
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
