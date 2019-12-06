#include "Movement.h"

/**
 CONSTRUCTOR
*/
Movement::Movement() {
	setPoint = NULL;
	currentPoint = NULL;
	behaviour = NULL;
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
void Movement::setSetPoint(Position *pos) {
	setPoint = pos;
}

/**
 Gets the set point
 @return The set point
*/
Position *Movement::getSetPoint() {
	return setPoint;
}

/**
 Sets the current point
 @param pos The current point
*/
void Movement::setCurrentPoint(Position *pos) {
	currentPoint = pos;
}

/**
 Gets the current point
 @return The current point
*/
Position *Movement::getCurrentPoint() {
	return currentPoint;
}

/**
 Sets the behaviour
 @param beh The behaviour
*/
void Movement::setBehaviour(Behaviour* beh) {
	behaviour = beh;
}

/**
 Gets the behaviour
 @return The behaviour
*/
Behaviour* Movement::getBehaviour() {
	return behaviour;
}