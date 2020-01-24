#include "Position.h"

/**
 CONSTRUCTOR
 @param x The x position
 @param y The y position
 @param z The z position
*/
Position::Position(double x, double y, double z) {
	x_position = x;
	y_position = y;
	z_position = z;
}

/**
 DECONSTRUCTOR
*/
Position::~Position() {

}

/**
 Sets the X position
 @param x The X position
*/
void Position::setXPosition(double x) {
	x_position = x;
}

/**
 Sets the X position
 @return The X position
*/
double Position::getXPosition() {
	return x_position;
}

/**
 Sets the Y position
 @param y The Y position
*/
void Position::setYPosition(double y) {
	y_position = y;
}

/**
 Sets the Y position
 @return The Y position
*/
double Position::getYPosition() {
	return y_position;
}

/**
 Sets the Z position
 @param z The Z position
*/
void Position::setZPosition(double z) {
	z_position = z;
}

/**
 Sets the Z position
 @return The Z position
*/
double Position::getZPosition() {
	return z_position;
}
