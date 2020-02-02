#include "AudioProcessor.h"

namespace processor {
	AudioProcessor ap(3);
}

AudioProcessor::AudioProcessor(int num_mics) {

}

AudioProcessor::~AudioProcessor() {

}

void AudioProcessor::startThread() {
	kill = false;
	pthread = std::thread(&AudioProcessor::processWrapper, this);
}

void AudioProcessor::process() {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

double AudioProcessor::getLastAudio() {
	return 0.0;
}