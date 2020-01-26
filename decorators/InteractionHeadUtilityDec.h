#ifndef INTERACTIONHEADUTILITYDEC_H
#define INTERACTIONHEADUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionHeadUtilityDec : public UtilityDec {
public:
	InteractionHeadUtilityDec(Node* chi);
	InteractionHeadUtilityDec() : InteractionHeadUtilityDec(NULL) {};
	~InteractionHeadUtilityDec();

	double getPriority();
protected:

};

#endif