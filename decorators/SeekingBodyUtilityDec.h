#ifndef SEEKINGBODYUTILITYDEC_H
#define SEEKINGBODYUTILITYDEC_H

#include <cmath>

#include "../behaviourtree/decorator/UtilityDec.h"

class SeekingBodyUtilityDec : public UtilityDec {
public:
	SeekingBodyUtilityDec(Node* chi);
	SeekingBodyUtilityDec() : SeekingBodyUtilityDec(NULL) {};
	~SeekingBodyUtilityDec();

	double getPriority();
protected:

};

#endif
