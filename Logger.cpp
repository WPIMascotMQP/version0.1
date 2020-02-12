#include "Logger.h"

namespace logger {
	std::ofstream* log_file;
	unsigned int max_log_size = 5;
	unsigned int print_width = 40;

	/**
	 The verbose printout
	 Used to control all verbose functions
	 @param verb The string to print out
	 */
	void verbose(std::string verb) {
		std::cout << verb << std::endl;
	}

	void verbose(std::string verb, double value) {
		std::cout << std::setw(print_width) << std::left << verb <<
			std::setw(print_width) << std::left << value << std::endl;
	}

	/**
	 Gets the Date Time Stamp at the current time
	 @return The Date Time as a string
	 */
	std::string getDateTime() {
		auto start = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(start);
		std::tm tm = *std::localtime(&time);

		std::ostringstream strs;
		strs << std::put_time(&tm, "%a %b %d %Y %H꞉%M꞉%S");
		return strs.str();
	}

	/**
	 Starts the log file at the current time
	 */
	void startLog() {
		std::ostringstream strs;
		strs << "logs/" << getDateTime() << ".txt";
		log_file = new std::ofstream(strs.str());
	}

	/**
	 Logs the given string with a DateTime stamp
	 @param log The string to log
	 */
	void log(std::string log) {
		*log_file << getDateTime() << " | " << log << std::endl;
	}

	/**
	 Logs the given string with a DateTime stamp
	 @param log The string to log
	 */
	void log(std::string log, std::string key, double value, std::string comment) {
		*log_file << getDateTime() << " | " <<
		 	std::setw(print_width) << std::left << log <<
			std::setw(print_width) << std::left << key <<
			std::setw(print_width) << std::left << value <<
			std::setw(print_width) << std::left << comment << std::endl;
	}

	/**
	 Logs the given string with a DateTime stamp
	 @param log The string to log
	 */
	void log(std::string log, std::string key, std::string value, std::string comment) {
		*log_file << getDateTime() << " | " <<
			std::setw(print_width) << std::left << log <<
			std::setw(print_width) << std::left << key <<
			std::setw(print_width) << std::left << value <<
			std::setw(print_width) << std::left << comment << std::endl;
	}

	/**
	 Ends the current log and removes old log files
	 */
	void endLog() {
		std::vector<std::string> paths;
		std::vector<time_t> times;

		// Get all current log files
		DIR *logs;
		struct dirent *log;
		logs = opendir("logs/");
		if(logs) {
			while((log = readdir(logs)) != NULL) {
				if(strcmp(log->d_name, ".")  == 0 || strcmp(log->d_name, "..") == 0) {
					continue;
				}
				paths.push_back(std::string(log->d_name));
			}
			closedir(logs);
		}

		// Read in the log date from the file names
		std::vector<std::string>::iterator itr_path = paths.begin();
		while(itr_path < paths.end()) {
			std::string path = *itr_path;

			std::tm tm = {};
			std::stringstream ss(path.substr(0, path.find_last_of(".")).c_str());
			ss >> std::get_time(&tm, "%a %b %d %Y %H꞉%M꞉%S");
			auto t_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
			std::time_t time = std::chrono::system_clock::to_time_t(t_time);

			times.push_back(time);
			itr_path++;
		}

		// Removes oldest log files until folder size down to max_log_size
		while(getLogFolderSize() > max_log_size) {
			std::vector<std::string>::iterator oldest_path = paths.begin();
			std::vector<time_t>::iterator oldest_time = times.begin();
			std::vector<std::string>::iterator itr_path = paths.begin();
			std::vector<time_t>::iterator itr_time = times.begin();
			// Find oldest log file
			while(itr_time < times.end()) {
				time_t time = *itr_time;
				time_t old_time = *oldest_time;
				if(std::difftime(time, old_time) < 0.0) {
					oldest_path = itr_path;
					oldest_time = itr_time;
				}

				itr_path++;
				itr_time++;
			}
			// Remove oldest log file
			std::string oldest_file = "logs/" + *oldest_path;
			const char* c = oldest_file.c_str();
			logger::log("Removing: " + oldest_file);
			remove(c);
			paths.erase(oldest_path);
			times.erase(oldest_time);
		}

		logger::log_file->close();
	}

	/**
	 Gets the number of log files inside the log folder
	 @return The number of log files inside the log folder
	 */
	unsigned int getLogFolderSize() {
		unsigned int count = 0;
		DIR *logs;
		struct dirent *log;
		logs = opendir("logs/");
		if(logs) {
			while((log = readdir(logs)) != NULL) {
				if(strcmp(log->d_name, ".")  == 0 || strcmp(log->d_name, "..") == 0) {
					continue;
				}
				count++;
			}
			closedir(logs);
		}
		return (unsigned int) count;
	}
}
