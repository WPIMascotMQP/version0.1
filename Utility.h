/**
 @file Utility.h
 @class Utility
 @brief The Utility composite node class
 @details This Utility node points to children of utiltiy decorator nodes
 it then gets the score from those decorators and executes the highest scored one

 If a child returns failure, the utility node will attempt to call another child
 If all children return a priority of 0, the utliltiy node will return failure
 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <iterator>
#include <vector>

#include "Composite.h"
#include "UtilityDec.h"

class Utility : public Composite {
public:
	Utility(std::vector<UtilityDec*> childr);
	Utility() : Utility(std::vector<UtilityDec*>()) {};
	~Utility();

	int executeC();
	int executeP(int stat, UtilityDec* dec);

	void addChild(UtilityDec* chi);
	void removeChild(UtilityDec* chi);
	void clearChildren();
protected:
	std::vector<UtilityDec*> children;
	std::vector<UtilityDec*> failures;
};
#endif