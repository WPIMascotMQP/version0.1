#include "MotorProcessor.h"
#include "../kinematics/Calculator.h"

namespace processor {
	MotorProcessor mp(motorData::num_motors);
}

namespace motorData {
	double neck_yaw_ratio = 1.0 / 3;
	double neck_pitch_ratio = 1.0 / 3;
	double head_yaw_ratio = 1.0 / 3;
	double head_pitch_ratio = 1.0 / 3;

	double neck_yaw_maximum_physical = 120;
	double neck_pitch_maximum_physical = 100;
	double head_yaw_maximum_physical = 100;
	double head_pitch_maximum_physical = 125;

	double neck_yaw_neutral_physical = 60;
	double neck_pitch_neutral_physical = 35;
	double head_yaw_neutral_physical = 50;
	double head_pitch_neutral_physical = 50;

	bool neck_yaw_flipped = false;
	bool neck_pitch_flipped = false;
	bool head_yaw_flipped = false;
	bool head_pitch_flipped = false;

	int num_motors = 4;

	int steps_per_rev = 6400;
}

/**
 CONSTRUCTOR
 @param num_motors The number of motors
 */
MotorProcessor::MotorProcessor(int num_motors) {
	for(int i = 0; i < motorData::num_motors; i++) {
		MotorTracker* mt = new MotorTracker();
		motors.push_back(mt);
	}
	setupMotor(motors.at(neck_yaw), 0, motorData::neck_yaw_ratio,
		motorData::neck_yaw_maximum_physical, motorData::neck_yaw_neutral_physical,
		motorData::neck_yaw_flipped);
	setupMotor(motors.at(neck_pitch), 0, motorData::neck_pitch_ratio,
		motorData::neck_pitch_maximum_physical, motorData::neck_pitch_neutral_physical,
		motorData::neck_pitch_flipped);
	setupMotor(motors.at(head_yaw), 0, motorData::head_yaw_ratio,
		motorData::head_yaw_maximum_physical, motorData::head_yaw_neutral_physical,
		motorData::head_yaw_flipped);
	setupMotor(motors.at(head_pitch), 0, motorData::head_pitch_ratio,
		motorData::head_pitch_maximum_physical, motorData::head_pitch_neutral_physical,
		motorData::head_pitch_flipped);
	cal::calculator.setFlipped();
}

/**
 Sets up a single motor given the step minimum, the gear ratio, the maximum_physical, the neutral_physical, and whether
 The motor is flipped or not
 @param motor The motor tracker to setup
 @param minum The minimum step number (0)
 @param ratio The gear ratio in terms of motor to physical radians
 @param maximum_physical The maximum_physical radian number
 @param neutral_physical The neutral physical radian number
 @param flipped Whether the motion of the motro is flipped or not
 */
void MotorProcessor::setupMotor(MotorTracker* motor, int minimum, double ratio,
	double maximum_physical, double neutral_physical, bool flipped) {
	motor->setMinimum(minimum);
	motor->setNeutralPhysical(neutral_physical / 180 * math::PI);
	motor->setMaximumPhysical(maximum_physical / 180 * math::PI);
	motor->setRatio(ratio);
	motor->setFlipped(flipped);
	motor->setNeutral((int) math::PI  * neutral_physical / 180 / motor->getRatio() * motorData::steps_per_rev);
	motor->setMaximum((int) math::PI  * maximum_physical / 180 / motor->getRatio() * motorData::steps_per_rev);
}

/**
 DECONSTRUCTOR
 */
MotorProcessor::~MotorProcessor() {

}

/**
 Starts the MotorProcessor processing thread
 */
void MotorProcessor::startThread() {
	kill = false;
	logger::log("MotorProcessor", motors.at(neck_yaw)->toString(), " - neck_yaw",  "Motor Constants");
	logger::log("MotorProcessor", motors.at(neck_pitch)->toString(), " - neck_pitch", "Motor Constants");
	logger::log("MotorProcessor", motors.at(head_yaw)->toString(), " - head_yaw", "Motor Constants");
	logger::log("MotorProcessor", motors.at(head_pitch)->toString(), " - head_pitch", "Motor Constants");
	pthread = std::thread(&MotorProcessor::processWrapper, this);

	logger::log("MotorProcessor Thread Started");
}

/**
 Kills the MotorProcessor processing thread
 */
void MotorProcessor::killThread() {
	SensorProcessor::killThread();
	logger::log("MotorProcessor Thread Killed");
}

