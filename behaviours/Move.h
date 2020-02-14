#ifndef MOVE_H
#define MOVE_H

#include "../behaviourtree/Behaviour.h"

class Move : public Behaviour {
public:
	Move(double ny, double np, double hy, double hp);
	Move() : Move(0.0, 0.0, 0.0, 0.0) {};
	~Move();

	Status* executeC();
	Status* executeP(Status* stat);

	std::string toString();

protected:
	double neck_yaw;
	double neck_pitch;
	double head_yaw;
	double head_pitch;

};

#endif
