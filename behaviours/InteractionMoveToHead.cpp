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
	status.setRunning();
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
