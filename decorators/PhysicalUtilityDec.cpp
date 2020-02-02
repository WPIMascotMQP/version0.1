#include "PhysicalUtilityDec.h"

PhysicalUtilityDec::PhysicalUtilityDec(Node* chi) : UtilityDec(chi) {

}

PhysicalUtilityDec::~PhysicalUtilityDec() {

}

double PhysicalUtilityDec::getPriority() {
	return data::sensorData.getTouched() ? 1.0 : 0.0;
}