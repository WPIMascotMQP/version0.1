#ifndef SEEKINGUTILITYDEC_H
#define SEEKINGUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class SeekingUtilityDec : public UtilityDec {
public:
	SeekingUtilityDec(Node* chi);
	SeekingUtilityDec() : SeekingUtilityDec(NULL) {};
	~SeekingUtilityDec();

	double getPriority();
protected:

};

#endif