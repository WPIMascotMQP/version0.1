#ifndef MOVE_H
#define MOVE_H

#include "../behaviourtree/Behaviour.h"

class Move : public Behaviour {
public:
	Move();
	~Move();

	Status* executeC();
	Status* executeP(Status* stat);

protected:

};

#endif