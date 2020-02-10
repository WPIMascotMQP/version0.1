#ifndef MOTORSTATUS_H
#define MOTORSTATUS_H

#include <cmath>
#include <vector>

class MotorTracker {
public:
	MotorTracker();
	~MotorTracker();

	bool EStop();
	void add(double current, double temperature, double position);
	void addToHistory(std::vector<double> history, double info);

	double minimum;
	double maximum;
	double maximum_physical;
	double ratio; // Motor Rad to Physical Rad
	double neutral;
	double neutral_physical;

protected:
	std::vector<double> current_history;
	std::vector<double> temperature_history;
	std::vector<double> position_history;

private:

};

namespace math {
	extern double PI;
}
#endif
