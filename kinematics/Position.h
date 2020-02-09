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
	Position(double by, double bp, double ny, double np);
	Position() : Position(0.0, 0.0, 0.0, 0.0) {};
	~Position();

	double base_yaw;
	double base_pitch;
	double neck_yaw;
	double neck_pitch;

	bool operator==(const Position& pos2) {
		return (base_yaw == pos2.base_yaw) &&
			(base_pitch == pos2.base_pitch) &&
			(neck_yaw == pos2.neck_yaw) &&
			(neck_pitch == pos2.neck_pitch);
	};

	friend std::ostream& operator<< (std::ostream& out, Position& pos) {
		char output[50];
		sprintf(output, "( %5.2f, %5.2f, %5.2f, %5.2f)",
			pos.base_yaw, pos.base_pitch, pos.neck_yaw, pos.neck_pitch);
		out << output;
		return out;
	}
private:

};
#endif
