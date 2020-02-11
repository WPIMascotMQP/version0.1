/**
 @file Parallel.h
 @class Parallel
 @brief The Parallel composite node class
 @details This Parallel class holds the parallel execution function
 which allows it to execute multiple children at once

 If a child returns failure, the parallel node will return failure after
 all child return

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef PARALLEL_H
#define PARALLEL_H

#include "Composite.h"

class Parallel : public Composite {
public:
	Parallel(std::vector<Node*> childr);
	Parallel() : Parallel(std::vector<Node*>()) {};
	~Parallel();

	Status* executeC();
	Status* executeP(Status* stat);
	void reset();

	friend Parallel& operator<< (Parallel& pl, Node& node) {
		pl.addChild(&node);
		return pl;
	}

protected:
	Status status;
	Status* returnedStatus;
	Status* returnedStatuses;
	Status successStatus;

private:
	unsigned int returedExecutes;
};
#endif
