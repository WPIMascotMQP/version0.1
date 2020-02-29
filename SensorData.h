/**
 @file SensorData.h
 @class SensorData
 @brief The SensorData class holds all sensor and joint data
 @details This SensorData functions as a data object holding on to
 all relavent sensor and positial data

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019
*/

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <string>

#include "processors/AudioProcessor.h"
#include "processors/MotorProcessor.h"
#include "processors/VisualProcessor.h"
#include "kinematics/Position.h"

class SensorData {
public:
	SensorData(double ny, double np, double hy, double hp);
	SensorData() : SensorData(0.0, 0.0, 0.0,0.0) {};
	~SensorData();

	std::string getInput();
	double getLastAudio();
	std::shared_ptr<Position> getCurrentStepPosition();
	bool getTouched();

	void setInput(std::string inp);
	void setTouched(bool touch);
	void setCurrentPosition(Position* pos);

protected:
	bool touched;
	std::string input;
	Position current_position;

};

namespace data {
	extern SensorData sensor_data;
	extern int centerVisualWidth;
	extern int centerVisualHeight;
}
#endif
