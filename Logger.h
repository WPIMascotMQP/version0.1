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
	void startLog();
	void log(std::string log);
	void endLog();
	unsigned int getLogFolderSize();
}

#endif