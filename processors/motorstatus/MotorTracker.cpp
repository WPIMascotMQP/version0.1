#include "MotorTracker.h"

namespace motortracker {
	unsigned int max_history = 50;
}

namespace math {
 	double PI = 4 * std::atan(1);
}

MotorTracker::MotorTracker() {
	minimum = 0.0;
	maximum = 0.0;
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
