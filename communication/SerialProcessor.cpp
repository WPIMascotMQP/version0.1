#include "SerialProcessor.h"

namespace serial {
	SerialProcessor serial(0);
}

SerialProcessor::SerialProcessor(int num_serials) {

}

SerialProcessor::~SerialProcessor() {

}

void SerialProcessor::startThread() {
	pthread = std::thread(&SerialProcessor::processWrapper, this);
}

void SerialProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

