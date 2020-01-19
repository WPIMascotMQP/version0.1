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

}