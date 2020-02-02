#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include "SensorProcessor.h"

class AudioProcessor : public SensorProcessor {
public:
	AudioProcessor(int num_mics);
	AudioProcessor() : AudioProcessor(0) {};
	~AudioProcessor();

	void startThread();
	void process();

	double getLastAudio();
protected:
private:
};

namespace processor {
	extern AudioProcessor ap;
}
#endif 