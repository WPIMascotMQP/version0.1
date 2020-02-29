/**
 @file Movement.h
 @class Movement
 @brief The Movement Object that contains the position data
 @details This Movement Object defines the actual expected output movements
 of the robot with position data that informs the Controller Object on the required
 kinematic locations.

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019 16:18:30
*/

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <memory>
#include <stdlib.h>
#include <string>

#include "Position.h"

class Behaviour;

class Movement {
public:
	Movement();
	~Movement();

	void setSetPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> getSetPosition();

	void setDelay(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> getDelay();

	std::string toString();
protected:
	std::shared_ptr<Position> setPosition;
	std::shared_ptr<Position> delay;

};
#endif
