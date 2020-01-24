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
Status* BehaviourTree::execute() {
	return executeP(NULL);
}

/**
 Behaviour Tree Execute
 @return The status
*/
Status* BehaviourTree::executeC() {
	return executeP(NULL);
}

/**
 Behaviour Tree Execute
 @return The status
*/
Status* BehaviourTree::executeP(Status* stat) {
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
