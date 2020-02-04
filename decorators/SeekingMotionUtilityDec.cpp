#include "SeekingMotionUtilityDec.h"

SeekingMotionUtilityDec::SeekingMotionUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingMotionUtilityDec::~SeekingMotionUtilityDec() {

}

double SeekingMotionUtilityDec::getPriority() {
	std::ostringstream strs;
	strs << "SeekingMotionUtilityDec Priority: 0.3 - Steady Minimum";
	logger::log(strs.str());
	
	return 0.3;
}
