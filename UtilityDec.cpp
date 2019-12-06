#include "Utility.h"
#include "UtilityDec.h"

/**
 CONSTRCUTOR
 @param chi The child
*/
UtilityDec::UtilityDec(Node* chi) {
	child = chi;
	status = status::fresh;
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
int UtilityDec::executeP(int stat) {
	if (status != status::running) {
		return status::running;
	}
	status = status::fresh;
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