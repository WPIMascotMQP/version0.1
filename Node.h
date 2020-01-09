/**
 @file Node.h
 @class Node
 @brief The interface class holds all of the shared global classes
 across all nodes as well as basic node functionality

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Status.h"

class Calculator;
class Controller;
class SensorData;

class Node {
public:
	Node();
	~Node();

	virtual Status* executeC();
	virtual Status* executeP(Status* stat);
	void setParent(Node *par);
	void verbose(std::string log);

	Calculator getCalculator();
	Controller getController();
	SensorData getSensorData();

	static Controller controller;
	static Calculator calculator;
	static SensorData data;

protected:
	Status status;
	Node *parent;

};

#endif
