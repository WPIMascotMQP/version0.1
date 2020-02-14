#ifndef INTERACTIONMOVETOHAND_H
#define INTERACTIONMOVETOHAND_H

#include "../behaviourtree/Behaviour.h"

class InteractionMoveToHand : public Behaviour {
public:
	InteractionMoveToHand();
	~InteractionMoveToHand();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();
protected:

};
#endif