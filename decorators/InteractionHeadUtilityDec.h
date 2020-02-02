#ifndef INTERACTIONHEADUTILITYDEC_H
#define INTERACTIONHEADUTILITYDEC_H

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionHeadUtilityDec : public UtilityDec {
public:
	InteractionHeadUtilityDec(Node* chi);
	InteractionHeadUtilityDec() : InteractionHeadUtilityDec(NULL) {};
	~InteractionHeadUtilityDec();

	double getPriority();
protected:
	int getMidX(cv::Rect* rect);
	int getMidY(cv::Rect* rect);

	double distance(int x1, int y1, int x2, int y2);
};

#endif