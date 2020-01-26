#include "InteractionMotionUtilityDec.h"

InteractionMotionUtilityDec::InteractionMotionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionMotionUtilityDec::~InteractionMotionUtilityDec() {

}

double InteractionMotionUtilityDec::getPriority() {
	return 0.0;
}