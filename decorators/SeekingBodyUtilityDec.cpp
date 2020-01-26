#include "SeekingBodyUtilityDec.h"

SeekingBodyUtilityDec::SeekingBodyUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingBodyUtilityDec::~SeekingBodyUtilityDec() {

}

double SeekingBodyUtilityDec::getPriority() {
	return 0.0;
}