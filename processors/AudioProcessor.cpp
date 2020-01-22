#include "AudioProcessor.h"

AudioProcessor::AudioProcessor() {

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