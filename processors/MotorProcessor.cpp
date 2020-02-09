#include "MotorProcessor.h"

namespace processor {
	MotorProcessor mp(4);
}

namespace motorData {
	Position position;
	std::vector<MotorTracker*> motors;
	std::mutex motor_lock;
}

MotorProcessor::MotorProcessor(int num_motors) {
	for(int i = 0; i < num_motors; i++) {
		motorData::motors.push_back(new MotorTracker);
	}
	motorData::motors[neck_yaw]->ratio = 3/2;
	motorData::motors[neck_pitch]->ratio = 3/2;
	motorData::motors[head_yaw]->ratio = 3/2;
	motorData::motors[head_pitch]->ratio = 3/2;
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

double MotorProcessor::getMotorRatio(motors index) {
	return motorData::motors[index]->ratio;
}
