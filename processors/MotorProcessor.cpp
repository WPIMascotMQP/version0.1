#include "MotorProcessor.h"

namespace motorData {
	Position position;
	std::vector<MotorStatus> motors;
}

MotorProcessor::MotorProcessor() {

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