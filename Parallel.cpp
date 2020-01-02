#include "Parallel.h"

/**
 CONSTRUCTOR
 @param childr The children of this node
*/
Parallel::Parallel(std::vector<Node*> childr) : Composite(childr) {
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
status Parallel::executeC() {
	// Iterator through children all call execute on them
	state = running;
	std::vector<Node*>::iterator itr;
	status returnedStatus = running;
	// Call all children
	for (itr = children.begin(); itr < children.end(); itr++) {
		Node *node = *itr;
		node->setParent(this);
		verbose("Call Parallel Child");
		returnedStatus = (node->executeC() == failure) ? failure : running;
	}
	returnedStatuses = success;
	return returnedStatus;
}

/**
 Node execute as parent function
 Counts the returned executes and calls parent
 @param stat The status of the child executing this parent
 @return the status
*/
status Parallel::executeP(status stat) {
	// If children still need to return count number of returns
	if (state != running) {
		return failure;
	}
	returedExecutes++;
	returnedStatuses = (stat == failure) ? failure : returnedStatuses;
	// If all children have returned call parent
	if (returedExecutes >= children.size()) {
		reset();
		state = returnedStatuses;
		verbose("Call Parallel Parent");
		return parent->executeP(returnedStatuses);
	}
	return running;
}

/**
 Resets the status and returned number of executes
*/
void Parallel::reset() {
	returedExecutes = 0;
}
