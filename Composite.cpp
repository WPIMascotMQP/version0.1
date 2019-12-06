#include "Composite.h"

/**
 CONSTRUCTOR
 @param childr The list of children
 @return The Composite Object
*/
Composite::Composite(std::vector<Node*> childr) {
	children = childr;
}

/**
 DECONSTRUCTOR
*/
Composite::~Composite() {
	clearChildren();
}

/**
 Empty execute function to be overwritten in child classes
*/
int Composite::executeC() {
	return status::success;
}

/**
 Empty execute function to be overwritten in child classes
*/
int Composite::executeP(int stat) {
	return stat;
}

/**
 Adds a child to the children list
 @param chi The child to add
*/
void Composite::addChild(Node *chi) {
	children.push_back(chi);
}

/**
 Removes the child from the children list
 @param chi The child to remove
*/
void Composite::removeChild(Node *chi) {
	std::vector<Node*>::iterator itr;
	for (itr = children.begin(); itr < children.end(); itr++) {
		if (chi == *itr) {
			children.erase(itr);
		}
	}
}

/**
 Removes all children
*/
void Composite::clearChildren() {
	children.clear();
}