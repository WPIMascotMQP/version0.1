#ifndef MOTORSTATUS_H
#define MOTORSTATUS_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include <string.h>

class MotorTracker {
public:
	MotorTracker();
	~MotorTracker();

	bool EStop();
	void add(int steps, double current, double temperature, double position);
	void addStepsHistory(int steps);
	void addToHistory(std::vector<double> history, double info);
	int getCurrentSteps();

	void setMinimum(int min);
	void setNeutral(int neu);
	void setMaximum(int max);
	void setNeutralPhysical(double neu_phy);
	void setMaximumPhysical(double max_phy);
	void setRatio(double rat);
	void setFlipped(bool flip);

	int getMinimum();
	int getNeutral();
	int getMaximum();
	double getNeutralPhysical();
	double getMaximumPhysical();
	double getRatio();
	bool getFlipped();

	std::string toString();

	friend std::ostream& operator<< (std::ostream& out, MotorTracker& mt) {
		std::string output = mt.toString();
		out << output;
		return out;
	}

protected:
	int minimum;
	int neutral;
	int maximum;
	double neutral_physical;
	double maximum_physical;
	double ratio; // Motor Rad to Physical Rad
	bool flipped;

	std::vector<int> steps_history;
	std::vector<double> current_history;
	std::vector<double> temperature_history;
	std::vector<double> position_history;

private:

};

namespace math {
	extern double PI;
}
#endif
