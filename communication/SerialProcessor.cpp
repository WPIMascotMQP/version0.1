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
	kill = false;
	pthread = std::thread(&SerialProcessor::processWrapper, this);
	logger::log("SerialProcessor Thread Started");
}

void SerialProcessor::killThread() {
	SensorProcessor::killThread();
	logger::log("SerialProcessor Thread Killed");
}


void SerialProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void SerialProcessor::finishBehaviours() {
	std::vector<Behaviour*>::iterator itr = coms::behaviour_list_current.begin();
	while(itr < coms::behaviour_list_current.end()) {
		coms::behaviour_list_execute.push_back(*itr);
		itr = coms::behaviour_list_current.erase(itr);
	}
}
