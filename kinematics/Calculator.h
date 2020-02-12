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
#include "../behaviourtree/Behaviour.h"
#include "../SensorData.h"
#include "Movement.h"

class Behaviour;
class Movement;

class Calculator {
public:
	Calculator(int start_int);
	Calculator() : Calculator(0){};
	~Calculator();

	//std::vector<Movement*> *generateMovements(std::vector<Action*> actions, Behaviour *beh);
	Position* getPosition(double yaw, double pitch);

	Position* getDeltaPosition(double yaw, double pitch);
	Position* getDeltaPosition(double ny, double np, double hy, double hp);

	double getNeckHeadRatio(double percent);
protected:

};

namespace cal {
	extern Calculator calculator;
}

#endif
