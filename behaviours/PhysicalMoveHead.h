#ifndef PHYSICALMOVEHEAD_H
#define PHYSICALMOVEHEAD_H

#include "../behaviourtree/Behaviour.h"

class PhysicalMoveHead : public Behaviour {
public:
	PhysicalMoveHead();
	~PhysicalMoveHead();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();

protected:

};

#endif