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
}

MotorTracker::~MotorTracker() {

}

bool MotorTracker::EStop() {
	return false;
}

void MotorTracker::add(double current, double temperature, double position) {
	addToHistory(current_history, current);
	addToHistory(temperature_history, temperature);
	addToHistory(position_history, position);
}

void MotorTracker::addToHistory(std::vector<double> history, double info) {
	history.push_back(info);
	std::vector<double>::iterator itr = history.begin();
	while(history.size() > motortracker::max_history) {
		itr = history.erase(itr);
	}
}

void MotorTracker::setMinimum(double min) {
	minimum = min;
}

void MotorTracker::setNeutral(double neu) {
	neutral = neu;
}

void MotorTracker::setMaximum(double max) {
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

double MotorTracker::getMinimum() {
	return minimum;
}

double MotorTracker::getNeutral() {
	return neutral;
}

double MotorTracker::getMaximum() {
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

std::string MotorTracker::toString() {
	char output[100];
	sprintf(output, "( %5.2f, %5.2f, %5.2f, %5.2f, %5.2f, %5.2f)",
		minimum, neutral, maximum, neutral_physical, maximum_physical, ratio);
	std::string s(output);
	return s;
}
