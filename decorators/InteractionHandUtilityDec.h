#ifndef INTERACTIONHANDUTILITYDEC_H
#define INTERACTIONHANDUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionHandUtilityDec : public UtilityDec {
public:
	InteractionHandUtilityDec(Node* chi);
	InteractionHandUtilityDec() : InteractionHandUtilityDec(NULL) {};
	~InteractionHandUtilityDec();

	double getPriority();
protected:

};

#endif