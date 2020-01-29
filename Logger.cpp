#include "Logger.h"

namespace logger {
	std::ofstream* log_file;
	unsigned int max_log_size = 5;
	const char* time_format = "%a %b %d %Y %H꞉%M꞉%S";

	void verbose(std::string verb) {
		std::cout << verb << std::endl;
	}

	std::string getDateTime() {
		auto start = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(start);
		std::tm tm = *std::localtime(&time);

		std::ostringstream strs;
		strs << std::put_time(&tm, "%a %b %d %Y %H꞉%M꞉%S");
		return strs.str();
	}

	void startLog() {
		std::ostringstream strs;
		strs << "logs/" << getDateTime() << ".txt";
		log_file = new std::ofstream(strs.str());
	}

	void log(std::string log) {
		*log_file << getDateTime() << " |" << log << std::endl;
	}

	void endLog() {
		logger::log_file->close();

		std::vector<std::string> paths;
		std::vector<time_t> times;

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

		std::vector<std::string>::iterator itr_path = paths.begin();
		while(itr_path < paths.end()) {
			std::string path = *itr_path;

			std::tm tm = {};
			const char* c = path.substr(0, path.find_last_of(".")).c_str();
			verbose(path.substr(0, path.find_last_of(".")));
			strptime(c, "%a %b %d %Y %H꞉%M꞉%S", &tm);
			auto t_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
			std::time_t time = std::chrono::system_clock::to_time_t(t_time);
			std::cout << time << std::endl;
			times.push_back(time);
			itr_path++;
		}
		
		verbose("" + getLogFolderSize());
		while(getLogFolderSize() > max_log_size) {
			std::vector<std::string>::iterator oldest_path = paths.begin();
			std::vector<time_t>::iterator oldest_time = times.begin();
			std::vector<std::string>::iterator itr_path = paths.begin();
			std::vector<time_t>::iterator itr_time = times.begin();
			while(itr_time < times.end()) {
				time_t time = *itr_time;
				time_t old_time = *oldest_time;
				if(std::difftime(time, old_time) > 0.0) {
					oldest_path = itr_path;
					oldest_time = itr_time;
				}

				itr_path++;
				itr_time++;
			}
			std::string oldest_file = "logs/" + *oldest_path;
			const char* c = oldest_file.c_str();
			verbose("Removing | " + oldest_file);
			remove(c);
			paths.erase(oldest_path);
			times.erase(oldest_time);
		}
	}

	unsigned int getLogFolderSize() {
		int count = 0;
		DIR *logs;
		struct dirent *log;
		logs = opendir("logs/");
		if(logs) {
			while((log = readdir(logs)) != NULL) {
				count++;
			}
			closedir(logs);
		}
		return count;
	}
}