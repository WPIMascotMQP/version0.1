/**
 @file Behaviour.h
 @class Behaviour
 @brief The encompassing Behaviour object that generates outputed movements
 @details This Behaviour object defines one part of the behaviour that the robot can execute.
 Namely this is the overall beahviour that is able to be scored, generate a list of
 movements for the robot based on sensor data, and passes that information to the master
 control loop.

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include "Node.h"
#include "../kinematics/Action.h"
#include "../kinematics/Calculator.h"
#include "../communication/Controller.h"
#include "../SensorData.h"

class Behaviour : public Node {
public:
	Behaviour();
    ~Behaviour();

	virtual Status* executeC();
	virtual Status* executeP(Status* stat);
	void end();

	virtual std::string toString();

protected:
	std::vector<Action*> actions;

};
#endif
