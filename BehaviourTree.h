/**
 @file BehaviourTree.h
 @class BehaviourTree
 @brief The encompassing BehaviourTree Object manages the behaviour tree
 @details This Behaviour Tree Object manages the beahviour tree as a whole
 it keeps hold of the currently executing nodes, the root node, and

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/
#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H
#include <vector>

#include "Behaviour.h"

class BehaviourTree : public Behaviour{

public:
	BehaviourTree(Node *nod);
	BehaviourTree() : BehaviourTree(NULL) {};
	~BehaviourTree();

	status execute();
	status executeC();
	status executeP(status stat);

	void setRoot(Node *nod);
private:
	Node *root;
};

#endif
