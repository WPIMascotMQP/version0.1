#include "Controller.h"

#include "MasterControlLoop.h"
#include "Node.h"
#include "Position.h"

Node node_controller;
SensorData Controller::data = node_controller.getSensorData();

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
int Controller::execute() {
	std::vector<std::vector<Movement*>*>::iterator list_itr;
	for (list_itr = movementsList.begin(); list_itr < movementsList.end(); list_itr++) {
		std::vector<Movement*> *movements = *list_itr;
		std::vector<Movement*>::iterator move_itr = movements->begin();

		Movement *movement = *move_itr;
		Position *set_pos = movement->getSetPoint();
		Position *cur_pos = movement->getCurrentPoint();
		// Calculate total change
		double deltaX = set_pos->getXPosition() - cur_pos->getXPosition();
		double deltaY = set_pos->getYPosition() - cur_pos->getYPosition();
		double deltaZ = set_pos->getZPosition() - cur_pos->getZPosition();

		// Limit change to 1
		double moveX = deltaX;
		double moveY = deltaY;
		double moveZ = deltaZ;
		if (deltaX > 1  || deltaX < -1) {
			moveX = deltaX > 1 ? 1 : -1;
		}
		if (deltaY > 1 || deltaY < -1) {
			moveY = deltaY > 1 ? 1 : -1;
		}
		if (deltaZ > 1 || deltaZ < -1) {
			moveZ = deltaZ > 1 ? 1 : -1;
		}

		// Change positions
		cur_pos->setXPosition(cur_pos->getXPosition() + moveX);
		cur_pos->setYPosition(cur_pos->getYPosition() + moveY);
		cur_pos->setZPosition(cur_pos->getZPosition() + moveZ);

		Position *act_pos = data.getCurrentPosition();
		act_pos->setXPosition(act_pos->getXPosition() + moveX);
		act_pos->setYPosition(act_pos->getYPosition() + moveY);
		act_pos->setZPosition(act_pos->getZPosition() + moveZ);
		

		std::cout << "SP:" << *set_pos << " | VP:" << *cur_pos << " | AP:" << *act_pos;
		if (list_itr + 1 < movementsList.end()) {
			std::cout << std::endl;
		}
		if (*(movement->getCurrentPoint()) == *(movement->getSetPoint())) {
			// Remove single movement
			delete(set_pos);
			delete(cur_pos);
			movements->erase(move_itr);
			
			if (movement->getBehaviour()) {
				// Remove list of movements
				currentBehaviours.push_back(movement->getBehaviour());
				movementsList.erase(list_itr);
				delete(movements);
			}
			delete(movement);
		} 
	}
	return status::success;
}