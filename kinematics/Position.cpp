#include "Position.h"

/**
 CONSTRUCTOR
 @param by The base yaw position
 @param bp The base pitch position
 @param ny The neck yaw position
 @param np The neck pitch postiion
*/
Position::Position(double by, double bp, double ny, double np) {
	base_yaw = by;
	base_pitch = bp;
	neck_yaw = ny;
	neck_pitch = np;
}

/**
 DECONSTRUCTOR
*/
Position::~Position() {

}
