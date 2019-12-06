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
int Sequence::executeC() {
	Node* node = *currentChild;
	node->setParent(this);
	verbose("Call Sequence Child");
	node->executeC();

	currentChild++;
	status = status::running;
	return status::running;
}

/**
 Node execute as parent function
 calls the next child or the parent node if done
 @param stat The status of the child executing this parent
 @return the status
*/
int Sequence::executeP(int stat) {
	if (status != status::running) {
		return status::failure;
	}
	if (stat == status::failure) {
		reset();
		return parent->executeP(stat);
	}
	if (currentChild >= children.end()) {
		reset();
		verbose("Call Sequence Parent");
		return parent->executeP(status::success);
	}
	return executeC();
}

/**
 Resets the sequence node to the beginning
*/
void Sequence::reset() {
	currentChild = children.begin();
}