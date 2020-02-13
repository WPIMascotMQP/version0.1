#include "Position.h"

/**
 CONSTRUCTOR
 @param ny The neck yaw position
 @param np The neck pitch position
 @param hy The head yaw position
 @param hp The head pitch postiion
*/
Position::Position(double ny, double np, double hy, double hp) {
	neck_yaw = ny;
	neck_pitch = np;
	head_yaw = hy;
	head_pitch = hp;
}

/**
 DECONSTRUCTOR
*/
Position::~Position() {

}

void Position::setNeckYaw(double ny) {
	neck_yaw = ny;
}

void Position::setNeckPitch(double np) {
	neck_pitch = np;
}

void Position::setHeadYaw(double hy) {
	head_yaw = hy;
}

void Position::setHeadPitch(double hp) {
	head_pitch = hp;
}

double Position::getNeckYaw() {
	return neck_yaw;
}

double Position::getNeckPitch() {
	return neck_pitch;
}

double Position::getHeadYaw() {
	return head_yaw;
}

double Position::getHeadPitch() {
	return head_pitch;
}

std::string Position::toString() {
	char output[50];
	sprintf(output, "( %5.2f, %5.2f, %5.2f, %5.2f)",
		neck_yaw, neck_pitch, head_yaw, head_pitch);
	std::string s(output);
	return s;
}
