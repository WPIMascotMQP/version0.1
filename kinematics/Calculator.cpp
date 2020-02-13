#include "Calculator.h"

#include "../behaviourtree/Node.h"

namespace cal {
	Calculator calculator(0);

}

/**
 CONSTRUCTOR
*/
Calculator::Calculator(int start_int) {

}

/**
 DECONSTRUCTOR
*/
Calculator::~Calculator() {

}

std::shared_ptr<Position> Calculator::getPosition(double yaw, double pitch) {
	std::shared_ptr<Position> maximum_pos = processor::mp.getMaximumPhysicalPosition();

	// Get maximum positions
	double maximum_yaw = maximum_pos->getNeckYaw() + maximum_pos->getHeadYaw();
	double maximum_pitch = maximum_pos->getNeckPitch() + maximum_pos->getHeadPitch();

	// Current polar + change in polar / total yaw = percent of total polar
	double yaw_ratio = getNeckHeadRatio(yaw / maximum_yaw);
	double pitch_ratio = getNeckHeadRatio(pitch / maximum_pitch);

	// New Position based on
	// neutral position + (final total polar change * ratio between head and neck)
	std::shared_ptr<Position> new_physical(new Position(
		(yaw) * (1 - yaw_ratio),
		(pitch) * (1 - pitch_ratio),
		(yaw) * yaw_ratio,
		(pitch) * pitch_ratio));
	std::shared_ptr<Position> new_pos = processor::mp.toMotorPosition(new_physical);

	return new_pos;
}

std::shared_ptr<Position> Calculator::getDeltaPosition(double yaw, double pitch) {
	std::shared_ptr<Position> current_pos = data::sensor_data.getCurrentPosition();
	std::shared_ptr<Position> physical_pos = processor::mp.toPhysicalPosiiton(current_pos);
	std::shared_ptr<Position> neutral_pos = processor::mp.getNeutralPhysicalPosition();
	std::shared_ptr<Position> maximum_pos = processor::mp.getMaximumPhysicalPosition();

	// Get total yaw positions
	double maximum_yaw = maximum_pos->getNeckYaw() + maximum_pos->getHeadYaw();
	double current_yaw = physical_pos->getNeckYaw() + physical_pos->getHeadYaw();
	double neutral_yaw = neutral_pos->getNeckYaw() + neutral_pos->getHeadYaw();

	// Get total pitch positions
	double maximum_pitch = maximum_pos->getNeckPitch() + maximum_pos->getHeadPitch();
	double current_pitch = physical_pos->getNeckPitch() + physical_pos->getHeadPitch();
	double neutral_pitch = neutral_pos->getNeckPitch() + neutral_pos->getHeadPitch();

	// Current polar + change in polar / total yaw = percent of total polar
	double yaw_ratio = getNeckHeadRatio((current_yaw + yaw) / maximum_yaw);
	double pitch_ratio = getNeckHeadRatio((current_pitch + pitch) / maximum_pitch);

	// New Position based on
	// neutral position + (final total polar change * ratio between head and neck)
	std::shared_ptr<Position> new_physical(new Position(
		neutral_pos->getNeckYaw() + (current_yaw - neutral_yaw + yaw) * (1 - yaw_ratio),
		neutral_pos->getNeckPitch() + (current_pitch - neutral_pitch + pitch) * (1 - pitch_ratio),
		neutral_pos->getHeadYaw() + (current_yaw -neutral_yaw + yaw) * yaw_ratio,
		neutral_pos->getHeadPitch() + (current_pitch -neutral_pitch + pitch) * pitch_ratio));
	std::shared_ptr<Position> new_pos = processor::mp.toMotorPosition(new_physical);

	return(new_pos);
}

std::shared_ptr<Position> Calculator::getDeltaPosition(double ny, double np, double hy, double hp) {
	std::shared_ptr<Position> current_pos = data::sensor_data.getCurrentPosition();
	std::shared_ptr<Position> physical_pos = processor::mp.toPhysicalPosiiton(current_pos);
	std::shared_ptr<Position> new_physical(new Position(physical_pos->getNeckYaw() + ny,
									physical_pos->getNeckPitch() + np,
									physical_pos->getHeadYaw() + hy,
									physical_pos->getHeadPitch() + hp));
	std::shared_ptr<Position> new_pos = processor::mp.toMotorPosition(new_physical);
	return(new_pos);
}

double Calculator::getNeckHeadRatio(double percent) {
	percent = percent - 0.5;
	return std::pow(percent, 4) - 3.5 * std::pow(percent, 2) + 1;
}

/**
 Generates the movements given a set of actions
 @param actions The list of actions
 @param beh The beahviour associated with the actions
 @return The list of movements
*/
/*std::vector<Movement*> *Calculator::generateMovements(std::vector<Action*> actions, Behaviour *beh) {
	std::vector<Movement*> *movements = new std::vector<Movement*>();
	std::vector<Action*>::iterator act_itr;
	Position pos = Position(data::sensorData.getCurrentPosition()->getXPosition(),
		data::sensorData.getCurrentPosition()->getYPosition(),
		data::sensorData.getCurrentPosition()->getZPosition());
	// For each action generate a movement based on the last one
	for (act_itr = actions.begin(); act_itr < actions.end(); act_itr++) {
		Action* action = *act_itr;
		double newX = pos.getXPosition() + action->getDeltaX();
		double newY = pos.getYPosition() + action->getDeltaY();
		double newZ = pos.getZPosition() + action->getDeltaZ();

		Movement *movement = new Movement();
		movement->setSetPoint(new Position(newX, newY, newZ));
		movement->setCurrentPoint(new Position(pos.getXPosition(), pos.getYPosition(), pos.getZPosition()));
		// For the last movement set the behaviour
		if (act_itr == actions.end() - 1) {
			movement->setBehaviour(beh);
		}
		movements->push_back(movement);

		pos.setXPosition(newX);
		pos.setYPosition(newY);
		pos.setZPosition(newZ);
	}
	return movements;
}*/
