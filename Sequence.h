/**
 @file Sequence.h
 @class Sequence
 @brief The Sequence composite node class
 @details This Sequence class holds the execution function
 to execute its children in sequence from first to last

 If a child returns failure, the sequence node immedately calls it parent
 and resets

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iterator>
#include <vector>

#include "Composite.h"

class Sequence : public Composite {
public:
	Sequence(std::vector<Node*> childr);
	Sequence() : Sequence(std::vector<Node*>()) {};
	~Sequence();

	int executeC();
	int executeP(int stat);
	void reset();

protected:
	std::vector<Node*>::iterator currentChild;

};
#endif