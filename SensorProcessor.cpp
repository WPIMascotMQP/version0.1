#include "SensorProcessor.h"

SensorProcessor::SensorProcessor() {

}

SensorProcessor::~SensorProcessor() {

}

void SensorProcessor::startThread() {
	kill = false;
	pthread = std::thread(&SensorProcessor::processWrapper, this);
}

void SensorProcessor::killThread() {
	kill_lock.lock();
	kill = true;
	kill_lock.unlock();
	pthread.join();
}

void SensorProcessor::processWrapper() {
	kill_lock.lock();
	while(!kill) {
		kill_lock.unlock();
		process();
		kill_lock.lock();
	}
}

void SensorProcessor::process() {

}