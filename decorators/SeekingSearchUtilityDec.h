#ifndef SEEKINGSEARCHUTILITYDEC_H
#define SEEKINGSEARCHUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class SeekingSearchUtilityDec : public UtilityDec {
public:
	SeekingSearchUtilityDec(Node* chi);
	SeekingSearchUtilityDec() : SeekingSearchUtilityDec(NULL) {};
	~SeekingSearchUtilityDec();

	double getPriority();
protected:

};

#endif