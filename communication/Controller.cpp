#include "Controller.h"

#include "../behaviourtree/Behaviour.h"
#include "../behaviourtree/Node.h"

namespace coms {
	Controller controller(0);
	std::vector<Behaviour*> current_behaviours;
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

void Controller::addBehaviour(std::shared_ptr<Behaviour> beh) {
	behaviour_list.push_back(beh);

	logger::log("Contoller", "Added Behaviour", beh->toString(), "Behaviour Execute Afterward");
}

/**
 Splits up the movements and executes of them
 @return The status
*/
Status* Controller::execute() {
	logger::log("Controller Sending Positions to SerialProcessor");
	// Send to SerialProcessor
	return status.setSuccess();
}

void Controller::clear() {
	std::vector<std::shared_ptr<Position>>::iterator itr_pos = position_list.begin();
	while(itr_pos < position_list.end()) {
		itr_pos = position_list.erase(itr_pos);
	}

	std::cout << "Cleared Positions" << std::endl;
	std::vector<std::shared_ptr<Behaviour>>::iterator itr_beh = behaviour_list.begin();
	while(itr_beh < behaviour_list.end()) {
		itr_beh = behaviour_list.erase(itr_beh);
	}
	logger::log("Controller All Positions and Behaviours Cleared");
}
