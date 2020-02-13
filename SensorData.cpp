#include "SensorData.h"

namespace data {
	SensorData sensor_data(0.0, 0.0, 0.0, 0.0);
	int centerVisualWidth = 640 / 2;
	int centerVisualHeight = 480 / 2;
}

/**
 CONSTRUCTOR
 @param ny The neck yaw position
 @param np The neck pitch position
 @param hy The head yaw position
 @param hp The head pitch postiion
*/
SensorData::SensorData(double ny, double np, double hy, double hp) {
	current_position.setNeckYaw(ny);
	current_position.setNeckPitch(np);
	current_position.setHeadYaw(hy);
	current_position.setHeadPitch(hp);
	touched = false;
	input = "";
}

/**
 DECONSTRUCTOR
*/
SensorData::~SensorData() {

}

/**
 Gets the string input
 @return The string input
*/
std::string SensorData::getInput() {
	return input;
}

double SensorData::getLastAudio() {
	return processor::ap.getLastAudio();
}

/**
 Gets the current position
 @return The current position
*/
std::shared_ptr<Position> SensorData::getCurrentPosition() {
	return processor::mp.getCurrentPosition();
}

bool SensorData::getTouched() {
	return touched;
}

/**
 Sets the string input
 @param inp The string input
*/
void SensorData::setInput(std::string inp) {
	input = inp;
}

void SensorData::setTouched(bool touch) {
	touched = touch;
}

/**
 Sets the current position
 @param pos The current position
*/
void SensorData::setCurrentPosition(Position* pos) {
	current_position = *pos;
}
