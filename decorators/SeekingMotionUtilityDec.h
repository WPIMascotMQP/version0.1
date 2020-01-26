#ifndef SEEKINGMOTIONUTILITYDEC_H
#define SEEKINGMOTIONUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class SeekingMotionUtilityDec : public UtilityDec {
public:
	SeekingMotionUtilityDec(Node* chi);
	SeekingMotionUtilityDec() : SeekingMotionUtilityDec(NULL) {};
	~SeekingMotionUtilityDec();

	double getPriority();
protected:

};

#endif