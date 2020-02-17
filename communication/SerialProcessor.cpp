#include "SerialProcessor.h"

#include "../processors/MotorProcessor.h"

namespace serial {
	SerialProcessor serial(2);

	std::vector<std::shared_ptr<Position>> positions_to_send;
	std::mutex position_lock;

	unsigned int buffer_size = 64;

	int num_serials = 2;
}

SerialProcessor::SerialProcessor(int num_serials) {
	for(int i = 0; i < serial::num_serials; i++) {
		serials.push_back(new SpiSlave(i));
		buffers.push_back(new std::vector<unsigned char*>());
		buffer_lengths.push_back(new std::vector<size_t>());
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
			size_t current_byte = 1;
			current_byte += encodeInt16(buffer, current_byte, MOTORPOSITION);
			current_byte += encodeInt16(buffer, current_byte, 1);
			current_byte += encodeFloat(buffer, current_byte, pos->getAtIndex(i));
			buffers.at(motor_serial)->push_back(buffer);
			buffer_lengths.at(motor_serial)->push_back(current_byte);

			strs << "|" << getStringHex(buffer, current_byte);
		}
		logger::log("SerialProcessor", "Encoded Position", pos->toString(), strs.str());
		serial::positions_to_send.erase(itr);
	}
	serial::position_lock.unlock();

	for(int i = 0; i < serial::num_serials; i++) {
		std::vector<unsigned char*>::iterator itr_buf = buffers.at(i)->begin();
		std::vector<unsigned int>::iterator itr_len = buffer_lengths.at(i)->begin();
		if(itr_buf < buffers.at(i)->end()) {
			unsigned char* buffer = *itr_buf;
			unsigned int length = *itr_len;

			logger::log("SerialProcessor", "Sending Buffer", getStringHex(buffer, length), "");
			serials.at(i)->readWrite(buffer, length);
			logger::log("SerialProcessor", "Recieved Buffer", getStringHex(buffer, length), "");
			
			// Process Recieved Buffer
			delete(buffer);
			buffers.at(i)->erase(itr_buf);
			buffer_lengths.at(i)->erase(itr_len);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void SerialProcessor::finishBehaviours() {
	std::vector<Behaviour*>::iterator itr = coms::behaviour_list_current.begin();
	while(itr < coms::behaviour_list_current.end()) {
		coms::behaviour_list_execute.push_back(*itr);
		itr = coms::behaviour_list_current.erase(itr);
	}
}

std::string SerialProcessor::getStringHex(unsigned char* buffer, size_t length) {
	char output[50];
	sprintf(output, "%#0*x", length, buffer);
	std::string s(output);
	return s;
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
	long number = *(long*) &num;
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