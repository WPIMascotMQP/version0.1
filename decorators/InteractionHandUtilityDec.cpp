#include "InteractionHandUtilityDec.h"

InteractionHandUtilityDec::InteractionHandUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionHandUtilityDec::~InteractionHandUtilityDec() {

}

double InteractionHandUtilityDec::getPriority() {
	return 0.0;
}