#include "Decorator.h"

/**
 CONSTUCTOR
 @param chi The child of the decorator
*/
Decorator::Decorator(Node *chi) {
	child = chi;
}

/**
 DECONSTRUCTOR
*/
Decorator::~Decorator() {

}

/**
 The Node execute as child function
 Calls the child
 @return The status
*/
Status* Decorator::executeC() {
	status.setRunning();
	child->setParent(this);
	logger::log("Call Decorator Child");
	return child->executeC();;
}

/**
 Node execute as parent function
 Calls the parent node
 @param stat The status of the child executing this parent
 @return the status
*/
Status* Decorator::executeP(Status* stat) {
	status = *stat;
	logger::log("Call Decorator Parent");
	return parent->executeP(stat);
}

/**
 Sets the child
 @param chi The child
*/
void Decorator::setChild(Node *chi) {
	child = chi;
}
