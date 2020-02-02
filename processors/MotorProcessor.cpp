#include "MotorProcessor.h"

namespace processor {
	MotorProcessor mp(5);
}

namespace motorData {
	Position position;
	std::vector<MotorStatus*> motors;
	std::mutex motor_lock;
}

MotorProcessor::MotorProcessor(int num_motors) {
	for(int i = 0; i < num_motors; i++) {
		motorData::motors.push_back(new MotorStatus);
	}
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
	return new Position(0, 0, 0);
}