/**
 The processing thread function for the MotorProcessor
 */
void MotorProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void MotorProcessor::addStepsHistory(int index, double radians) {
	motors.at(index)->addStepsHistory(radians);
}

/**
 Gets the current step position of the robot
 @return The current step position of the robot
 */
std::shared_ptr<Position> MotorProcessor::getCurrentStepPosition() {
	double ny = motors.at(neck_yaw)->getCurrentSteps();
	double np = motors.at(neck_pitch)->getCurrentSteps();
	double hy = motors.at(head_yaw)->getCurrentSteps();
	double hp = motors.at(head_pitch)->getCurrentSteps();
	return std::shared_ptr<Position>(new Position(ny, np, hy, hp));
}

/**
 Converts a given physical radian position to a motor radian position
 @param pos The physical position to convert
 @return The motor posiiton
 */
std::shared_ptr<Position> MotorProcessor::physicalToMotorPosition(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() 	/ motors.at(neck_yaw)->getRatio();
	double np = pos->getNeckPitch() / motors.at(neck_pitch)->getRatio();

	double h0 = (pos->getHeadPitch() + pos->getHeadYaw()) / motors.at(head_0)->getRatio();
	double h1 = (pos->getHeadPitch() - pos->getHeadYaw()) / motors.at(head_1)->getRatio();
	return std::shared_ptr<Position>(new Position(ny, np, h0, h1));
}

/**
 Converts a given motor radian position to a motor step position
 @param pos The motor position to convert
 @return The step posiiton
 */
std::shared_ptr<Position> MotorProcessor::motorToStepPosition(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() 	/ (2.0 * math::PI) * motorData::steps_per_rev;
	double np = pos->getNeckPitch() / (2.0 * math::PI) * motorData::steps_per_rev;
	double h0 = pos->getHead0() 	/ (2.0 * math::PI) * motorData::steps_per_rev;
	double h1 = pos->getHead1() 	/ (2.0 * math::PI) * motorData::steps_per_rev;
	return std::shared_ptr<Position>(new Position(ny, np, h0, h1));
}

/**
 Converts a given physical radian position to a motor step position
 @param pos The physical position to convert
 @return The step posiiton
 */
 std::shared_ptr<Position> MotorProcessor::physicalToStepPosition(std::shared_ptr<Position> pos) {
 	return motorToStepPosition(physicalToMotorPosition(pos));
 }

/**
 Converts a given motor step position to a motor radian position
 @param pos The motor step position to convert
 @return The motor posiiton
 */
std::shared_ptr<Position> MotorProcessor::stepToMotorPosition(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() 	/ motorData::steps_per_rev * (2 * math::PI);
	double np = pos->getNeckPitch() / motorData::steps_per_rev * (2 * math::PI);
	double h0 = pos->getHead0() 	/ motorData::steps_per_rev * (2 * math::PI);
	double h1 = pos->getHead1() 	/ motorData::steps_per_rev * (2 * math::PI);
	return std::shared_ptr<Position>(new Position(ny, np, h0, h1));
}

/**
 Converts a given motor raidan position to a physical radian position
 @param pos The motor radin position to convert
 @return The physical posiiton
 */
std::shared_ptr<Position> MotorProcessor::motorToPhysicalPosition(std::shared_ptr<Position> pos) {
	double ny = pos->getNeckYaw() 	* motors.at(neck_yaw)->getRatio();
	double np = pos->getNeckPitch() * motors.at(neck_pitch)->getRatio();

	double hy = (pos->getHead0() + pos->getHead1()) / 2;
	double hp = (pos->getHead0() - pos->getHead1()) / 2;
	return std::shared_ptr<Position>(new Position(ny, np, hy, hp));
}

/**
 Converts a given motor step position to a physical radian position
 @param pos The motor step position to convert
 @return The physcial posiiton
 */
 std::shared_ptr<Position> MotorProcessor::stepToPhysicalPosition(std::shared_ptr<Position> pos) {
	return motorToPhysicalPosition(stepToMotorPosition(pos));
 }

std::shared_ptr<Position> MotorProcessor::getMinimumStepPosition() {
	int ny_min = motors.at(neck_yaw)->getMinimum();
	int np_min = motors.at(neck_pitch)->getMinimum();
	int hy_min = motors.at(head_yaw)->getMinimum();
	int hp_min = motors.at(head_pitch)->getMinimum();
	return std::shared_ptr<Position>(new Position(ny_min, np_min, hy_min, hp_min));
}

