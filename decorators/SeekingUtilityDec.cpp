#include "SeekingUtilityDec.h"

SeekingUtilityDec::SeekingUtilityDec(Node* chi) : UtilityDec(chi) {

}

SeekingUtilityDec::~SeekingUtilityDec() {

}

double SeekingUtilityDec::getPriority() {
	logger::log("SeekingUtilityDec", "Priority:", 0.12, "Steady Minimum");

	return 0.12;
}
