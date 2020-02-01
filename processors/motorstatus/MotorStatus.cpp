#include "MotorStatus.h"

namespace motorstatus {
	unsigned int max_history = 50;
}

MotorStatus::MotorStatus() {

}

MotorStatus::~MotorStatus() {

}

bool MotorStatus::EStop() {
	return false;
}

void MotorStatus::add(double current, double temperature, double position) {
	addToHistory(current_history, current);
	addToHistory(temperature_history, temperature);
	addToHistory(position_history, position);
}

void MotorStatus::addToHistory(std::vector<double> history, double info) {
	history.push_back(info);
	std::vector<double>::iterator itr = history.begin();
	while(history.size() > motorstatus::max_history) {
		itr = history.erase(itr);
	}
}