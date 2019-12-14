#include "BehaviourTree.h"

/**
 CONSTRUCTOR
 @param nod The root node
*/
BehaviourTree::BehaviourTree(Node *nod) {
	root = nod;
}

/**
 DECONSTRUCTOR
*/
BehaviourTree::~BehaviourTree() {

}

/**
 Behaviour Tree Execute
 @return The status
*/
int BehaviourTree::execute() {
	return executeP(status::success);
}

/**
 Behaviour Tree Execute
 @return The status
*/
int BehaviourTree::executeC() {
	return executeP(status::success);
}

/**
 Behaviour Tree Execute
 @return The status
*/
int BehaviourTree::executeP(int stat) {
	std::cout << "Call Beahviour Tree Root" << std::endl;
	return root->executeC();
}

/**
 Sets the root node
 @param node The root node
*/
void BehaviourTree::setRoot(Node *nod) {
	root = nod;
	root->setParent(this);
}