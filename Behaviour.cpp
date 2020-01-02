#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "Behaviour.h"
#include "Movement.h"

/**
 CONSTUCTOR
*/
Behaviour::Behaviour() {
	state = fresh;
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
status Behaviour::executeC() {
	return running;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
status Behaviour::executeP(status stat) {
	if (state != running) {
		return failure;
	}
	state = stat;
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
