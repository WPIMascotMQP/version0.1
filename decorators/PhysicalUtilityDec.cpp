#include "PhysicalUtilityDec.h"

PhysicalUtilityDec::PhysicalUtilityDec(Node* chi) : UtilityDec(chi) {

}

PhysicalUtilityDec::~PhysicalUtilityDec() {

}

double PhysicalUtilityDec::getPriority() {
	// If being touched, return 1
	double priority = data::sensor_data.getTouched() ? 1.0 : 0.0;

	logger::log("PhysicalUtilityDec", "Priority:", priority, "1 if touched, else 0");

	return priority;
}
