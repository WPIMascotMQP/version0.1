#ifndef MOTORSTATUS_H
#define MOTORSTATUS_H

#include <vector>

class MotorTracker {
public:
	MotorTracker();
	~MotorTracker();

	bool EStop();
	void add(double current, double temperature, double position);
	void addToHistory(std::vector<double> history, double info);

	double maximum_physical;
	double minimum;
	double maximum;
	double ratio;

protected:
	std::vector<double> current_history;
	std::vector<double> temperature_history;
	std::vector<double> position_history;


private:

};

#endif
