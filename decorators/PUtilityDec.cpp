#include "PUtilityDec.h"

PUtilityDec::PUtilityDec(Node* chi) : UtilityDec(chi) {

}

PUtilityDec::~PUtilityDec() {

}

double PUtilityDec::getPriority() {
	return data::sensorData.getInput().find("p") != std::string::npos ? 1.0 : 0.0;
}