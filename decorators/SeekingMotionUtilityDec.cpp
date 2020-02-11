#include "SeekingMotionUtilityDec.h"

SeekingMotionUtilityDec::SeekingMotionUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingMotionUtilityDec::~SeekingMotionUtilityDec() {

}

double SeekingMotionUtilityDec::getPriority() {
	logger::log("SeekingMotionUtilityDec", "Priority:", 0.3, "Stead Minimum");

	return 0.3;
}
