/**
 @file Controller.h
 @class Controller
 @brief The Controller class breaks ups movements and send commands
 @details This Controller class recieves a list of movements to execute
 and generates commands within parameters for the point to fulfill those
 movements

 @author Jonathan Chang
 @version 0.0.2
 @date 18/02/2020
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "../behaviourtree/Node.h"
#include "../kinematics/Movement.h"
#include "../kinematics/Position.h"
#include "../SensorData.h"
#include "../Status.h"

class Behaviour;
class Controller {
public:
	Controller(int start_int);
	Controller() : Controller(0){};
	~Controller();

	void addPosition(std::shared_ptr<Position> pos);
	void addMovement(std::shared_ptr<Movement> mov);
	void addBehaviour(Behaviour* beh);

	Status* execute();

	void clear();
protected:
	std::vector<std::shared_ptr<Position>> position_list;
	std::vector<std::shared_ptr<Movement>> movement_list;
	Status status;

};

namespace coms {
	extern Controller controller;
	extern std::vector<Behaviour*> behaviour_list_current; // Behaviours that produced commands
	extern std::vector<Behaviour*> behaviour_list_execute; // Behaviours to execute
}
#endif
