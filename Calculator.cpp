#include "Calculator.h"

#include "Node.h"

Node node_calculator;
SensorData Calculator::data = node_calculator.getSensorData();

/**
 CONSTRUCTOR
*/
Calculator::Calculator() {
	Node node;
}

/**
 DECONSTRUCTOR
*/
Calculator::~Calculator() {

}

/**
 Generates the movements given a set of actions
 @param actions The list of actions
 @param beh The beahviour associated with the actions
 @return The list of movements
*/
std::vector<Movement*> *Calculator::generateMovements(std::vector<Action*> actions, Behaviour *beh) {
	std::vector<Movement*> *movements = new std::vector<Movement*>();
	std::vector<Action*>::iterator act_itr;
	Position *pos = &Position(data.getCurrentPosition()->getXPosition(), data.getCurrentPosition()->getYPosition(), data.getCurrentPosition()->getZPosition());
	// For each action generate a movement based on the last one
	for (act_itr = actions.begin(); act_itr < actions.end(); act_itr++) {
		Action* action = *act_itr;
		double newX = pos->getXPosition() + action->getDeltaX();
		double newY = pos->getYPosition() + action->getDeltaY();
		double newZ = pos->getZPosition() + action->getDeltaZ();

		Movement *movement = new Movement();
		movement->setSetPoint(new Position(newX, newY, newZ));
		movement->setCurrentPoint(new Position(pos->getXPosition(), pos->getYPosition(), pos->getZPosition()));
		// For the last movement set the behaviour
		if (act_itr == actions.end() - 1) {
			movement->setBehaviour(beh);
		}
		movements->push_back(movement);

		pos->setXPosition(newX);
		pos->setYPosition(newY);
		pos->setZPosition(newZ);
	}
	return movements;
}