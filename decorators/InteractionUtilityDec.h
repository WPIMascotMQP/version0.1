#ifndef INTERACTIONUTILITYDEC_H
#define INTERACTIONUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionUtilityDec : public UtilityDec {
public:
	InteractionUtilityDec(Node* chi);
	InteractionUtilityDec() : InteractionUtilityDec(NULL) {};
	~InteractionUtilityDec();

	double getPriority();
protected:

};

#endif