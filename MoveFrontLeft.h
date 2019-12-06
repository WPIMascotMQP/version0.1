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

#include "Behaviour.h"

class MoveFrontLeft : public Behaviour {
public:
	MoveFrontLeft();
	~MoveFrontLeft();

	int executeC();
	int executeP(int stat);
	std::vector<Movement*> generateMovements();

protected:

};
#endif