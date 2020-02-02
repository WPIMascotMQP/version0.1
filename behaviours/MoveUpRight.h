/**
 @file MoveUpRight.h
 @class MoveUpRight
 @brief The Behaviour node for moving up and right
 @details This Behaviour node holds the actions and generates the movements
 in order for the point to move up and right

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef MOVEUPRIGHT_H
#define MOVEUPRIGHT_H

#include "../behaviourtree/Behaviour.h"

class MoveUpRight : public Behaviour {
public:
	MoveUpRight();
	~MoveUpRight();

	Status* executeC();
	Status* executeP(Status* stat);

protected:

};
#endif
