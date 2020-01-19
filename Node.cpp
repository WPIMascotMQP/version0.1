#include "Node.h"

#include "kinematics/Calculator.h"
#include "Controller.h"
#include "SensorData.h"

Calculator cal_node;
Calculator Node::calculator = cal_node;
SensorData dat_node;
SensorData Node::data = dat_node;
Controller con_node;
Controller Node::controller = con_node;

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

/**
 Get the static calculator
 @return The calculator
*/
Calculator Node::getCalculator() {
	return calculator;
}

/**
 Get the static controller
 @return The controller
*/
Controller Node::getController() {
	return controller;
}

/**
 Get the static sensorData
 @return The sensorData
*/
SensorData Node::getSensorData() {
	return data;
}
