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
	status = status::fresh;
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
int Behaviour::executeC() {
	return status::running;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
int Behaviour::executeP(int stat) {
	if (status != status::running) {
		return status::failure;
	}
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