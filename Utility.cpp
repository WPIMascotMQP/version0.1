#include "Utility.h"

/**
 CONSTRUCTOR
 @param childr The children of the Utiltiy
*/
Utility::Utility(std::vector<UtilityDec*> childr) {
	children = childr;
	state = fresh;
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
status Utility::executeC() {
	state = running;

	// Get Priorities
	std::vector<double> priorities;
	std::vector<UtilityDec*>::iterator itr;
	for (itr = children.begin(); itr < children.end(); itr++) {
		UtilityDec* node = *itr;
		priorities.push_back(node->getPriority());
	}

	// Get Highest Priority
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
		state = failure;
		verbose("Call Utility Parent");
		return parent->executeP(state);
	}

	// Call Highest Child
	UtilityDec* node = *itr;
	node->setParent(this);
	verbose("Call Utility Child");
	node->executeC();
	return state;
}

/**
 Node execute as parent function
 Calls parent or calls another child on failure
 @param stat The status of the child executing this parent
 @param dec The decorator which returned failure
 @return the status
*/
status Utility::executeP(status stat, UtilityDec* dec) {
	if (state != running) {
		return not_running;
	}
	if (stat == failure) {
		failures.push_back(dec);
		if (children.size() == failures.size()) {
			failures.clear();
			state = failure;
			verbose("Call Utility Parent");
			return parent->executeP(stat);
		}
		return executeC();
	}
	failures.clear();
	state = stat;
	verbose("Call Utility Parent");
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
