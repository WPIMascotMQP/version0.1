#include "TouchProcessor.h"

TouchProcessor::TouchProcessor() {

}

TouchProcessor::~TouchProcessor() {
	
}

void TouchProcessor::startThread() {
	kill = false;
	pthread = std::thread(&TouchProcessor::processWrapper, this);
}

void TouchProcessor::process() {

}