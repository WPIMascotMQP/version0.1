#include "InteractionMotionUtilityDec.h"

InteractionMotionUtilityDec::InteractionMotionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionMotionUtilityDec::~InteractionMotionUtilityDec() {

}

double InteractionMotionUtilityDec::getPriority() {
	logger::log("InteractionMotionUtilityDec Priority: 0.3 - Steady Minimum");
	return 0.3;
}
