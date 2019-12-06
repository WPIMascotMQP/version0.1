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
int Parallel::executeC() {
	// Iterator through children all call execute on them
	status = status::running;
	std::vector<Node*>::iterator itr;
	int returnedStatus = status::running;
	// Call all children
	for (itr = children.begin(); itr < children.end(); itr++) {
		Node *node = *itr;
		node->setParent(this);
		verbose("Call Parallel Child");
		returnedStatus = (node->executeC() == status::failure) ? status::failure : status::running;
	}
	returnedStatuses = status::success;
	return returnedStatus;
}

/**
 Node execute as parent function
 Counts the returned executes and calls parent
 @param stat The status of the child executing this parent
 @return the status
*/
int Parallel::executeP(int stat) {
	// If children still need to return count number of returns
	if (status != status::running) {
		return status::failure;
	}
	returedExecutes++;
	returnedStatuses = (stat == status::failure) ? status::failure : returnedStatuses;
	// If all children have returned call parent
	if (returedExecutes >= children.size()) {
		reset();
		verbose("Call Parallel Parent");
		return parent->executeP(returnedStatuses);
	}
	return status::running;
}

/**
 Resets the status and returned number of executes
*/
void Parallel::reset() {
	status = status::fresh;
	returedExecutes = 0;
}