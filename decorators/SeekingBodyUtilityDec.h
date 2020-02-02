#ifndef SEEKINGBODYUTILITYDEC_H
#define SEEKINGBODYUTILITYDEC_H

#include <cmath>

#include "../behaviourtree/decorator/UtilityDec.h"

class SeekingBodyUtilityDec : public UtilityDec {
public:
	SeekingBodyUtilityDec(Node* chi);
	SeekingBodyUtilityDec() : SeekingBodyUtilityDec(NULL) {};
	~SeekingBodyUtilityDec();

	double getPriority();
protected:
	int getMidX(cv::Rect* rect);
	int getMidY(cv::Rect* rect);

	double distance(int x1, int y1, int x2, int y2);
};

#endif