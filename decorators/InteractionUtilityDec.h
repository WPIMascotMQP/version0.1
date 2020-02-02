#ifndef INTERACTIONUTILITYDEC_H
#define INTERACTIONUTILITYDEC_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include "../behaviourtree/decorator/UtilityDec.h"

class InteractionUtilityDec : public UtilityDec {
public:
	InteractionUtilityDec(Node* chi);
	InteractionUtilityDec() : InteractionUtilityDec(NULL) {};
	~InteractionUtilityDec();

	double getPriority();
protected:

};

#endif