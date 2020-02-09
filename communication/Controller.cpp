#include "Controller.h"

#include "../MasterControlLoop.h"
#include "../behaviourtree/Node.h"
#include "../kinematics/Position.h"

std::vector<Behaviour*> currentBehaviours;

/**
 CONSTRUCTOR
*/
Controller::Controller() {
	std::vector<std::vector<Movement*>*> movL;
	movementsList = movL;
}

/**
 DECONSTRUCTOR
*/
Controller::~Controller() {

}

/**
 Adds movements to do
 @param movements The movements to add
*/
void Controller::addMovements(std::vector<Movement*> *movements) {
	movementsList.push_back(movements);
}

/**
 Splits up the movements and executes of them
 @return The status
*/
Status* Controller::execute() {
	return status.setSuccess();
}
