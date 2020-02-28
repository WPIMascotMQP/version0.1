#include "Movement.h"

/**
 CONSTRUCTOR
*/
Movement::Movement() {
	setPosition = NULL;
	delay = NULL;
}

/**
 DECONSTRUCTOR
*/
Movement::~Movement() {

}

/**
 Sets the set point
 @param pos The set point
*/
void Movement::setSetPosition(std::shared_ptr<Position> pos) {
	setPosition = pos;
}

/**
 Gets the set point
 @return The set point
*/
std::shared_ptr<Position> Movement::getSetPosition() {
	return setPosition;
}

/**
 Sets the current point
 @param pos The current point
*/
void Movement::setDelay(std::shared_ptr<Position> pos) {
	delay = pos;
}

/**
 Gets the current point
 @return The current point
*/
std::shared_ptr<Position> Movement::getDelay() {
	return delay;
}

std::string Movement::toString() {
	std::ostringstream strs;
	strs << "( " << setPosition->toString() << ", " << delay->toString() << ")";
	return strs.str();
}
