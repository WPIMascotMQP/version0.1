#include "Position.h"

/**
 CONSTRUCTOR
 @param ny The neck yaw position
 @param np The neck pitch position
 @param hy The head yaw position
 @param hp The head pitch postiion
*/
Position::Position(double ny, double np, double hy, double hp) {
	neck_yaw = ny;
	neck_pitch = np;
	head_yaw = hy;
	head_pitch = hp;
}

/**
 DECONSTRUCTOR
*/
Position::~Position() {

}
