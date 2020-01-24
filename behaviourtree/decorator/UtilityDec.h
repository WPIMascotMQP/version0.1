/**
 @file UtilityDec.h
 @class UtilityDec
 @brief The UtilityDec Decorator node class
 @details This Decorator node class will calculate and return a score
 on wheather to execute the beahviour under it or not

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef UTILITYDEC_H
#define UTILITYDEC_H

#include "Decorator.h"

class Utility;
class UtilityDec : public Decorator {
public:
	UtilityDec(Node *chi);
	UtilityDec() : UtilityDec(NULL) {};
	~UtilityDec();

	virtual double getPriority();
	Status* executeP(Status* stat);
	void setParent(Utility* par);

protected:
	Utility* parent;
};
#endif
