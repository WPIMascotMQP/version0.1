#ifndef PHYSICALUTILITYDEC_H
#define PHYSICALUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class PhysicalUtilityDec : public UtilityDec {
public:
	PhysicalUtilityDec(Node* chi);
	PhysicalUtilityDec() : PhysicalUtilityDec(NULL) {};
	~PhysicalUtilityDec();

	double getPriority();
protected:

};
#endif