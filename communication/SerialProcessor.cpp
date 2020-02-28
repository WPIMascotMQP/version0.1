#include "SerialProcessor.h"

#include "../processors/MotorProcessor.h"

namespace serial {
	int num_serials = 2;
	SerialProcessor serial(num_serials);

	std::vector<std::shared_ptr<Movement>> movements_to_send;
	std::mutex movement_lock;

	std::vector<std::shared_ptr<Position>> positions_to_send;
	std::mutex position_lock;

	size_t buffer_size = 64;
	size_t pattern_len = 10;

	std::shared_ptr<Position> standard_delay(new Position(400, 400, 400, 400));
}

/**
 CONSTRUCTOR
 Constructors and sets up the serial processor
 @param num_serial This param is ignored
*/
SerialProcessor::SerialProcessor(int num_serials) {
	for(int i = 0; i < serial::num_serials; i++) {
		serials.push_back(new SpiSlave(i));
		buffers.push_back(new std::vector<unsigned char*>());
		buffer_lengths.push_back(new std::vector<size_t>());
	}
	std::srand(std::time(0));
}

/**
 DECONSTRUCTOR
*/
SerialProcessor::~SerialProcessor() {

}

/**
 Starts the Serial Processing Thread
*/
void SerialProcessor::startThread() {
	kill = false;
	pthread = std::thread(&SerialProcessor::processWrapper, this);
	logger::log("SerialProcessor Thread Started");
}

/**
 Kills the Serial Processing Thread
*/
void SerialProcessor::killThread() {
	SensorProcessor::killThread();
	logger::log("SerialProcessor Thread Killed");
}

