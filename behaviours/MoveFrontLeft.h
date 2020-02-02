/**
 @file MoveFrontLeft.h
 @class MoveFrontLeft
 @brief The Behaviour node for moving foward and left
 @details This Behaviour node holds the actions and generates the movements
 in order for the point to move foward and left

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef MOVEFRONTLEFT_H
#define MOVEFRONTLEFT_H

#include "../behaviourtree/Behaviour.h"

class MoveFrontLeft : public Behaviour {
public:
	MoveFrontLeft();
	~MoveFrontLeft();

	Status* executeC();
  	Status* executeP(Status* stat);

protected:

};
#endif
