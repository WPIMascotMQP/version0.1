#ifndef MOTORPROCESSOR_H
#define MOTORPROCESSOR_H

#include "motorstatus/MotorStatus.h"
#include "../kinematics/Position.h"
#include "SensorProcessor.h"

class MotorProcessor : public SensorProcessor {
public:
	MotorProcessor(int num_motors);
	MotorProcessor() : MotorProcessor(0){};
	~MotorProcessor();

	void startThread();
	void process();

	Position* getCurrentPosition();
protected:
private:
};

namespace processor {
	extern MotorProcessor mp;
}
#endif