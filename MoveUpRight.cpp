#include "MoveUpRight.h"

#include "Calculator.h"
#include "Controller.h"
#include "Node.h"

/**
 CONSTRUCTOR
 Creates all of the actions and
 @return The MoveUpRight Object
*/
MoveUpRight::MoveUpRight() {
	status = status::fresh;
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
int MoveUpRight::executeC() {
	status = status::running;
	verbose("Execute MoveUpRight");
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
int MoveUpRight::executeP(int stat) {
	if (status != status::running) {
		return status::failure;
	}
	status = status::success;
	verbose("Call MoveUpRight Parent");
	return parent->executeP(stat);
}

std::vector<Movement*> MoveUpRight::generateMovements() {
	std::vector<Movement*> movements;
	return movements;
}