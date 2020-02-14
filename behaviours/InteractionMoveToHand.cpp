#include "InteractionMoveToHand.h"

/**
 CONSTUCTOR
*/
InteractionMoveToHand::InteractionMoveToHand() {

}

/**
 DECONSTRUCTOR
*/
InteractionMoveToHand::~InteractionMoveToHand() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts InteractionMoveToHand into controller
 @return The status
*/
Status* InteractionMoveToHand::executeC() {
	logger::log("InteractionMoveToHand Called as Child");
	status.setRunning();

	logger::log("InteractionMoveToHand This Behaviour is Not Implemented");
	coms::controller.addBehaviour(this);
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* InteractionMoveToHand::executeP(Status* stat) {
	logger::log("InteractionMoveToHand Called as Parent");
	status = *stat;
	return parent->executeP(stat);
}

std::string InteractionMoveToHand::toString() {
	return "InteractionMoveToHand";
}