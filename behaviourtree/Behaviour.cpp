#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "Behaviour.h"
#include "../kinematics/Movement.h"

/**
 CONSTUCTOR
*/
Behaviour::Behaviour() {
	
}

/**
 DECONSTRUCTOR
*/
Behaviour::~Behaviour() {
	actions.clear();
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
	if (status.getState() != running) {
		verbose("WARNING: Behaviour Already Running.");
		return &status;
	}
	status = *stat;
	return parent->executeP(stat);
}

/**
 Generates the movements
 @return The movements
*/
std::vector<Movement*> Behaviour::generateMovements() {
	std::vector<Movement*> movementList;
	return movementList;
}
