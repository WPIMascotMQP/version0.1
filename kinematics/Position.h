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
	Position(double ny, double np, double hy, double hp);
	Position(Position* pos) : Position(pos->neck_yaw, pos->neck_pitch,
			pos->head_yaw, pos->head_pitch) {};
	Position() : Position(0.0, 0.0, 0.0, 0.0) {};
	~Position();

	double neck_yaw;
	double neck_pitch;
	double head_yaw;
	double head_pitch;

	bool operator==(const Position& pos2) {
		return (neck_yaw == pos2.neck_yaw) &&
			(neck_pitch == pos2.neck_pitch) &&
			(head_yaw == pos2.head_yaw) &&
			(head_pitch == pos2.head_pitch);
	};

	friend std::ostream& operator<< (std::ostream& out, Position& pos) {
		char output[50];
		sprintf(output, "( %5.2f, %5.2f, %5.2f, %5.2f)",
			pos.neck_yaw, pos.neck_pitch, pos.head_yaw, pos.head_pitch);
		out << output;
		return out;
	}
private:

};
#endif
