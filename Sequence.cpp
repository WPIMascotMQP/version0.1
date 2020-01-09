#include "Sequence.h"

/**
 CONSTRUCTOR
 @param childr The children of this sequence object
*/
Sequence::Sequence(std::vector<Node*> childr) : Composite(childr) {
	currentChild = children.begin();
}

/**
 DECONSTRUCTOR
*/
Sequence::~Sequence() {

}

/**
 Node execute as child function
 Calls all children in order
 @return The status
*/
Status* Sequence::executeC() {
	Node* node = *currentChild;
	node->setParent(this);
	verbose("Call Sequence Child");
	node->executeC();

	currentChild++;
	status.setRunning();
	return &status;
}

/**
 Node execute as parent function
 calls the next child or the parent node if done
 @param stat The status of the child executing this parent
 @return the status
*/
Status* Sequence::executeP(Status* stat) {
	if (status.getState() != running) {
		verbose("WARNING: Sequence is not Running.");
		return &status;
	}
	if (stat->getState() == failure) {
		reset();
		return parent->executeP(stat);
	}
	if (currentChild >= children.end()) {
		reset();
		status.setSuccess();
		verbose("Call Sequence Parent");
		return parent->executeP(&status);
	}
	return executeC();
}

/**
 Resets the sequence node to the beginning
*/
void Sequence::reset() {
	currentChild = children.begin();
}
