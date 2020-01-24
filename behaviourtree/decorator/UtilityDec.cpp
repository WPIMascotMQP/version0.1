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
 Node execute as parent function
 Calls the parent node
 @param stat The status of the child executing this parent
 @return the status
*/
Status* UtilityDec::executeP(Status* stat) {
	if (status.getState() != running) {
		verbose("WARNING: UtilityDec is not Running.");
		return &status;
	}
	status = *stat;
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
