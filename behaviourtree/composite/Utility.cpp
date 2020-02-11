#include "Utility.h"

/**
 CONSTRUCTOR
 @param childr The children of the Utiltiy
*/
Utility::Utility(std::vector<UtilityDec*> childr) {
	children = childr;
}

/**
 DECONSTRUCTOR
*/
Utility::~Utility() {

}

/**
 Node execute as child function
 Calls the highest scoring child
 @return The status
*/
Status* Utility::executeC() {
	logger::log("Utility Composite Called As Child");
	status.setRunning();

	// Get Priorities
	std::vector<double> priorities;
	std::vector<UtilityDec*>::iterator itr;
	for (itr = children.begin(); itr < children.end(); itr++) {
		UtilityDec* node = *itr;
		priorities.push_back(node->getPriority());
	}

	// Get Highest Priority (Skipping Failures)
	std::vector<double>::iterator pro_itr;
	std::vector<double>::iterator max_itr = priorities.begin();
	std::vector<UtilityDec*>::iterator fail_itr = children.begin();
	itr = children.begin();
	for (pro_itr = priorities.begin(); pro_itr < priorities.end(); pro_itr++) {
		if (*pro_itr > *max_itr && std::find(failures.begin(), failures.end(), *fail_itr) == failures.end()) {
			while (max_itr != pro_itr) {
				max_itr++;
				itr++;
			}
		}
		fail_itr++;
	}

	// All prioirties are 0.0
	if (*max_itr == 0.0) {
		failures.clear();
		status.setFailure();
		status.setErrorCode(-3101);
		status.setDescription("All Children Returned Priority 0.0");
		logger::log("Call Utility Composite Parent");
		return parent->executeP(&status);
	}

	// Call Highest Child
	UtilityDec* node = *itr;
	node->setParent(this);
	logger::log("Call Utility Composite Child");
	node->executeC();
	return &status;
}

/**
 Node execute as parent function
 Calls parent or calls another child on failure
 @param stat The status of the child executing this parent
 @param dec The decorator which returned failure
 @return the status
*/
Status* Utility::executeP(Status* stat, UtilityDec* dec) {
	logger::log("Utility Composite Called As Parent");
	if (stat->getState() == failure) {
		failures.push_back(dec);
		if (children.size() == failures.size()) {
			failures.clear();
			status.setFailure();
			status.setErrorCode(-3102);
			status.setDescription("All Children Failed in Execution");
			logger::log("Call Utility Composite Parent");
			return parent->executeP(&status);
		}
		return executeC();
	}
	failures.clear();
	status = *stat;
	logger::log("Call Utility Composite Parent");
	return parent->executeP(stat);
}

/**
 Adds a child to the utility
 @param chi The child to add
*/
void Utility::addChild(UtilityDec* chi) {
	children.push_back(chi);
}

/**
 Removes a child from the utility
 @param chi The child to remove
*/
void Utility::removeChild(UtilityDec* chi) {
	std::vector<UtilityDec*>::iterator itr;
	for (itr = children.begin(); itr < children.end(); itr++) {
		if (chi == *itr) {
			children.erase(itr);
		}
	}
}

/**
 Clears all children
*/
void Utility::clearChildren() {
	children.clear();
}
