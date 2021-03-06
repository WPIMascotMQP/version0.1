#include "Behaviour.h"

#include "../processors/motorstatus/MotorTracker.h"

/**
 CONSTUCTOR
*/
Behaviour::Behaviour() {

}

/**
 DECONSTRUCTOR
*/
Behaviour::~Behaviour() {

}

/**
 The Node execute as child function
 Puts behaviour into controller
 @return The status
*/
Status* Behaviour::executeC() {
	status.setRunning();
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* Behaviour::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}

std::string Behaviour::toString() {
	return "Behaviour";
}
