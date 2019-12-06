#include "MoveFrontLeft.h"

#include "Calculator.h"
#include "Controller.h"
#include "Node.h"

/**
 CONSTRUCTOR
 Creates all of the actions and
 @return The MoveFrontLeft Object
*/
MoveFrontLeft::MoveFrontLeft() {
	status = status::fresh;
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
int MoveFrontLeft::executeC() {
	status = status::running;
	verbose("Execute MoveFrontLeft");
	std::vector<Movement*>* movements = calculator.generateMovements(actions, this);
	controller.addMovements(movements);
	return status::running;
}

/**
 Node Execute as parent fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/
int MoveFrontLeft::executeP(int stat) {
	if (status != status::running) {
		return status::failure;
	}
	status = status::success;
	verbose("Call MoveFrontLeft Parent");
	return parent->executeP(stat);
}

std::vector<Movement*> MoveFrontLeft::generateMovements() {
	std::vector<Movement*> movements;
	return movements;
}