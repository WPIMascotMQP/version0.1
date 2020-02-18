#include "Controller.h"

#include "../MasterControlLoop.h"
#include "../behaviourtree/Behaviour.h"
#include "../behaviourtree/Node.h"

namespace coms {
	Controller controller(0);
	std::vector<Behaviour*> behaviour_list_current;
	std::vector<Behaviour*> behaviour_list_execute;
}

/**
 CONSTRUCTOR
*/
Controller::Controller(int start_int) {

}

/**
 DECONSTRUCTOR
*/
Controller::~Controller() {

}

/**
 Adds position to move to
 @param pos The position to add
*/
void Controller::addPosition(std::shared_ptr<Position> pos) {
	position_list.push_back(pos);

	logger::log("Contoller", "Added Position", pos->toString(), "Position To Move To");
}

void Controller::addBehaviour(Behaviour* beh) {
	coms::behaviour_list_current.push_back(beh);

	logger::log("Contoller", "Added Behaviour", beh->toString(), "Behaviour Execute Afterward");
}

/**
 Splits up the movements and executes of them
 @return The status
*/
Status* Controller::execute() {
	serial::position_lock.lock();
	std::vector<std::shared_ptr<Position>>::iterator itr_pos = position_list.begin(); 
	while(itr_pos < position_list.end()){
		serial::positions_to_send.push_back(*itr_pos);
		itr_pos = position_list.erase(itr_pos);
	}
	serial::position_lock.unlock();
	logger::log("Controller Sent Positions to SerialProcessor");
	return status.setSuccess();
}

void Controller::clear() {
	std::vector<std::shared_ptr<Position>>::iterator itr_pos = position_list.begin();
	while(itr_pos < position_list.end()) {
		itr_pos = position_list.erase(itr_pos);
	}

	
	std::vector<Behaviour*>::iterator itr_beh = coms::behaviour_list_current.begin();
	while(itr_beh < coms::behaviour_list_current.end()) {
		itr_beh = coms::behaviour_list_current.erase(itr_beh);
	}

	itr_beh = coms::behaviour_list_execute.begin();
	while(itr_beh < coms::behaviour_list_execute.end()) {
		itr_beh = coms::behaviour_list_execute.erase(itr_beh);
	}

	coms::behaviour_list_execute.push_back(&nodes::bt);

	logger::log("Controller All Positions and Behaviours Cleared");
}
