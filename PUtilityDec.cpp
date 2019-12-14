#include "PUtilityDec.h"

#include "SensorData.h"

PUtilityDec::PUtilityDec(Node* chi) : UtilityDec(chi) {

}

PUtilityDec::~PUtilityDec() {

}

double PUtilityDec::getPriority() {
	return getSensorData().getInput().find("p") != std::string::npos ? 1.0 : 0.0;
}