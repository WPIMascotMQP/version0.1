#include "InteractionMoveToHand.h"

/**
 CONSTUCTOR
*/
InteractionMoveToHand::InteractionMoveToHand() {
	
}

/**
 DECONSTRUCTOR
*/
InteractionMoveToHand::~InteractionMoveToHand() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts InteractionMoveToHand into controller
 @return The status
*/
Status* InteractionMoveToHand::executeC() {
	status.setRunning();
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* InteractionMoveToHand::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}
