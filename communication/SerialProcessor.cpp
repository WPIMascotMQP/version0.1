#include "SerialProcessor.h"

namespace serial {
	SerialProcessor serial(0);
	std::vector<SpiSlave> serials;
	std::mutex serial_lock;
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
