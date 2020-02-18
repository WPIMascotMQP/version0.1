#include "SerialProcessor.h"

#include "../processors/MotorProcessor.h"

namespace serial {
	SerialProcessor serial(2);

	std::vector<std::shared_ptr<Position>> positions_to_send;
	std::mutex position_lock;

	size_t buffer_size = 64;

	int num_serials = 2;
	size_t pattern_len = 10;
}

SerialProcessor::SerialProcessor(int num_serials) {
	for(int i = 0; i < serial::num_serials; i++) {
		serials.push_back(new SpiSlave(i));
		buffers.push_back(new std::vector<unsigned char*>());
		buffer_lengths.push_back(new std::vector<size_t>());
		buffers_rec.push_back(new unsigned char);
		rec_bytes.push_back(0);
		recievings.push_back(false);
		counters.push_back(0);
	}
}

SerialProcessor::~SerialProcessor() {

}

void SerialProcessor::startThread() {
	kill = false;
	pthread = std::thread(&SerialProcessor::processWrapper, this);
	logger::log("SerialProcessor Thread Started");
}

void SerialProcessor::killThread() {
	SensorProcessor::killThread();
	logger::log("SerialProcessor Thread Killed");
}


void SerialProcessor::process() {
	serial::position_lock.lock();
	
	std::vector<std::shared_ptr<Position>>::iterator itr = serial::positions_to_send.begin();

	// If have posiitons send them
	if(itr < serial::positions_to_send.end()) {
		std::shared_ptr<Position> pos = *itr;

		std::ostringstream strs;
		for(int i = 0; i < motorData::num_motors; i++) {
			unsigned char* buffer = new unsigned char[serial::buffer_size];
			size_t current_byte = 0;

			current_byte += encodePattern(buffer, current_byte);
			buffer[current_byte++] = MOTORPOSITION;
			current_byte += encodeInt16(buffer, current_byte, 1);
			current_byte += encodeFloat(buffer, current_byte, pos->getAtIndex(i));
			current_byte += encodePattern(buffer, current_byte);

			buffers.at(motor_serial)->push_back(buffer);
			buffer_lengths.at(motor_serial)->push_back(current_byte);

			strs << "|" << getStringHex(buffer, current_byte);
		}
		logger::log("SerialProcessor", "Encoded Position", pos->toString(), strs.str());
		serial::positions_to_send.erase(itr);
	}
	serial::position_lock.unlock();

	for(int i = 0; i < serial::num_serials; i++) {
		if(recievings.at(i)) {
			// If Listening for a response
			unsigned char* buffer = new unsigned char[serial::buffer_size];
			unsigned char* buf_rec = buffers_rec.at(i);
			size_t rec_byte = rec_bytes.at(i);
			size_t inc_byte = serials.at(i)->readWrite(buffer, serial::buffer_size);

			// If recieved too much, start at 0
			if(rec_byte + inc_byte >= serial::buffer_size) {
				rec_byte = 0;
			}
			rec_byte += overwriteBytes(buf_rec, rec_byte, buffer, 0,  inc_byte);

			// TEST IF COMPLETE
			if(findCommand(buffer)) {
				recievings.at(i) = false;
				// Process command
				delete(buffer);
			}

			rec_bytes.at(i) = rec_byte;
		} else {
			// If have buffers to send, send them
			std::vector<unsigned char*>::iterator itr_buf = buffers.at(i)->begin();
			std::vector<unsigned int>::iterator itr_len = buffer_lengths.at(i)->begin();
			if(itr_buf < buffers.at(i)->end()) {
				unsigned char* buffer = *itr_buf;
				unsigned int length = *itr_len;

				logger::log("SerialProcessor", "Sending Buffer", getStringHex(buffer, length), "");
				serials.at(i)->readWrite(buffer, length);

				buffers.at(i)->erase(itr_buf);
				buffer_lengths.at(i)->erase(itr_len);

				rec_bytes.at(i) = 0;
				recievings.at(i) = true;
			}
		}
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void SerialProcessor::finishBehaviours() {
	std::vector<Behaviour*>::iterator itr = coms::behaviour_list_current.begin();
	while(itr < coms::behaviour_list_current.end()) {
		coms::behaviour_list_execute.push_back(*itr);
		itr = coms::behaviour_list_current.erase(itr);
	}
}

std::string SerialProcessor::getStringHex(unsigned char* buffer, size_t length) {
	char hex[length * 2 + 1];
	for(size_t i = 0; i < length; i++) {
   		sprintf(hex + 2 * i, "%.2x", buffer[i]);
	}
	hex[length * 2 + 1] = '\0';

	char output[100];
	sprintf(output, "0x%s", hex);
	std::string s(output);
	return s;
}

bool SerialProcessor::findCommand(unsigned char* buffer) {
	unsigned char* buf = new unsigned char[serial::buffer_size];
	overwriteBytes(buf, 0, buffer, 0, serial::buffer_size);

	std::vector<size_t> patterns;
	std::vector<size_t> lengths;
	bool start_bypte = 0;
	size_t counter = 0;
	bool on_one = false;

	for(size_t i = 0; i < serial::buffer_size; i++) {
		// If found pattern byte
		if(buffer[i] == PATTERN) {
			// If not on pattern yet
			if(!on_one) {
				on_one = true;
				start_bypte = i;
			// If on pattern add to counter
			} else if(on_one) {
				counter++;
			}
		}
		// If on one but less length than pattern
		if(on_one && (counter < serial::pattern_len || counter > serial::pattern_len)) {
			start_bypte = 0;
			on_one = false;
		}
		// If on one which is longer than pattern length
		if(on_one && counter == serial::pattern_len) {
			patterns.push_back(start_bypte);
			lengths.push_back(counter);
			start_bypte = 0;
			on_one = false;
		}	
	}
	if(patterns.size() == 2) {
		overwriteBytes(buffer, 0, buf, patterns.at(0) + lengths.at(0), patterns.at(1) - patterns.at(0) - lengths.at(0));
		delete(buf);
		return true;
	}
	delete(buf);
	return false;
}

size_t SerialProcessor::overwriteBytes(unsigned char* buffer, size_t byte_start, unsigned char* buf, size_t inc_start, size_t byte_inc) {
	for(size_t i = 0; i < byte_inc; i++) {
		buffer[byte_start + i] = buf[inc_start + i];
	}
	return byte_inc;
}

size_t SerialProcessor::encodePattern(unsigned char* buffer, size_t byte_start) {
	buffer[byte_start + 0] = PATTERN;
	buffer[byte_start + 1] = PATTERN;
	buffer[byte_start + 2] = PATTERN;
	buffer[byte_start + 3] = PATTERN;
	buffer[byte_start + 4] = PATTERN;
	buffer[byte_start + 5] = PATTERN;
	buffer[byte_start + 6] = PATTERN;
	buffer[byte_start + 7] = PATTERN;
	buffer[byte_start + 8] = PATTERN;
	buffer[byte_start + 9] = PATTERN;
	return serial::pattern_len;
}

size_t SerialProcessor::encodeInt16(unsigned char* buffer, size_t byte_start, int16_t num) {
	buffer[byte_start + 0] = (num >> 8) & 0xFF;
	buffer[byte_start + 1] = num & 0xFF;
	return sizeof(int16_t);
}

size_t SerialProcessor::encodeInt32(unsigned char* buffer, size_t byte_start, int32_t num) {
	buffer[byte_start + 0] = (num >> 24) & 0xFF;
	buffer[byte_start + 1] = (num >> 16) & 0xFF;
	buffer[byte_start + 2] = (num >> 8) & 0xFF;
	buffer[byte_start + 3] = num & 0xFF;
	return sizeof(int32_t);
}

size_t SerialProcessor::encodeFloat(unsigned char* buffer, size_t byte_start, float num) {
	float_i number = *(float_i*) &num;
	buffer[byte_start + 0] = (number >> 24) & 0xFF;
	buffer[byte_start + 1] = (number >> 16) & 0xFF;
	buffer[byte_start + 2] = (number >> 8) & 0xFF;
	buffer[byte_start + 3] = number & 0xFF;
	return sizeof(float);
}

int16_t SerialProcessor::decodeInt16(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[2];
	buf[0] = buffer[byte_start + 1];
	buf[1] = buffer[byte_start + 0];
	int16_t number = *(int16_t*) &buf;
	
	return number;
}

int32_t SerialProcessor::decodeInt32(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[4];
	buf[0] = buffer[byte_start + 3];
	buf[1] = buffer[byte_start + 2];
	buf[2] = buffer[byte_start + 1];
	buf[3] = buffer[byte_start + 0];
	int32_t number = *(int32_t*) &buf;
	
	return number;
}

float SerialProcessor::decodeFloat(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[4];
	buf[0] = buffer[byte_start + 3];
	buf[1] = buffer[byte_start + 2];
	buf[2] = buffer[byte_start + 1];
	buf[3] = buffer[byte_start + 0];
	float number = *(float*) &buf;
	
	return number;
}