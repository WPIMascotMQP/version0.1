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

void Position::setHead0(double h0) {
	setHeadYaw(h0);
}

void Position::setHead1(double h1) {
	setHeadPitch(h1);
}

void Position::setAtIndex(int index, double value) {
	switch(index) {
		case 0:
			setNeckYaw(value);
			break;
		case 1:
			setNeckPitch(value);
			break;
		case 2:
			setHeadYaw(value);
			break;
		case 3:
			setHeadPitch(value);
			break;
	}
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

double Position::getHead0() {
	return head_yaw;
}

double Position::getHead1() {
	return head_pitch;
}

double Position::getAtIndex(int index) {
	switch(index) {
		case 0:
			return getNeckYaw();
		case 1:
			return getNeckPitch();
		case 2:
			return getHeadYaw();
		case 3:
			return getHeadPitch();
		default:
			return 0.0;
	}
}

std::string Position::toString() {
	char output[100];
	sprintf(output, "( %5.2f, %5.2f, %5.2f, %5.2f)",
		neck_yaw, neck_pitch, head_yaw, head_pitch);
	std::string s(output);
	return s;
}
