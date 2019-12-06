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

#include <stdlib.h>

#include "Behaviour.h"
#include "Position.h"

class Movement {

public:
	Movement();
	~Movement();

	void setSetPoint(Position *pos);
	Position *getSetPoint();

	void setCurrentPoint(Position *pos);
	Position *getCurrentPoint();

	void setBehaviour(Behaviour *beh);
	Behaviour* getBehaviour();

protected:
	Position *setPoint;
	Position *currentPoint;
	Behaviour *behaviour;
};
#endif