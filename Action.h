/**
 @file Action.h
 @class Action
 @brief The Action object that defines an expected movement in a behaviour
 @details This Action object defines a single actions that a particular behaviour
 should exhibit without the necessary position data.

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef ACTION_H
#define ACTION_H

#include <stdlib.h>
#include "Position.h"

class Action {
public:
	Action(double dX, double dY, double dZ);
	Action() : Action(0.0, 0.0, 0.0) {};
	~Action();

	double getDeltaX();
	double getDeltaY();
	double getDeltaZ();

protected:
	double deltaX;
	double deltaY;
	double deltaZ;
};
#endif