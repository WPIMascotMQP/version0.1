#include "SensorData.h"
std::string SensorData::input = "";
Position data_pos;
Position SensorData::currentPosition = data_pos;

/**
 CONSTRUCTOR
 @param cX The current X position
 @param cY The current Y position
 @param cZ The current Z position
*/
SensorData::SensorData(double cX, double cY, double cZ) {
	currentPosition.setXPosition(cX);
	currentPosition.setYPosition(cY);
	currentPosition.setZPosition(cZ);
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
	return &currentPosition;
	//return processor::mp::getCurrentPosition();
}

std::vector<cv::Rect*>* SensorData::getFaces() {
	return processor::vp.getFaceRects();
}

std::vector<cv::Rect*>* SensorData::getBodies() {
	return processor::vp.getBodyRects();
}

/**
 Sets the string input
 @param inp The string input
*/
void SensorData::setInput(std::string inp) {
	input = inp;
}

/**
 Sets the current position
 @param pos The current position
*/
void SensorData::setCurrentPosition(Position* pos) {
	currentPosition = *pos;
}