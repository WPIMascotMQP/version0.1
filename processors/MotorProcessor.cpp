#include "MotorProcessor.h"

namespace processor {
	MotorProcessor mp(4);
}

namespace motorData {
	double neck_yaw_ratio = 1;
	double neck_pitch_ratio = 1;
	double head_yaw_ratio = 1;
	double head_pitch_ratio = 1;

	double neck_yaw_maximum_physical = 120;
	double neck_pitch_maximum_physical = 100;
	double head_yaw_maximum_physical = 100;
	double head_pitch_maximum_physical = 125;

	double neck_yaw_neutral_physical = 60;
	double neck_pitch_neutral_physical = 35;
	double head_yaw_neutral_physical = 50;
	double head_pitch_neutral_physical = 50;
}

MotorProcessor::MotorProcessor(int num_motors) {
	for(int i = 0; i < 4; i++) {
		MotorTracker* mt = new MotorTracker();
		motors.push_back(mt);
	}
	setupMotor(motors.at(neck_yaw), 0, motorData::neck_yaw_ratio,
		motorData::neck_yaw_maximum_physical, motorData::neck_yaw_neutral_physical);
	setupMotor(motors.at(neck_pitch), 0, motorData::neck_pitch_ratio,
		motorData::neck_pitch_maximum_physical, motorData::neck_pitch_neutral_physical);
	setupMotor(motors.at(head_yaw), 0, motorData::head_yaw_ratio,
		motorData::head_yaw_maximum_physical, motorData::head_yaw_neutral_physical);
	setupMotor(motors.at(head_pitch), 0, motorData::head_pitch_ratio,
		motorData::head_pitch_maximum_physical, motorData::head_pitch_neutral_physical);
}

void MotorProcessor::setupMotor(MotorTracker* motor, double minimum, double ratio,
	double maximum_physical, double neutral_physical) {
	motor->setMinimum(minimum);
	motor->setNeutralPhysical(neutral_physical / 180 * math::PI);
	motor->setMaximumPhysical(maximum_physical / 180 * math::PI);
	motor->setRatio(ratio);
	motor->setNeutral(math::PI  * neutral_physical / 180 / motor->getRatio());
	motor->setMaximum(math::PI  * maximum_physical / 180 / motor->getRatio());
}

MotorProcessor::~MotorProcessor() {

}

void MotorProcessor::startThread() {
	kill = false;
	logger::log("MotorProcessor", motors.at(neck_yaw)->toString(), " - neck_yaw",  "Motor Constants");
	logger::log("MotorProcessor", motors.at(neck_pitch)->toString(), " - neck_pitch", "Motor Constants");
	logger::log("MotorProcessor", motors.at(head_yaw)->toString(), " - head_yaw", "Motor Constants");
	logger::log("MotorProcessor", motors.at(head_pitch)->toString(), " - head_pitch", "Motor Constants");
	pthread = std::thread(&MotorProcessor::processWrapper, this);

	logger::log("MotorProcessor Thread Started");
}

void MotorProcessor::killThread() {
	SensorProcessor::killThread();
	logger::log("MotorProcessor Thread Killed");
}

void MotorProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

std::shared_ptr<Position> MotorProcessor::getCurrentPosition() {
	return toMotorPosition(getNeutralPhysicalPosition());
}

std::shared_ptr<Position> MotorProcessor::toPhysicalPosiiton(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() * motors.at(neck_yaw)->getRatio();
	double np = pos->getNeckPitch() * motors.at(neck_pitch)->getRatio();
	double hy = pos->getHeadYaw() * motors.at(head_yaw)->getRatio();
	double hp = pos->getHeadPitch() * motors.at(head_pitch)->getRatio();
	return std::shared_ptr<Position>(new Position(ny, np, hy, hp));
}

std::shared_ptr<Position> MotorProcessor::toMotorPosition(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() / motors.at(neck_yaw)->getRatio();
	double np = pos->getNeckPitch() / motors.at(neck_pitch)->getRatio();
	double hy = pos->getHeadYaw() / motors.at(head_yaw)->getRatio();
	double hp = pos->getHeadPitch() / motors.at(head_pitch)->getRatio();
	return std::shared_ptr<Position>(new Position(ny, np, hy, hp));
}

std::shared_ptr<Position> MotorProcessor::getMinimumMotorPosition() {
	double ny_min = motors.at(neck_yaw)->getMinimum();
	double np_min = motors.at(neck_pitch)->getMinimum();
	double hy_min = motors.at(head_yaw)->getMinimum();
	double hp_min = motors.at(head_pitch)->getMinimum();
	return std::shared_ptr<Position>(new Position(ny_min, np_min, hy_min, hp_min));
}

std::shared_ptr<Position> MotorProcessor::getNeutralMotorPosition() {
	double ny_mid = motors.at(neck_yaw)->getNeutral();
	double np_mid = motors.at(neck_pitch)->getNeutral();
	double hy_mid = motors.at(head_yaw)->getNeutral();
	double hp_mid = motors.at(head_pitch)->getNeutral();
	return std::shared_ptr<Position>(new Position(ny_mid, np_mid, hy_mid, hp_mid));
}

std::shared_ptr<Position> MotorProcessor::getMaximumMotorPosition() {
	double ny_max = motors.at(neck_yaw)->getMaximum();
	double np_max = motors.at(neck_pitch)->getMaximum();
	double hy_max = motors.at(head_yaw)->getMaximum();
	double hp_max = motors.at(head_pitch)->getMaximum();
	return std::shared_ptr<Position>(new Position(ny_max, np_max, hy_max, hp_max));
}

std::shared_ptr<Position> MotorProcessor::getNeutralPhysicalPosition() {
	double ny_mid = motors.at(neck_yaw)->getNeutralPhysical();
	double np_mid = motors.at(neck_pitch)->getNeutralPhysical();
	double hy_mid = motors.at(head_yaw)->getNeutralPhysical();
	double hp_mid = motors.at(head_pitch)->getNeutralPhysical();
	return std::shared_ptr<Position>(new Position(ny_mid, np_mid, hy_mid, hp_mid));
}

std::shared_ptr<Position> MotorProcessor::getMaximumPhysicalPosition() {
	double ny_max = motors.at(neck_yaw)->getMaximumPhysical();
	double np_max = motors.at(neck_pitch)->getMaximumPhysical();
	double hy_max = motors.at(head_yaw)->getMaximumPhysical();
	double hp_max = motors.at(head_pitch)->getMaximumPhysical();
	return std::shared_ptr<Position>(new Position(ny_max, np_max, hy_max, hp_max));
}

std::shared_ptr<Position> MotorProcessor::getRatioPosition() {
	double ny_rat = motors.at(neck_yaw)->getRatio();
	double np_rat = motors.at(neck_pitch)->getRatio();
	double hy_rat = motors.at(head_yaw)->getRatio();
	double hp_rat = motors.at(head_pitch)->getRatio();
	return std::shared_ptr<Position>(new Position(ny_rat, np_rat, hy_rat, hp_rat));
}
