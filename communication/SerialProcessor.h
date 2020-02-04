#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include "../processors/SensorProcessor.h"

class SerialProcessor : public SensorProcessor{
public:
	SerialProcessor(int num_serials);
	SerialProcessor() Serial(0) {};
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