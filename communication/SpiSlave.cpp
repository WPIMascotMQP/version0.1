#include "SpiSlave.h"

namespace spi {
    extern const int buf_size;
    extern const int bus_speed;
}

SpiSlave::SpiSlave(int dev) {
    device = dev;
    /*if(wiringPiSPISetup(device, spi::bus_speed) < 0) {
        std::ostringstream strs;
        strs << "Unable to Start SPI on Device: " << device;
        logger::log(strs.str());
    }*/
}

SpiSlave::~SpiSlave() {

}

int SpiSlave::readWrite(unsigned char* buf, unsigned int length) {
    return 0; //wiringPiSPIDataRW(device, buf, length);
}
