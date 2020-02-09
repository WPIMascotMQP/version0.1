#ifndef MOTORPROCESSOR_H
#define MOTORPROCESSOR_H

#include "motorstatus/MotorTracker.h"
#include "../kinematics/Position.h"
#include "SensorProcessor.h"

enum motors {neck_yaw = 0, neck_pitch = 1, head_yaw = 2, head_pitch = 3};

class MotorProcessor : public SensorProcessor {
public:
	MotorProcessor(int num_motors);
	MotorProcessor() : MotorProcessor(0){};
	~MotorProcessor();

	void startThread();
	void process();

	Position* getCurrentPosition();
	Position* toPhysicalPosiiton(Position* pos);
	Position* toMotorPosition(Position* pos);

	double getMotorRatio(motors index);
protected:
private:
};

namespace processor {
	extern MotorProcessor mp;
}
#endif
