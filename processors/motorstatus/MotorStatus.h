#ifndef MOTORSTATUS_H
#define MOTORSTATUS_H

#include <vector>

class MotorStatus {
public:
	MotorStatus();
	~MotorStatus();

	bool EStop();
	void add(double current, double temperature, double position);
	void addToHistory(std::vector<double> history, double info);
protected:
	std::vector<double> current_history;
	std::vector<double> temperature_history;
	std::vector<double> position_history;
private:

};

#endif