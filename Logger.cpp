#include "Logger.h"

namespace logger {
	std::ofstream* log_file;
}

void verbose(std::string verb) {
	std::cout << verb << std::endl;
}

void startLog() {
	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	std::ostringstream strs;
	strs << "logs/" << std::ctime(&start_time) << ".txt";
	logger::log_file = new std::ofstream(strs.str());
}

void log(std::string log) {
	auto end = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(end);
	*logger::log_file << std::ctime(&start_time) << " |" << log << std::endl;
}

void endLog() {
	logger::log_file->close();
}