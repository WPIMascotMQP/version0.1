#ifndef ACTIONUPRIGHT_H
#define ACTIONUPRIGHT_H

#include "Action.h"

class ActionUpRight : public Action {
public:
	ActionUpRight(int dX, int dY, int dZ);
	ActionUpRight() : ActionUpRight(0, 0, 0) {};
	~ActionUpRight();

	int execute();

protected:

};
#endif