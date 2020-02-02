#include "SensorData.h"

namespace data {
	SensorData sensorData(0.0, 0.0, 0.0);
}

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
	return &currentPosition;
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
	currentPosition = *pos;
}