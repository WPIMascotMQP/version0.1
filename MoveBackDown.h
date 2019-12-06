/**
 @file MoveBackDown.h
 @class MoveBackDown
 @brief The Behaviour node for moving back down
 @details This Behaviour node holds the actions and generates the movements
 in order for the point to move back down 

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef MOVEBACKDOWN_H
#define MOVEBACKDOWN_H

#include "Behaviour.h"

class MoveBackDown : public Behaviour {
public:
	MoveBackDown();
	~MoveBackDown();

	int executeC();
	int executeP(int stat);
	std::vector<Movement*> generateMovements();

protected:

};
#endif