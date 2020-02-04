#include "SeekingSearchUtilityDec.h"

SeekingSearchUtilityDec::SeekingSearchUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingSearchUtilityDec::~SeekingSearchUtilityDec() {

}

double SeekingSearchUtilityDec::getPriority() {
	std::ostringstream strs;
	strs << "SeekingSearchUtilityDec Priority: 0.3 - Steady Minimum";
	logger::log(strs.str());
	
	return 0.3;
}
