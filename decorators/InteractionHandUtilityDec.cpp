#include "InteractionHandUtilityDec.h"

InteractionHandUtilityDec::InteractionHandUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionHandUtilityDec::~InteractionHandUtilityDec() {

}

double InteractionHandUtilityDec::getPriority() {
	logger::log("InteractionHandUtiltyDec", "Priority:", 0.0, "Not Currently Implemented");
	return 0.0;
}
