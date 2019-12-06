/**
 @file Decorator.h
 @class Decorator
 @brief The interface for Decorator nodes
 @details This interface node holds the basic functionality of decorator nodes
 which includes setting and executing its children 

 @author Jonathan Chang
 @version 0.0.1
 @date 03/12/2019
*/

#ifndef DECORATOR_H
#define DECORATOR_H

#include "Node.h"

class Decorator : public Node {
public:
	Decorator(Node *chi);
	Decorator() : Decorator(&Node()) {};
	~Decorator();

	int executeC();
	int executeP(int stat);
	void setChild(Node *chi);

protected:
	Node* child;
};
#endif