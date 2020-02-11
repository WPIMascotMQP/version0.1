#include "Parallel.h"

/**
 CONSTRUCTOR
 @param childr The children of this node
*/
Parallel::Parallel(std::vector<Node*> childr) : Composite(childr) {
	successStatus.setSuccess();
	reset();
}

/**
 DECONTRUCTOR
*/
Parallel::~Parallel() {

}

/**
 Node execute as child function
 Calls all children and does not call parent
 until all children return
 @return The status
*/
Status* Parallel::executeC() {
	logger::log("Parallel Called As Child");
	// Iterator through children all call execute on them
	status.setRunning();
	std::vector<Node*>::iterator itr;
	returnedStatus = &successStatus;
	// Call all children
	for (itr = children.begin(); itr < children.end(); itr++) {
		Node *node = *itr;
		node->setParent(this);
		logger::log("Call Parallel Child");
		Status* stat = node->executeC();
		returnedStatus = (stat->getState() == failure) ? stat : &successStatus;
	}
	returnedStatuses = &successStatus;
	return returnedStatus;
}

/**
 Node execute as parent function
 Counts the returned executes and calls parent
 @param stat The status of the child executing this parent
 @return the status
*/
Status* Parallel::executeP(Status* stat) {
	logger::log("Parallel Called As Parent");

	// If children still need to return count number of returns
	returedExecutes++;
	returnedStatuses = (stat->getState() == failure) ? stat : returnedStatuses;
	// If all children have returned call parent
	if (returedExecutes >= children.size()) {
		reset();
		status = *returnedStatuses;
		logger::log("Call Parallel Parent");
		return parent->executeP(returnedStatuses);
	}
	return &status;
}

/**
 Resets the status and returned number of executes
*/
void Parallel::reset() {
	returedExecutes = 0;
}
