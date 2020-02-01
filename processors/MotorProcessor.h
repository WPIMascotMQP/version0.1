#ifndef MOTORPROCESSOR_H
#define MOTORPROCESSOR_H

#include "motorstatus/MotorStatus.h"
#include "../kinematics/Position.h"
#include "SensorProcessor.h"

class MotorProcessor : public SensorProcessor {
public:
	MotorProcessor();
	~MotorProcessor();

	void startThread();
	void process();
protected:
private:
};
#endif