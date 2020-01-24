#include "MoveFrontLeft.h"

#include "../kinematics/Calculator.h"
#include "../communication/Controller.h"
#include "../behaviourtree/Node.h"

/**
 CONSTRUCTOR
 Creates all of the actions and
 @return The MoveFrontLeft Object
*/
MoveFrontLeft::MoveFrontLeft() {
	Action *mf = new Action(0, 3, 0);
	Action *ml = new Action(-3, 0, 0);
	actions.push_back(mf);
	actions.push_back(ml);
}

/**
 DECONSTRUCTOR
*/
MoveFrontLeft::~MoveFrontLeft() {

}

/**
 Node Execute as child fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/
Status* MoveFrontLeft::executeC() {
	if (status.getState() == running) {
		verbose("WARNING: MoveFrontLeft is Already Running");
		return &status;
	}
	status.setRunning();
	verbose("Execute MoveFrontLeft");
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
Status* MoveFrontLeft::executeP(Status* stat) {
	if (status.getState() != running) {
		verbose("WARNING: MoveFrontLeft is Already Running");
		return &status;
	}
	status = *stat;
	verbose("Call MoveFrontLeft Parent");
	return parent->executeP(stat);
}

std::vector<Movement*> MoveFrontLeft::generateMovements() {
	std::vector<Movement*> movements;
	return movements;
}
