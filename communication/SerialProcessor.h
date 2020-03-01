/**
 @file SerialProcessor.h
 @class SerialProcessor
 @brief The SerialProcessor class handles the overhead of the SPI communication
 by encoding motor positions or other commands, sending those to the SPI Slaves,
 decoding commands recieved by from the SPI Slaves, and executing apporiate actions
 based on those recieved commands.

 This SerialProcessor assumes that all buffers are sucessfully written to the ESP32
 and that all recieved buffers will be complete when checking. If packets are lost,
 the robot will self correct since it uses absolute positions.

 @author Jonathan Chang
 @version 0.0.1
 @date 18/02/2020
*/

#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include <cstddef>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <wiringPiSPI.h>

#include "../behaviourtree/Behaviour.h"
#include "../processors/MotorProcessor.h"
#include "../processors/SensorProcessor.h"
#include "../kinematics/Movement.h"
#include "SpiSlave.h"

// Immediate variable type between float and long
typedef long float_i;

// Flags for the flag byte of each command
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

// Holds the hex representation of each command
enum cmds {
	PATTERN = 0xFF,
	ESTOP = 0x00,
	MOTORPOSITION = 0x01,
	REQUESTCMD = 0x02,
	HANDSHAKE = 0x03,

	TOUCHINFO = 0x10,
	AUDIOINFO = 0x20,

};

// Holds the byte index for different parts of the commmand
enum byte_index {
	flag_byte = 0,
	cmd_byte = 1,
};

// Holds the serial index of the motor and sensir SPI slaves
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
	void handleCommand(unsigned char* buffer);

	void encodePosition(std::shared_ptr<Position> pos, std::shared_ptr<Position> delay);
	size_t overwriteBytes(unsigned char* buffer, size_t byte_start, unsigned char* buf, size_t inc_start, size_t byte_inc);
	size_t encodePattern(unsigned char* buffer, size_t byte_start);
	size_t encodeInt8(unsigned char* buffer, size_t byte_start, int8_t num);
	size_t encodeInt16(unsigned char* buffer, size_t byte_start, int16_t num);
	size_t encodeInt32(unsigned char* buffer, size_t byte_start, int32_t num);
	size_t encodeFloat(unsigned char* buffer, size_t byte_start, float num);

	int8_t decodeInt8(unsigned char* buffer, size_t byte_start);
	int16_t decodeInt16(unsigned char* buffer, size_t byte_start);
	int32_t decodeInt32(unsigned char* buffer, size_t byte_start);
	float decodeFloat(unsigned char* buffer, size_t byte_start);

protected:
	std::vector<SpiSlave*> serials;

	std::vector<std::vector<unsigned char*>*> buffers;
	std::vector<std::vector<size_t>*> buffer_lengths;

private:
};

namespace serial {
	extern SerialProcessor serial;

	extern std::vector<std::shared_ptr<Movement>> movements_to_send; // Movements to send out
	extern std::mutex movement_lock;

	extern std::vector<std::shared_ptr<Position>> positions_to_send; // Positions to send out
	extern std::mutex position_lock;

	extern int num_serials;
	extern std::shared_ptr<Position> standard_delay;
}

#endif
