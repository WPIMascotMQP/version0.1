#include "PhysicalUtilityDec.h"

PhysicalUtilityDec::PhysicalUtilityDec(Node* chi) : UtilityDec(chi) {

}

PhysicalUtilityDec::~PhysicalUtilityDec() {

}

double PhysicalUtilityDec::getPriority() {
	return 0.0;
}