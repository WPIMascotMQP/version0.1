#include "../composite/Utility.h"
#include "UtilityDec.h"

/**
 CONSTRCUTOR
 @param chi The child
*/
UtilityDec::UtilityDec(Node* chi) {
	child = chi;
}

/**
 DECONSTRUCTOR
*/
UtilityDec::~UtilityDec() {

}

/**
 The Node execute as child function
 Calls the child
 @return The status
*/
Status* UtilityDec::executeC() {
	status.setRunning();
	child->setParent(this);
	logger::log("Call Utility Decorator Child");
	return child->executeC();;
}

/**
 Node execute as parent function
 Calls the parent node
 @param stat The status of the child executing this parent
 @return the status
*/
Status* UtilityDec::executeP(Status* stat) {
	status = *stat;
	logger::log("Call Utility Decorator Parent");
	return parent->executeP(stat, this);
}

/**
 Sets the parent
 @param par The parent
*/
void UtilityDec::setParent(Utility* par) {
	parent = par;
}

/**
 Gets the priority of the behaviour
 @return The priority of the behaviour
*/
double UtilityDec::getPriority() {
	return 0.0;
}
