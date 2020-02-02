#include "SUtilityDec.h"

SUtilityDec::SUtilityDec(Node* chi) : UtilityDec(chi) {

}

SUtilityDec::~SUtilityDec() {

}

double SUtilityDec::getPriority() {
	return data::sensorData.getInput().find("s") != std::string::npos ? 1.0 : 0.1;
}