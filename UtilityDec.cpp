#include "Utility.h"
#include "UtilityDec.h"

/**
 CONSTRCUTOR
 @param chi The child
*/
UtilityDec::UtilityDec(Node* chi) {
	child = chi;
	state = fresh;
}

/**
 DECONSTRUCTOR
*/
UtilityDec::~UtilityDec() {

}

/**
 Node execute as parent function
 Calls the parent node
 @param stat The status of the child executing this parent
 @return the status
*/
status UtilityDec::executeP(status stat) {
	if (state != running) {
		return not_running;
	}
	state = stat;
	verbose("Call Decorator Parent");
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
