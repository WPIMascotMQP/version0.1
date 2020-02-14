#ifndef SEEKINGMOVESEARCH_H
#define SEEKINGMOVESEARCH_H

#include "../behaviourtree/Behaviour.h"

class SeekingMoveSearch : public Behaviour {
public:
	SeekingMoveSearch();
	~SeekingMoveSearch();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();

protected:


};

#endif
