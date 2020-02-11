/**
 @file Logger.h
 @brief The Logger namespace
 @details This Logger namespace will handle verbose printout and log file
 handling inside the logger namespace

 @author Jonathan Chang
 @version 0.0.1
 @date 08/1/2020
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

namespace logger {
	void verbose(std::string verb);
	void verbose(std::string verb, double value);
	void startLog();
	void log(std::string log);
	void log(std::string log, std::string key, double value, std::string comment);
	void endLog();
	unsigned int getLogFolderSize();
}

#endif
