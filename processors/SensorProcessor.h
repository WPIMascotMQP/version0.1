#ifndef SENSORPROCESSOR_H
#define SENSORPROCESSOR_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <mutex>

class SensorProcessor {
public:
	SensorProcessor();
	~SensorProcessor();

	virtual void startThread();
	void killThread();

	void processWrapper();
	virtual void process();

protected:
	std::mutex kill_lock;
	bool kill;

	std::thread pthread;

private:
};
#endif