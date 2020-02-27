#include "MotorTracker.h"

namespace motortracker {
	unsigned int max_history = 50;
}

namespace math {
 	double PI = 4.0 * std::atan(1);
}

MotorTracker::MotorTracker() {
	minimum = 0.0;
	maximum = 0.0;
	neutral = 0.0;
	neutral_physical = 0.0;
	maximum_physical = 0.0;
	ratio = 0.0; // Motor Rad to Physical Rad
	addStepsHistory(0);
}

MotorTracker::~MotorTracker() {

}

bool MotorTracker::EStop() {
	return false;
}

void MotorTracker::add(int steps, double current, double temperature, double position) {
	addStepsHistory(steps);
	addToHistory(temperature_history, temperature);
	addToHistory(position_history, position);
}

void MotorTracker::addStepsHistory(int steps) {
	steps_history.push_back(steps);
	std::vector<int>::iterator itr = steps_history.begin();
	while(steps_history.size() > motortracker::max_history) {
		itr = steps_history.erase(itr);
	}
}

void MotorTracker::addToHistory(std::vector<double> history, double info) {
	history.push_back(info);
	std::vector<double>::iterator itr = history.begin();
	while(history.size() > motortracker::max_history) {
		itr = history.erase(itr);
	}
}

int MotorTracker::getCurrentSteps() {
	return steps_history.back();
}

void MotorTracker::setMinimum(int min) {
	minimum = min;
}

void MotorTracker::setNeutral(int neu) {
	neutral = neu;
}

void MotorTracker::setMaximum(int max) {
	maximum = max;
}

void MotorTracker::setNeutralPhysical(double neu_phy) {
	neutral_physical = neu_phy;
}

void MotorTracker::setMaximumPhysical(double max_phy) {
	maximum_physical = max_phy;
}

void MotorTracker::setRatio(double rat) {
	ratio = rat;
}

void MotorTracker::setFlipped(bool flip) {
	flipped = flip;
}

int MotorTracker::getMinimum() {
	return minimum;
}

int MotorTracker::getNeutral() {
	return neutral;
}

int MotorTracker::getMaximum() {
	return maximum;
}

double MotorTracker::getNeutralPhysical() {
	return neutral_physical;
}

double MotorTracker::getMaximumPhysical() {
	return maximum_physical;
}

double MotorTracker::getRatio() {
	return ratio;
}

bool MotorTracker::getFlipped() {
	return flipped;
}

std::string MotorTracker::toString() {
	char output[100];
	char flip[10];
	if(flipped) {
		strcpy(flip, "True");
	} else {
		strcpy(flip, "False");
	}
	sprintf(output, "( %5.2d, %5.2d, %5.2d, %5.2f, %5.2f, %5.2f, %s)",
		minimum, neutral, maximum, neutral_physical, maximum_physical, ratio, flip);
	std::string s(output);
	return s;
}
