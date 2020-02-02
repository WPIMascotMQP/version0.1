#ifndef SEEKINGMOVETOBODY_H
#define SEEKINGMOVETOBODY_H

#include "../behaviourtree/Behaviour.h"

class SeekingMoveToBody : public Behaviour {
public:
	SeekingMoveToBody();
	~SeekingMoveToBody();

	Status* executeC();
	Status* executeP(Status* stat);

protected:

};

#endif