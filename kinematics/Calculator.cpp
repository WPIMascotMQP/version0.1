#include "Calculator.h"

#include "../behaviourtree/Node.h"

namespace cal {
	Calculator calculator(0);

}

/**
 CONSTRUCTOR
*/
Calculator::Calculator(int start_int) {

}

/**
 DECONSTRUCTOR
*/
Calculator::~Calculator() {

}

Position* Calculator::getDeltaPosition(double yaw, double pitch) {
	Position* current_pos = data::sensor_data.getCurrentPosition();
	Position* physical_pos = processor::mp.toPhysicalPosiiton(current_pos);

	Position* new_pos = processor::mp.toMotorPosition(physical_pos);
	delete(physical_pos);
	delete(current_pos);
	return(new_pos);
}

Position* Calculator::getDeltaPosition(double by, double bp, double ny, double np) {
	Position* current_pos = data::sensor_data.getCurrentPosition();
	Position* new_pos = new Position(current_pos);
	delete(current_pos);
	return(new_pos);
}

double Calculator::getNeckHeadRatio(double from_0) {
	return 0.5;
}
/**
 Generates the movements given a set of actions
 @param actions The list of actions
 @param beh The beahviour associated with the actions
 @return The list of movements
*/
/*std::vector<Movement*> *Calculator::generateMovements(std::vector<Action*> actions, Behaviour *beh) {
	std::vector<Movement*> *movements = new std::vector<Movement*>();
	std::vector<Action*>::iterator act_itr;
	Position pos = Position(data::sensorData.getCurrentPosition()->getXPosition(),
		data::sensorData.getCurrentPosition()->getYPosition(),
		data::sensorData.getCurrentPosition()->getZPosition());
	// For each action generate a movement based on the last one
	for (act_itr = actions.begin(); act_itr < actions.end(); act_itr++) {
		Action* action = *act_itr;
		double newX = pos.getXPosition() + action->getDeltaX();
		double newY = pos.getYPosition() + action->getDeltaY();
		double newZ = pos.getZPosition() + action->getDeltaZ();

		Movement *movement = new Movement();
		movement->setSetPoint(new Position(newX, newY, newZ));
		movement->setCurrentPoint(new Position(pos.getXPosition(), pos.getYPosition(), pos.getZPosition()));
		// For the last movement set the behaviour
		if (act_itr == actions.end() - 1) {
			movement->setBehaviour(beh);
		}
		movements->push_back(movement);

		pos.setXPosition(newX);
		pos.setYPosition(newY);
		pos.setZPosition(newZ);
	}
	return movements;
}*/
