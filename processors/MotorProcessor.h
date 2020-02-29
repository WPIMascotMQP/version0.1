#ifndef MOTORPROCESSOR_H
#define MOTORPROCESSOR_H

#include "motorstatus/MotorTracker.h"
#include "../kinematics/Movement.h"
#include "../kinematics/Position.h"
#include "SensorProcessor.h"

enum motor_index {neck_yaw = 0, neck_pitch = 1, head_yaw = 2, head_pitch = 3, head_0 = 2, head_1 = 3};

class MotorProcessor : public SensorProcessor {
public:
	MotorProcessor(int num_motors);
	MotorProcessor() : MotorProcessor(0){};
	~MotorProcessor();

	void setupMotor(MotorTracker* motor, int minimum, double ratio,
		double maximum_physical, double neutral_physical, bool flipped);

	void startThread();
	void killThread();
	void process();

	void addRadiansHistory(int index, double radians);

	std::shared_ptr<Position> getCurrentStepPosition();
	std::shared_ptr<Position> physicalToMotorPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> motorToStepPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> physicalToStepPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> stepToMotorPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> motorToPhysicalPosition(std::shared_ptr<Position> pos);
	std::shared_ptr<Position> stepToPhysicalPosition(std::shared_ptr<Position> pos);

	std::shared_ptr<Position> getMinimumStepPosition();
	std::shared_ptr<Position> getNeutralStepPosition();
	std::shared_ptr<Position> getMaximumStepPosition();
	std::shared_ptr<Position> getNeutralPhysicalPosition();
	std::shared_ptr<Position> getMaximumPhysicalPosition();
	std::shared_ptr<Position> getRatioPosition();
	std::shared_ptr<Position> getFlippedPosition();

	std::shared_ptr<Movement> calculateMovement(std::shared_ptr<Position> pos,
		double neck_velocity, double head_velocity);
	std::shared_ptr<Position> stepsToDelay(std::shared_ptr<Position> steps);

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
