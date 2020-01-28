#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>

void verbose(std::string verb);
void startLog();
void log(std::string log);
void endLog();

#endif