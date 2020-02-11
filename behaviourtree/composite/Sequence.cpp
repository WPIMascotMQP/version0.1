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
	logger::log("Sequence Called As Child");

	Node* node = *currentChild;
	node->setParent(this);
	logger::log("Call Sequence Child");
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
	logger::log("Sequence Called As Parent");
	if (stat->getState() == failure) {
		reset();
		return parent->executeP(stat);
	}
	if (currentChild >= children.end()) {
		reset();
		status.setSuccess();
		logger::log("Call Sequence Parent");
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
