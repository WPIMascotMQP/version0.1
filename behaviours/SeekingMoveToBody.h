#ifndef SEEKINGMOVETOBODY_H
#define SEEKINGMOVETOBODY_H

#include "../behaviourtree/Behaviour.h"

class SeekingMoveToBody : public Behaviour {
public:
	SeekingMoveToBody();
	~SeekingMoveToBody();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();

protected:

};

#endif