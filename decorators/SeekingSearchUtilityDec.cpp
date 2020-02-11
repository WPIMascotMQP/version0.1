#include "SeekingSearchUtilityDec.h"

SeekingSearchUtilityDec::SeekingSearchUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingSearchUtilityDec::~SeekingSearchUtilityDec() {

}

double SeekingSearchUtilityDec::getPriority() {
	logger::log("SeekingSearchUtilityDec", "Priority:", 0.3, "Steady Minimum");

	return 0.3;
}
