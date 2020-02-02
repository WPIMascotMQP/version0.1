#include "SeekingMoveSearch.h"

/**
 CONSTUCTOR
*/
SeekingMoveSearch::SeekingMoveSearch() {
	
}

/**
 DECONSTRUCTOR
*/
SeekingMoveSearch::~SeekingMoveSearch() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts SeekingMoveSearch into controller
 @return The status
*/
Status* SeekingMoveSearch::executeC() {
	status.setRunning();
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* SeekingMoveSearch::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}
