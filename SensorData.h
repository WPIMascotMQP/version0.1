/**
 @file SensorData.h
 @class SensorData
 @brief The SensorData class holds all sensor and joint data
 @details This SensorData functions as a data object holding on to
 all relavent sensor and positial data

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <string>

#include "Position.h"

class SensorData {
public:
	SensorData(double cX, double cY, double cZ);
	SensorData() : SensorData(0.0, 0.0, 0.0) {};
	~SensorData();

	std::string getInput();
	Position* getCurrentPosition();

	void setInput(std::string inp);
	void setCurrentPosition(Position* pos);

protected:
	static std::string input;
	static Position currentPosition;

};
#endif