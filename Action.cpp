#include "Action.h"

/**
 CONSTRUCTOR
 @param dX The change in X
 @param dY The change in Y
 @param dZ The change in Z
*/
Action::Action(double dX, double dY, double dZ) {
	deltaX = dX;
	deltaY = dY;
	deltaZ = dZ;
}

/**
 DECONSTRUCTOR
*/
Action::~Action() {

}

/**
 Gets the DeltaX
 @return The deltaX
*/
double Action::getDeltaX() {
	return deltaX;
}

/**
 Gets the DeltaY
 @return The deltaY
*/
double Action::getDeltaY() {
	return deltaY;
}

/**
 Gets the DeltaZ
 @return The deltaZ
*/
double Action::getDeltaZ() {
	return deltaZ;
}