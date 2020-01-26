#ifndef INTERACTIONMOTIONUTILITYDEC_H
#define INTERACTIONMOTIONUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionMotionUtilityDec : public UtilityDec {
public:
	InteractionMotionUtilityDec(Node* chi);
	InteractionMotionUtilityDec() : InteractionMotionUtilityDec(NULL) {};
	~InteractionMotionUtilityDec();

	double getPriority();
protected:

};

#endif