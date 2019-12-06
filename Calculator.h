/**
 @file Calculator.h
 @class Calculator
 @brief The Calculator class figures out the movements
 @details This Calcualtor class takes in the expected actions as well as the 
 current positiion and generates movements to based on those actions.

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Action.h"
#include "Behaviour.h"
#include "SensorData.h"
#include "Movement.h"

class Calculator {
public:
	Calculator();
	~Calculator();

	std::vector<Movement*> *generateMovements(std::vector<Action*> actions, Behaviour *beh);

protected:
	static SensorData data;
};
#endif