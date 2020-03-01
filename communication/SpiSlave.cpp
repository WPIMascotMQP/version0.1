#include "SpiSlave.h"

namespace spi {
    extern const int buf_size;
    extern const int bus_speed;
}

/**
 CONSTRUCTOR
 The contructor for the SPI Slave
 @param dev The channel number to read and write from
 */
SpiSlave::SpiSlave(int dev) {
    device = dev;
    if(wiringPiSPISetup(device, spi::bus_speed) < 0) {
        std::ostringstream strs;
        strs << "Unable to Start SPI on Device: " << device;
        logger::log(strs.str());
    }
}

/**
 DECONSTRUCTOR
 */
SpiSlave::~SpiSlave() {

}

/**
 Reads and Writes from the SPI Buffer
 @param buf The buffer to send and write into
 @param length The number of bytes to send
 @return int Unknown but could be number of bytes written into the buffer
 */
int SpiSlave::readWrite(unsigned char* buf, unsigned int length) {
    return wiringPiSPIDataRW(device, buf, length);
}
