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
status BehaviourTree::execute() {
	return executeP(success);
}

/**
 Behaviour Tree Execute
 @return The status
*/
status BehaviourTree::executeC() {
	return executeP(success);
}

/**
 Behaviour Tree Execute
 @return The status
*/status BehaviourTree::executeP(status stat) {
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
