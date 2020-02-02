/**
 @file Composite.h
 @class Composite
 @brief The interface for composite nodes
 @details This interface node holds the basic functionality of composite nodes
 by adding, removing, and otherwise handling children

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iterator>
#include <vector>

#include "../Node.h"

class Composite : public Node {
public:
	Composite(std::vector<Node*> childr);
	Composite() : Composite(std::vector<Node*>()) {};
	~Composite();

	virtual Status* executeC();
	virtual Status* executeP(Status* stat);
	void addChild(Node *chi);
	void removeChild(Node *chi);
	void clearChildren();

	friend Composite& operator<< (Composite& cp, Node& node) {
		cp.addChild(&node);
		return cp;
	}
protected:
	std::vector<Node*> children;

};
#endif
