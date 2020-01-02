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
status Sequence::executeC() {
	Node* node = *currentChild;
	node->setParent(this);
	verbose("Call Sequence Child");
	node->executeC();

	currentChild++;
	state = running;
	return state;
}

/**
 Node execute as parent function
 calls the next child or the parent node if done
 @param stat The status of the child executing this parent
 @return the status
*/
status Sequence::executeP(status stat) {
	if (state != running) {
		return failure;
	}
	if (stat == failure) {
		reset();
		return parent->executeP(stat);
	}
	if (currentChild >= children.end()) {
		reset();
		state = success;
		verbose("Call Sequence Parent");
		return parent->executeP(success);
	}
	return executeC();
}

/**
 Resets the sequence node to the beginning
*/
void Sequence::reset() {
	currentChild = children.begin();
}
