#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include "SensorProcessor.h"

class AudioProcessor : public SensorProcessor {
public:
	AudioProcessor();
	~AudioProcessor();

	void startThread();
	void process();
protected:
private:
};
#endif 