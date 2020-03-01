/**
 @file SpiSlave.h
 @class SpiSlave
 @brief The SpiSlave class reading and writing of a buffer from the SPI communication

 @author Jonathan Chang
 @version 0.0.1
 @date 18/02/2020
*/

#ifndef SPISLAVE_H
#define SPISLAVE_H

#include <iostream>
#include <errno.h>
#include <sstream>
#include <string>
#include <wiringPiSPI.h>
#include <unistd.h>

#include "../Logger.h"

namespace spi {
    const int buf_size = 32;
    const int bus_speed = 500000;
}

class SpiSlave {
public:
    SpiSlave(int dev);
    SpiSlave() : SpiSlave(0) {};
    ~SpiSlave();

    int readWrite(unsigned char* buf, unsigned int length);
protected:

private:
    int device;
    unsigned char buffer[spi::buf_size];
};

#endif
