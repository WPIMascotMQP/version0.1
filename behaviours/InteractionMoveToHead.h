#ifndef INTERACTIONMOVETOHEAD_H
#define INTERACTIONMOVETOHEAD_H

#include "../behaviourtree/Behaviour.h"

class InteractionMoveToHead : public Behaviour {
public:
	InteractionMoveToHead();
	~InteractionMoveToHead();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();
protected:

};
#endif