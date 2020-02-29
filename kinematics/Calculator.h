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
	std::shared_ptr<Position> getPosition(double yaw, double pitch);

	std::shared_ptr<Position> getDeltaPosition(double yaw, double pitch);
	std::shared_ptr<Position> getDeltaPosition(double ny, double np, double hy, double hp);

	std::shared_ptr<Movement> getMovement(double yaw, double pitch, double neck_v, double head_v);

	std::shared_ptr<Movement> getDeltaMovement(double yaw, double pitch, double neck_v, double head_v);
	std::shared_ptr<Movement> getDeltaMovement(double ny, double np, double hy, double hp, double neck_v, double head_v);

	void limit(std::shared_ptr<Position> pos);
	double getNeckHeadRatio(double percent);
	void setFlipped();

protected:
	std::vector<double> flips;
};

namespace cal {
	extern Calculator calculator;
}

#endif
