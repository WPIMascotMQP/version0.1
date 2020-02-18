#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include <cstddef>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../behaviourtree/Behaviour.h"
#include "../processors/SensorProcessor.h"
#include "SpiSlave.h"

typedef long float_i;

enum flags {
	FLAG1 = 0x80, // 10000000
	FLAG2 = 0x40, // 01000000
	FLAG3 = 0x20, // 00100000
	FLAG4 = 0x10, // 00010000
	FLAG5 = 0x08, // 00001000
	FLAG6 = 0x04, // 00000100
	FLAG7 = 0x02, // 00000010
	FLAG8 = 0x01, // 00000001
};

enum cmds {
	PATTERN = 0xFF,
	MOTORPOSITION = 0x01,

};

enum serial_index {
	motor_serial = 0,
	sensor_serial = 1,
};

class SerialProcessor : public SensorProcessor{
public:
	SerialProcessor(int num_serials);
	SerialProcessor() : SerialProcessor(0) {};
	~SerialProcessor();

	void startThread();
	void killThread();
	void process();

	void finishBehaviours();

	std::string getStringHex(unsigned char* buffer, size_t length);
	bool findCommand(unsigned char* buffer);

	size_t overwriteBytes(unsigned char* buffer, size_t byte_start, unsigned char* buf, size_t inc_start, size_t byte_inc);
	size_t encodePattern(unsigned char* buffer, size_t byte_start);
	size_t encodeInt16(unsigned char* buffer, size_t byte_start, int16_t num);
	size_t encodeInt32(unsigned char* buffer, size_t byte_start, int32_t num);
	size_t encodeFloat(unsigned char* buffer, size_t byte_start, float num);

	int16_t decodeInt16(unsigned char* buffer, size_t byte_start);
	int32_t decodeInt32(unsigned char* buffer, size_t byte_start);
	float decodeFloat(unsigned char* buffer, size_t byte_start);

protected:
	std::vector<SpiSlave*> serials;

	std::vector<unsigned char*> buffers_rec;
	std::vector<size_t> rec_bytes;
	std::vector<int> counters;
	std::vector<bool> recievings;


	std::vector<std::vector<unsigned char*>*> buffers;
	std::vector<std::vector<size_t>*> buffer_lengths;

private:
};

namespace serial {
	extern SerialProcessor serial;

	extern std::vector<std::shared_ptr<Position>> positions_to_send;
	extern std::mutex position_lock;

	extern int num_serials;
}

#endif
