#include "MoveUpRight.h"

#include "kinematics/Calculator.h"
#include "Controller.h"
#include "Node.h"

/**
 CONSTRUCTOR
 Creates all of the actions and
 @return The MoveUpRight Object
*/
MoveUpRight::MoveUpRight() {
	Action *mur = new Action(3.0, 0.0, 3.0);
	actions.push_back(mur);
}

/**
 DECONSTRUCTOR
*/
MoveUpRight::~MoveUpRight() {

}

/**
 Node Execute as child fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/
Status* MoveUpRight::executeC() {
	if (status.getState() == running) {
		verbose("WARNING: MoveUpRight is Already Running.");
		return &status;
	}
	status.setRunning();
	verbose("Execute MoveUpRight");
	std::vector<Movement*>* movements = calculator.generateMovements(actions, this);
	controller.addMovements(movements);
	return &status;
}

/**
 Node Execute as parent fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/
Status* MoveUpRight::executeP(Status* stat) {
	if (status.getState() != running) {
		verbose("WARNING: MoveUpRight is not Running.");
		return &status;
	}
	status = *stat;
	verbose("Call MoveUpRight Parent");
	return parent->executeP(stat);
}

std::vector<Movement*> MoveUpRight::generateMovements() {
	std::vector<Movement*> movements;
	return movements;
}
