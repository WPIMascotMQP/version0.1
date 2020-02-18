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

	void setupMotor(MotorTracker* motor, double minimum, double ratio,
		double maximum_physical, double neutral_physical, bool flipped);

	void startThread();
	void killThread();
	void process();

	void addRadiansHistory(int index, double radians);

	std::shared_ptr<Position> getCurrentPosition();
	std::shared_ptr<Position> toPhysicalPosiiton(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> toMotorPosition(std::shared_ptr<Position> pos);

	std::shared_ptr<Position> getMinimumMotorPosition();
	std::shared_ptr<Position> getNeutralMotorPosition();
	std::shared_ptr<Position> getMaximumMotorPosition();
	std::shared_ptr<Position> getNeutralPhysicalPosition();
	std::shared_ptr<Position> getMaximumPhysicalPosition();
	std::shared_ptr<Position> getRatioPosition();
	std::shared_ptr<Position> getFlippedPosition();

	std::mutex motor_lock;
protected:
	std::vector<MotorTracker*> motors;

private:

};

namespace processor {
	extern MotorProcessor mp;
}

namespace motorData {
	extern int num_motors;
}
#endif
