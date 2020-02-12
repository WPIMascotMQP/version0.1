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

Position* Calculator::getPosition(double yaw, double pitch) {
	Position* maximum_pos = processor::mp.getMaximumPhysicalPosition();

	// Get maximum positions
	double maximum_yaw = maximum_pos->neck_yaw + maximum_pos->head_yaw;
	double maximum_pitch = maximum_pos->neck_pitch + maximum_pos->head_pitch;

	// Current polar + change in polar / total yaw = percent of total polar
	double yaw_ratio = getNeckHeadRatio(yaw / maximum_yaw);
	double pitch_ratio = getNeckHeadRatio(pitch / maximum_pitch);

	// New Position based on
	// neutral position + (final total polar change * ratio between head and neck)
	Position* new_physical = new Position(
		(yaw) * (1 - yaw_ratio),
		(pitch) * (1 - pitch_ratio),
		(yaw) * yaw_ratio,
		(pitch) * pitch_ratio);
	Position* new_pos = processor::mp.toMotorPosition(new_physical);

	delete(maximum_pos);
	delete(new_physical);
	return new_pos;
}

Position* Calculator::getDeltaPosition(double yaw, double pitch) {
	Position* current_pos = data::sensor_data.getCurrentPosition();
	Position* physical_pos = processor::mp.toPhysicalPosiiton(current_pos);
	Position* neutral_pos = processor::mp.getNeutralPhysicalPosition();
	Position* maximum_pos = processor::mp.getMaximumPhysicalPosition();

	// Get total yaw positions
	double maximum_yaw = maximum_pos->neck_yaw + maximum_pos->head_yaw;
	double current_yaw = physical_pos->neck_yaw + physical_pos->head_yaw;
	double neutral_yaw = neutral_pos->neck_yaw + neutral_pos->head_yaw;

	// Get total pitch positions
	double maximum_pitch = maximum_pos->neck_pitch + maximum_pos->head_pitch;
	double current_pitch = physical_pos->neck_pitch + physical_pos->head_pitch;
	double neutral_pitch = neutral_pos->neck_pitch + neutral_pos->head_pitch;

	// Current polar + change in polar / total yaw = percent of total polar
	double yaw_ratio = getNeckHeadRatio((current_yaw + yaw) / maximum_yaw);
	double pitch_ratio = getNeckHeadRatio((current_pitch + pitch) / maximum_pitch);

	// New Position based on
	// neutral position + (final total polar change * ratio between head and neck)
	Position* new_physical = new Position(
		neutral_pos->neck_yaw + (current_yaw - neutral_yaw + yaw) * (1 - yaw_ratio),
		neutral_pos->neck_pitch + (current_pitch - neutral_pitch + pitch) * (1 - pitch_ratio),
		neutral_pos->head_yaw + (current_yaw -neutral_yaw + yaw) * yaw_ratio,
		neutral_pos->head_pitch + (current_pitch -neutral_pitch + pitch) * pitch_ratio);
	Position* new_pos = processor::mp.toMotorPosition(new_physical);

	delete(current_pos);
	delete(physical_pos);
	delete(neutral_pos);
	delete(maximum_pos);
	delete(new_physical);
	return(new_pos);
}

Position* Calculator::getDeltaPosition(double ny, double np, double hy, double hp) {
	Position* current_pos = data::sensor_data.getCurrentPosition();
	Position* physical_pos = processor::mp.toPhysicalPosiiton(current_pos);
	Position* new_physical = new Position(physical_pos->neck_yaw + ny,
									physical_pos->neck_pitch + np,
									physical_pos->head_yaw + hy,
									physical_pos->head_pitch + hp);
	Position* new_pos = processor::mp.toMotorPosition(new_physical);
	delete(current_pos);
	delete(physical_pos);
	delete(new_physical);
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
