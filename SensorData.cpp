#include "SensorData.h"

namespace data {
	SensorData sensorData(0.0, 0.0, 0.0, 0.0);
	int centerVisualWidth = 640 / 2;
	int centerVisualHeight = 480 / 2;
}

/**
 CONSTRUCTOR
 CONSTRUCTOR
 @param by The base yaw position
 @param bp The base pitch position
 @param ny The neck yaw position
 @param np The neck pitch postiion
*/
SensorData::SensorData(double by, double bp, double ny, double np) {
	current_position.base_yaw = by;
	current_position.base_pitch = bp;
	current_position.neck_yaw = ny;
	current_position.neck_pitch = np;
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
Position* SensorData::getCurrentPosition() {
	return &current_position;
	//return processor::mp::getCurrentPosition();
}

bool SensorData::getTouched() {
	return touched;
}

std::vector<cv::Rect*>* SensorData::getFaces() {
	return processor::vp.getFaceRects();
}

std::vector<cv::Rect*>* SensorData::getBodies() {
	return processor::vp.getBodyRects();
}

int SensorData::getVisualWidth() {
	return processor::vp.getVideoWidth();
}

int SensorData::getVisualHeight() {
	return processor::vp.getVideoHeight();
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