std::shared_ptr<Position> MotorProcessor::getNeutralStepPosition() {
	int ny_mid = motors.at(neck_yaw)->getNeutral();
	int np_mid = motors.at(neck_pitch)->getNeutral();
	int hy_mid = motors.at(head_yaw)->getNeutral();
	int hp_mid = motors.at(head_pitch)->getNeutral();
	return std::shared_ptr<Position>(new Position(ny_mid, np_mid, hy_mid, hp_mid));
}

std::shared_ptr<Position> MotorProcessor::getMaximumStepPosition() {
	int ny_max = motors.at(neck_yaw)->getMaximum();
	int np_max = motors.at(neck_pitch)->getMaximum();
	int hy_max = motors.at(head_yaw)->getMaximum();
	int hp_max = motors.at(head_pitch)->getMaximum();
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

std::shared_ptr<Position> MotorProcessor::getFlippedPosition() {
	double ny_flp = motors.at(neck_yaw)->getFlipped() ? 1.0 : 0.0;
	double np_flp = motors.at(neck_pitch)->getFlipped() ? 1.0 : 0.0;
	double hy_flp = motors.at(head_yaw)->getFlipped() ? 1.0 : 0.0;
	double hp_flp = motors.at(head_pitch)->getFlipped() ? 1.0 : 0.0;
	return std::shared_ptr<Position>(new Position(ny_flp, np_flp, hy_flp, hp_flp));
}

/**
 Turns a given desired physical position and neck and head velocity to a movement with the step number and delay
 @param setPos The desired physical position to move to
 @param neck_velocity The desired velocity of the neck movement in radians/sec
 @param head_velocuty The desired velocity of the head movement in radians/sec
 */
std::shared_ptr<Movement> MotorProcessor::calculateMovement(std::shared_ptr<Position> pos, double neck_velocity, double head_velocity) {
	std::shared_ptr<Position> pos_physical = stepToPhysicalPosition(getCurrentStepPosition());

	// Calculate the velocity for each axis
	double neck_yaw_d = 	std::abs(pos_physical->getNeckYaw() - pos->getNeckYaw());
	double neck_pitch_d = 	std::abs(pos_physical->getNeckPitch() - pos->getNeckPitch());
	double head_yaw_d = 	std::abs(pos_physical->getHeadYaw() - pos->getHeadYaw());
	double head_pitch_d = 	std::abs(pos_physical->getHeadPitch() - pos->getHeadPitch());

	double neck_d = std::sqrt(std::pow(neck_yaw_d, 2) + std::pow(neck_pitch_d, 2));
	double head_d = std::sqrt(std::pow(head_yaw_d, 2) + std::pow(head_pitch_d, 2));

	double neck_yaw_v = 	neck_yaw_d == 0 ? 0 :	std::abs(neck_d * neck_velocity / neck_yaw_d);
	double neck_pitch_v = 	neck_pitch_d == 0 ? 0 :	std::abs(neck_d * neck_velocity / neck_pitch_d);
	double head_yaw_v = 	head_yaw_d == 0 ? 0 :	std::abs(head_d * head_velocity / head_yaw_d);
	double head_pitch_v = 	head_pitch_d == 0 ? 0 :	std::abs(head_d * head_velocity / head_pitch_d);

	// Convert to steps per sec and then to microsec delay
	std::shared_ptr<Position> pos_physical_v(new Position(neck_yaw_v, neck_pitch_v, head_yaw_v, head_pitch_v));
	std::shared_ptr<Position> pos_s = physicalToStepPosition(pos_physical_v);
	std::shared_ptr<Position> pos_delay = stepsToDelay(pos_s);

	// Create and return movement
	std::shared_ptr<Position> pos_steps = physicalToStepPosition(pos);
	std::shared_ptr<Movement> mov(new Movement);
	mov->setSetPosition(pos_steps);
	mov->setDelay(pos_delay);

	return mov;
}

/**
 Converst a steps per sec to a mircosec per step
 @param steps The steps per sec
 @return The microsec delay
 */
std::shared_ptr<Position>  MotorProcessor::stepsToDelay(std::shared_ptr<Position> steps) {
	std::shared_ptr<Position> pos(new Position);
	for(int i = 0; i < 4; i++) {
		double steps_micro = steps->getAtIndex(i) / 1000000;
		double delay = steps_micro == 0 ? 500 : std::round(1.0 / steps_micro + 0.5);
		pos->setAtIndex(i, delay);
	}
	return pos;
}
