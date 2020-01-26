#include "InteractionUtilityDec.h"

InteractionUtilityDec::InteractionUtilityDec(Node* chi) : UtilityDec(chi) {

}

InteractionUtilityDec::~InteractionUtilityDec() {

}

double InteractionUtilityDec::getPriority() {
	return 0.0;
}