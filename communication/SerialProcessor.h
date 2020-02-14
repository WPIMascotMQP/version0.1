#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include <cstddef>

#include "../behaviourtree/Behaviour.h"
#include "../processors/SensorProcessor.h"
#include "SpiSlave.h"

class SerialProcessor : public SensorProcessor{
public:
	SerialProcessor(int num_serials);
	SerialProcessor() : SerialProcessor(0) {};
	~SerialProcessor();

	void startThread();
	void killThread();
	void process();

	void finishBehaviours();
protected:
private:
};

namespace serial {
	extern SerialProcessor serial;
}

#endif
