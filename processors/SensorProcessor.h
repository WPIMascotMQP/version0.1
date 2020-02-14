#ifndef SENSORPROCESSOR_H
#define SENSORPROCESSOR_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>

#include "../Logger.h"

class SensorProcessor {
public:
	SensorProcessor();
	~SensorProcessor();

	virtual void startThread();
	virtual void killThread();

	void processWrapper();
	virtual void process();

protected:
	std::mutex kill_lock;
	bool kill;

	std::thread pthread;

private:
};
#endif