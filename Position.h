/**
 @file Positon.h
 @class Position
 @brief The Position Object that defines the kinematic location of the robot
 @details This Position Object defines the required kinematic location of robot
 in both a 3D space as well as intended encoder values

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019 16:18:30 
*/

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Position {

public:
	Position(double x, double y, double z);
	Position() : Position(0.0, 0.0, 0.0) {};
	~Position();

	void setXPosition(double x);
	void setYPosition(double y);
	void setZPosition(double z);
	double getXPosition();
	double getYPosition();
	double getZPosition();

	bool operator==(const Position& pos2) {
		return (x_position == pos2.x_position) &&
			(y_position == pos2.y_position) &&
			(z_position == pos2.z_position);
	};

	friend std::ostream& operator<< (std::ostream& out, Position& pos) {
		char output[50];
		sprintf_s(output, "( %5.2f, %5.2f, %5.2f)", pos.getXPosition(), pos.getYPosition(), pos.getZPosition());
		out << output;
		return out;
	}
private:
	double x_position;
	double y_position;
	double z_position;
};
#endif