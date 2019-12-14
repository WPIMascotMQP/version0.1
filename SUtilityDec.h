/**
 @file SUtilityDec.h
 @class SUtilityDec
 @brief The SUtilityDec Decorator node class
 @details This Decorator node class will calculate a score based
 on if the letter S was inputed

 @author Jonathan Chang
 @version 0.0.1
 @date 07/12/2019
*/

#ifndef SUTILITYDEC_H
#define SUTILITYDEC_H

#include "Node.h"
#include "UtilityDec.h"

class SUtilityDec : public UtilityDec {
public:
	SUtilityDec(Node* chi);
	SUtilityDec() : SUtilityDec(&Node()) {};
	~SUtilityDec();

	double getPriority();

protected:
	
};
#endif