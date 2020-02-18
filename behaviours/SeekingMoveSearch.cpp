#include "SeekingMoveSearch.h"

/**
 CONSTUCTOR
*/
SeekingMoveSearch::SeekingMoveSearch() {
	std::srand(time(0));
}

/**
 DECONSTRUCTOR
*/
SeekingMoveSearch::~SeekingMoveSearch() {
	actions.clear();
}

/**
 The Node execute as child function
 Puts SeekingMoveSearch into controller
 @return The status
*/
Status* SeekingMoveSearch::executeC() {
	logger::log("SeekingMoveSearch Called as Child");
	status.setRunning();

	std::shared_ptr<Position> neutral_pos = processor::mp.getNeutralPhysicalPosition();
	std::shared_ptr<Position> maximum_pos = processor::mp.getMaximumPhysicalPosition();

	double neutral_yaw = neutral_pos->getNeckYaw() + neutral_pos->getHeadYaw();
	double maximum_yaw = maximum_pos->getNeckYaw() + maximum_pos->getHeadYaw();
	double delta_yaw = std::min(neutral_yaw, maximum_yaw - neutral_yaw);

	double random_yaw = neutral_yaw - (delta_yaw * 4.0 / 5.0) + std::rand() %
		(int) (delta_yaw * (8.0 / 5.0) + 0.5);

	double neutral_pitch = neutral_pos->getNeckPitch() + neutral_pos->getHeadPitch();
	double maximum_pitch = maximum_pos->getNeckPitch() + maximum_pos->getHeadPitch();
	double delta_pitch = std::min(neutral_pitch, maximum_pitch - neutral_pitch);

	double random_pitch = neutral_pitch - (delta_pitch / 2.0) + std::rand() %
		(int) (delta_pitch + 0.5);

	std::shared_ptr<Position> pos = cal::calculator.getPosition(random_yaw, random_pitch);
	coms::controller.addPosition(pos);
	coms::controller.addBehaviour(this);

	logger::log("SeekingMoveSearch", "Calculated Position", pos->toString(), "Position to Move To");
	return &status;
}

/**
 The Node execute as parent function
 @param stat The status of the child executing this parent
 @return the status
*/
Status* SeekingMoveSearch::executeP(Status* stat) {
	status = *stat;
	return parent->executeP(stat);
}

std::string SeekingMoveSearch::toString() {
	return "SeekingMoveSearch";
}