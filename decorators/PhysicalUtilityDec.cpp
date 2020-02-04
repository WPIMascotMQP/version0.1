#include "PhysicalUtilityDec.h"

PhysicalUtilityDec::PhysicalUtilityDec(Node* chi) : UtilityDec(chi) {

}

PhysicalUtilityDec::~PhysicalUtilityDec() {

}

double PhysicalUtilityDec::getPriority() {
	// If being touched, return 1
	double priority = data::sensorData.getTouched() ? 1.0 : 0.0;

	std::ostringstream strs;
	strs << "PhysicalUtilityDec Priority: " << priority;
	logger::log(strs.str());

	return priority;
}
