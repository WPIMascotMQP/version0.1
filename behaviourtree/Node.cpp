#include "Node.h"

/**
 CONSTRUCTOR
*/
Node::Node() {
	status.setSuccess();
}

/**
 DECONSTRCUTOR
*/
Node::~Node() {

}

/**
  Node execute as child function
  @return the status
*/
Status* Node::executeC() {
	return status.setSuccess();
}

/**
  Node execute as parent
  @param The status of the child executing this parent
  @return the status
*/
Status* Node::executeP(Status* stat) {
	return status.setSuccess();
}

/**
 Sets the parent
 @param par The parent
*/
void Node::setParent(Node* par) {
	parent = par;
}

/**
 Debug verbose print out
 @param log The string to print
*/
void Node::verbose(std::string log) {
	std::cout << log << std::endl;
}
