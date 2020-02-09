#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include <cstddef>

#include "../processors/SensorProcessor.h"
#include "SpiSlave.h"

class SerialProcessor : public SensorProcessor{
public:
	SerialProcessor(int num_serials);
	SerialProcessor() : SerialProcessor(0) {};
	~SerialProcessor();

	void startThread();
	void process();
protected:
private:
};

namespace serial {
	extern SerialProcessor serial;
}

#endif