/**
 The main processing loop for serial Processing
 If there are positions to send, encode the first and add it to list of buffers to send
 If it is recieving from an SPI slave, reads in the buffer and looks for a command
 If not recieveding, sends out the next buffer
*/
void SerialProcessor::process() {
	serial::position_lock.lock();

	// If have posiitons send, encode them
	std::vector<std::shared_ptr<Position>>::iterator itr_pos = serial::positions_to_send.begin();
	if(itr_pos < serial::positions_to_send.end()) {
		std::shared_ptr<Position> pos = *itr_pos;
		logger::log("SerialProcessor", "Encoding Position", pos->toString(), "");
		encodePosition(pos, serial::standard_delay);
		logger::log("SerialProcessor", "Encoded Position", pos->toString(), "");
		serial::positions_to_send.erase(itr_pos);
	}
	serial::position_lock.unlock();

	serial::movement_lock.lock();

	// If have movements to send, encode them
	std::vector<std::shared_ptr<Movement>>::iterator itr_mov = serial::movements_to_send.begin();
	if(itr_mov < serial::movements_to_send.end()) {
		std::shared_ptr<Movement> mov = *itr_mov;
		logger::log("SerialProcessor", "Encoding Movement", mov->getSetPosition()->toString(), mov->getDelay()->toString());
		encodePosition(mov->getSetPosition(), mov->getDelay());
		logger::log("SerialProcessor", "Encoded Movement", mov->getSetPosition()->toString(), mov->getDelay()->toString());
		serial::movements_to_send.erase(itr_mov);
	}

	serial::movement_lock.unlock();

	// For each SPI serial
	for(int i = 0; i < serial::num_serials; i++) {
		unsigned char* buffer;
		unsigned char* buffer_copy = new unsigned char[serial::buffer_size];
		bool buffer_set = false;
		// If have buffers to send, send them
		std::vector<unsigned char*>::iterator itr_buf = buffers.at(i)->begin();
		std::vector<unsigned int>::iterator itr_len = buffer_lengths.at(i)->begin();
		if(itr_buf < buffers.at(i)->end()) {
			buffer = *itr_buf;
			buffer_set = true;
			unsigned int length = *itr_len;
			overwriteBytes(buffer_copy, 0, buffer, 0, serial::buffer_size);

			logger::log("SerialProcessor", "Sending Buffer", getStringHex(buffer, length), "");
			serials.at(i)->readWrite(buffer, length);

			buffers.at(i)->erase(itr_buf);
			buffer_lengths.at(i)->erase(itr_len);
		}
		// If did not send out a cmd
		if(!buffer_set) {
			buffer = new unsigned char[serial::buffer_size];
			overwriteBytes(buffer_copy, 0, buffer, 0, serial::buffer_size);
			serials.at(i)->readWrite(buffer, serial::buffer_size);
		}

		// Testing code
		//overwriteBytes(buffer, 7, buffers.at(i)->at(0), 0, buffer_lengths.at(i)->at(0));

		// TEST IF COMPLETE
		if(findCommand(buffer) && (!memcmp(buffer, buffer_copy, serial::buffer_size))) {
			handleCommand(buffer);
		}
		delete(buffer);
		delete(buffer_copy);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/**
 Marks all behaviours in current list as complete and moves them to the execute list
 */
void SerialProcessor::finishBehaviours() {
	std::vector<Behaviour*>::iterator itr = coms::behaviour_list_current.begin();
	while(itr < coms::behaviour_list_current.end()) {
		coms::behaviour_list_execute.push_back(*itr);
		itr = coms::behaviour_list_current.erase(itr);
	}
}

/**
 Handles the command in the given buffer
 @param buffer The buffer where the command is (must start at beginning of buffer)
 */
void SerialProcessor::handleCommand(unsigned char* buffer) {
	logger::log("SerialProcessor", "Recieved Command", getStringHex(buffer, serial::buffer_size), "");
	if(buffer[cmd_byte] == MOTORPOSITION) {
		// If command is the current motor position
		size_t current_byte = 2;
		int index = (int) decodeInt16(buffer, current_byte);
		current_byte += 2;
		double radians = (double) decodeFloat(buffer, current_byte);
		processor::mp.addRadiansHistory(index, radians);

		std::ostringstream strs;
		strs << radians;
		std::ostringstream strsIndex;
		strsIndex << index;
		logger::log("SerialProcessor", "Recieved Motor Radians", strsIndex.str(), strs.str());
	}
}

/**
 Gets the std::string represention of the given buffer
 @param buffer The given buffer to represent
 @param length The length of the buffer to represent
 @return The std::string hex value
 */
std::string SerialProcessor::getStringHex(unsigned char* buffer, size_t length) {
	char hex[length * 2 + 1];
	for(size_t i = 0; i < length; i++) {
   		sprintf(hex + 2 * i, "%.2x", buffer[i]);
	}
	hex[length * 2 + 1] = '\0';

	char output[length * 2 + 1];
	sprintf(output, "0x%s", hex);
	std::string s(output);
	return s;
}

/**
 Finds a valid command in the given buffer
 If a command was found, writies that command into the beginning of the buffer
 @param buffer
 @return Whether a command was found or not
 */
bool SerialProcessor::findCommand(unsigned char* buffer) {
	unsigned char* buf = new unsigned char[serial::buffer_size];
	overwriteBytes(buf, 0, buffer, 0, serial::buffer_size);

	std::vector<size_t> patterns;
	std::vector<size_t> lengths;
	size_t start_bypte = 0;
	size_t counter = 0;
	bool on_one = false;

	// Parse throught each byte in the buffer
	for(size_t i = 0; i < serial::buffer_size; i++) {
		// If found pattern byte
		if(buffer[i] == PATTERN) {
			// If not on pattern yet
			if(!on_one) {
				on_one = true;
				start_bypte = i;
				counter++;
			// If on pattern add to counter
			} else if(on_one) {
				counter++;
			}
		} else {
			// If on one but less length or longer than pattern length
			if(on_one && (counter < serial::pattern_len || counter > serial::pattern_len)) {
				start_bypte = 0;
				counter = 0;
				on_one = false;
			}
			// If on one which is exactly  pattern length
			if(on_one && counter == serial::pattern_len) {
				patterns.push_back(start_bypte);
				lengths.push_back(counter);
				start_bypte = 0;
				counter = 0;
				on_one = false;
			}
		}
	}
	if(patterns.size() == 2) {
		overwriteBytes(buffer, 0, buf, patterns.at(0) + lengths.at(0),
			patterns.at(1) - patterns.at(0) - lengths.at(0));
		delete(buf);
		return true;
	}
	delete(buf);
	return false;
}

/**
 Encodes a posiiton command with the given delay
 and pushes it onto the buffers_to_send
 @param pos The position to encode
 @param delay The delay for each of the axises
 */
void SerialProcessor::encodePosition(std::shared_ptr<Position> pos, std::shared_ptr<Position> delay) {
	for(int i = 0; i < motorData::num_motors; i++) {
		unsigned char* buffer = new unsigned char[serial::buffer_size];
		size_t current_byte = 0;

		current_byte += encodePattern(buffer, current_byte);
		buffer[current_byte++] = 0x00; // Flag Byte
		buffer[current_byte++] = MOTORPOSITION;
		current_byte += encodeInt16(buffer, current_byte, i);
		current_byte += encodeFloat(buffer, current_byte, pos->getAtIndex(i));
		current_byte += encodeInt16(buffer, current_byte, delay->getAtIndex(i));
		current_byte += encodePattern(buffer, current_byte);

		buffers.at(motor_serial)->push_back(buffer);
		buffer_lengths.at(motor_serial)->push_back(current_byte);

		logger::log("SerialProcessor", "Encoded Command", getStringHex(buffer, current_byte), "");
	}
}

/**
 Overwrites the bytes in the given buffer with bytes from the other given buffer
 @param buffer The buffer to write into
 @param byte_start The starting location to write to
 @param buf The buffer to write from
 @param int_start The starting location to write from
 @param byte_inc The number of bytes to write
 @return The number of bytes written
*/
size_t SerialProcessor::overwriteBytes(unsigned char* buffer, size_t byte_start, unsigned char* buf, size_t inc_start, size_t byte_inc) {
	for(size_t i = 0; i < byte_inc; i++) {
		buffer[byte_start + i] = buf[inc_start + i];
	}
	return byte_inc;
}

/**
 Writes the pattern into the given buffer at the given position
 @param buffer The buffer to write into
 @param byte_start The starting byte to writing into
 @return The number of bytes written
 */
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

/**
 Encodes a 16 bit int into the given buffer
 @param buffer The buffer to write into
 @param byte_start The starting byte to write into
 @param num The 16 bit int to encode
 @return The number of bytes encoded
 */
size_t SerialProcessor::encodeInt16(unsigned char* buffer, size_t byte_start, int16_t num) {
	buffer[byte_start + 0] = (num >> 8) & 0xFF;
	buffer[byte_start + 1] = num & 0xFF;
	return sizeof(int16_t);
}

/**
 Encodes a 32 bit int into the given buffer
 @param buffer The buffer to write into
 @param byte_start The starting byte to write into
 @param num The 32 bit int to encode
 @return The number of bytes encoded
 */
size_t SerialProcessor::encodeInt32(unsigned char* buffer, size_t byte_start, int32_t num) {
	buffer[byte_start + 0] = (num >> 24) & 0xFF;
	buffer[byte_start + 1] = (num >> 16) & 0xFF;
	buffer[byte_start + 2] = (num >> 8) & 0xFF;
	buffer[byte_start + 3] = num & 0xFF;
	return sizeof(int32_t);
}

/**
 Encodes a 32 bit float into the given buffer
 @param buffer The buffer to write into
 @param byte_start The starting byte to write into
 @param num The 32 bit float to encode
 @return The number of bytes encoded
 */
size_t SerialProcessor::encodeFloat(unsigned char* buffer, size_t byte_start, float num) {
	float_i number = *(float_i*) &num;
	buffer[byte_start + 0] = (number >> 24) & 0xFF;
	buffer[byte_start + 1] = (number >> 16) & 0xFF;
	buffer[byte_start + 2] = (number >> 8) & 0xFF;
	buffer[byte_start + 3] = number & 0xFF;
	return sizeof(float);
}

/**
 Decodes a 16 bit int from given buffer
 @param buffer The buffer to read from
 @param byte_start The starting byte to read from
 @return The 16 bit int decoded
 */
int16_t SerialProcessor::decodeInt16(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[2];
	buf[0] = buffer[byte_start + 1];
	buf[1] = buffer[byte_start + 0];
	int16_t number = *(int16_t*) &buf;

	return number;
}

/**
 Decodes a 32 bit int from given buffer
 @param buffer The buffer to read from
 @param byte_start The starting byte to read from
 @return The 32 bit int decoded
 */
int32_t SerialProcessor::decodeInt32(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[4];
	buf[0] = buffer[byte_start + 3];
	buf[1] = buffer[byte_start + 2];
	buf[2] = buffer[byte_start + 1];
	buf[3] = buffer[byte_start + 0];
	int32_t number = *(int32_t*) &buf;

	return number;
}

/**
 Decodes a float from given buffer
 @param buffer The buffer to read from
 @param byte_start The starting byte to read from
 @return The float decoded
 */
float SerialProcessor::decodeFloat(unsigned char* buffer, size_t byte_start) {
	unsigned char buf[4];
	buf[0] = buffer[byte_start + 3];
	buf[1] = buffer[byte_start + 2];
	buf[2] = buffer[byte_start + 1];
	buf[3] = buffer[byte_start + 0];
	float number = *(float*) &buf;

	return number;
}
