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
void Controller::addPosition(Position* pos) {
	position_list.push_back(pos);

	std::ostringstream strs;
	strs << "Controller Added Position: " << *pos;
	logger::log(strs.str());
}

void Controller::addBehaviour(Behaviour* beh) {
	behaviour_list.push_back(beh);
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
