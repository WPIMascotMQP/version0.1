/**
 @file PUtilityDec.h
 @class PUtilityDec
 @brief The PUtilityDec Decorator node class
 @details This Decorator node class will calculate a score based
 on if the letter P was inputed

 @author Jonathan Chang
 @version 0.0.1
 @date 07/12/2019
*/

#ifndef PUTILITYDEC_H
#define PUTILITYDEC_H

#include "Node.h"
#include "UtilityDec.h"

class PUtilityDec : public UtilityDec {
public:
	PUtilityDec(Node* chi);
	PUtilityDec() : PUtilityDec(&Node()) {};
	~PUtilityDec();

	double getPriority();

protected:

};
#endif