#ifndef MOTORPROCESSOR_H
#define MOTORPROCESSOR_H

#include "motorstatus/MotorTracker.h"
#include "../kinematics/Position.h"
#include "SensorProcessor.h"

enum motor_index {neck_yaw = 0, neck_pitch = 1, head_yaw = 2, head_pitch = 3};

class MotorProcessor : public SensorProcessor {
public:
	MotorProcessor(int num_motors);
	MotorProcessor() : MotorProcessor(0){};
	~MotorProcessor();

	void setupMotor(motor_index motor, double minimum, double ratio,
		double maximum_physical, double neutral_physical);

	void startThread();
	void process();

	Position* getCurrentPosition();
	Position* toPhysicalPosiiton(Position* pos);
	Position* toMotorPosition(Position* pos);
	Position* getMaximumMotorPosition();
	Position* getMaximumPhysicalPosition();
	Position* getNeutralMotorPosition();
	Position* getNeutralPhysicalPosition();

	double getMotorRatio(motor_index index);

	std::mutex motor_lock;
protected:
	Position position;
	std::vector<MotorTracker*> motors;

private:
};

namespace processor {
	extern MotorProcessor mp;
}
#endif
