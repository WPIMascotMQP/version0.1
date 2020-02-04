#include "SeekingUtilityDec.h"

SeekingUtilityDec::SeekingUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingUtilityDec::~SeekingUtilityDec() {

}

double SeekingUtilityDec::getPriority() {
	std::ostringstream strs;
	strs << "SeekingUtilityDec Priority: 0.3 - Steady Minimum";
	logger::log(strs.str());

	return 0.3;
}
