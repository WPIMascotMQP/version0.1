#include "MotorProcessor.h"

namespace processor {
	MotorProcessor mp(4);
}

namespace motorData {
	Position position;
	std::vector<MotorTracker*> motors;
	std::mutex motor_lock;

	int neck_yaw_ratio = 120;
	int neck_pitch_ratio = 100;
	int head_yaw_ratio = 100;
	int head_pitch_ratio = 125;

	int neck_yaw_maximum_physical = 120;
	int neck_pitch_maximum_physical = 100;
	int head_yaw_maximum_physical = 100;
	int head_pitch_maximum_physical = 125;

	int neck_yaw_neutral_physical = 60;
	int neck_pitch_neutral_physical = 35;
	int head_yaw_neutral_physical = 50;
	int head_pitch_neutral_physical = 50;
}

MotorProcessor::MotorProcessor(int num_motors) {
	for(int i = 0; i < num_motors; i++) {
		motorData::motors.push_back(new MotorTracker);
	}
	setupMotor(neck_yaw, 0, motorData::neck_yaw_ratio,
		motorData::neck_yaw_maximum_physical, motorData::neck_yaw_neutral_physical);
	setupMotor(neck_pitch, 0, motorData::neck_pitch_ratio,
		motorData::neck_pitch_maximum_physical, motorData::neck_pitch_neutral_physical);
	setupMotor(head_yaw, 0, motorData::head_yaw_ratio,
		motorData::head_yaw_maximum_physical, motorData::head_yaw_neutral_physical);
	setupMotor(head_pitch, 0, motorData::head_pitch_ratio,
		motorData::head_pitch_maximum_physical, motorData::head_pitch_neutral_physical);
}

void MotorProcessor::setupMotor(motors motor, double minimum, double ratio,
	double maximum_physical, double neutral_physical) {
	motorData::motors[motor]->minimum = minimum;
	motorData::motors[motor]->ratio = ratio;
	motorData::motors[motor]->maximum_physical =
		math::PI  * maximum_physical / 180;
	motorData::motors[motor]->neutral_physical =
		math::PI  * neutral_physical / 180;
	motorData::motors[motor]->maximum =
		motorData::motors[motor]->maximum_physical
		/ motorData::motors[motor]->ratio;
	motorData::motors[motor]->neutral =
		motorData::motors[motor]->neutral_physical
		/ motorData::motors[motor]->ratio;
}

MotorProcessor::~MotorProcessor() {

}

void MotorProcessor::startThread() {
	kill = false;
	pthread = std::thread(&MotorProcessor::processWrapper, this);
}

void MotorProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

Position* MotorProcessor::getCurrentPosition() {
	return new Position(0, 0, 0, 0);
}

Position* MotorProcessor::toPhysicalPosiiton(Position* pos) {
	double ny = pos->neck_yaw * motorData::motors[neck_yaw]->ratio;
	double np = pos->neck_pitch * motorData::motors[neck_pitch]->ratio;
	double hy = pos->head_yaw * motorData::motors[head_yaw]->ratio;
	double hp = pos->head_pitch * motorData::motors[head_pitch]->ratio;
	return new Position(ny, np, hy, hp);
}

Position* MotorProcessor::toMotorPosition(Position* pos) {
	double ny = pos->neck_yaw / motorData::motors[neck_yaw]->ratio;
	double np = pos->neck_pitch / motorData::motors[neck_pitch]->ratio;
	double hy = pos->head_yaw / motorData::motors[head_yaw]->ratio;
	double hp = pos->head_pitch / motorData::motors[head_pitch]->ratio;
	return new Position(ny, np, hy, hp);
}

Position* MotorProcessor::getMaximumMotorPosition() {
	double ny_mid = motorData::motors[neck_yaw]->maximum;
	double np_mid = motorData::motors[neck_pitch]->maximum;
	double hy_mid = motorData::motors[head_yaw]->maximum;
	double hp_mid = motorData::motors[head_pitch]->maximum;
	return new Position(ny_mid, np_mid, hy_mid, hp_mid);
}

Position* MotorProcessor::getMaximumPhysicalPosition() {
	double ny_mid = motorData::motors[neck_yaw]->maximum_physical;
	double np_mid = motorData::motors[neck_pitch]->maximum_physical;
	double hy_mid = motorData::motors[head_yaw]->maximum_physical;
	double hp_mid = motorData::motors[head_pitch]->maximum_physical;
	return new Position(ny_mid, np_mid, hy_mid, hp_mid);
}

Position* MotorProcessor::getNeutralMotorPosition() {
	double ny_mid = motorData::motors[neck_yaw]->neutral;
	double np_mid = motorData::motors[neck_pitch]->neutral;
	double hy_mid = motorData::motors[head_yaw]->neutral;
	double hp_mid = motorData::motors[head_pitch]->neutral;
	return new Position(ny_mid, np_mid, hy_mid, hp_mid);
}

Position* MotorProcessor::getNeutralPhysicalPosition() {
	double ny_mid = motorData::motors[neck_yaw]->neutral_physical;
	double np_mid = motorData::motors[neck_pitch]->neutral_physical;
	double hy_mid = motorData::motors[head_yaw]->neutral_physical;
	double hp_mid = motorData::motors[head_pitch]->neutral_physical;
	return new Position(ny_mid, np_mid, hy_mid, hp_mid);
}

double MotorProcessor::getMotorRatio(motors index) {
	return motorData::motors[index]->ratio;
}
