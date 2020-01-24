/**
 @file Status.h
 @class Status
 @brief The Status class contains data about the result of a behaviour
 @details This Status class contains data about the result of an execution of a behaviour
 It contains an error code, a text description, and a sequence of commands.

 @author Jonathan Chang
 @version 0.0.1
 @date 09/01/2020
*/

#ifndef STATUS_H
#define STATUS_H

#include <string>
#include <vector>

#include "kinematics/Action.h"

enum state {fresh = 1, success = 2, running = 3, failure = 4, not_running = 5};

class Status {
public:
	Status(state stat, int errCod, std::string desc);
	Status() : Status(fresh, 0, "") {};
	~Status();

	Status* setRunning();
	Status* setSuccess();
	Status* setFailure();

	state getState();
	Status* setState(state stat);

	int getErrorCode();
	Status* setErrorCode(int errCod);

	std::string getDescription();
	Status* setDescription(std::string des);

	std::vector<Action*> getActions();
	Status* setActions(std::vector<Action*> acts);
	Status* addAction(Action* act);
	Status* removeAction(Action* act);
	Status* clearActions();

	void operator=(const Status& sta) {
		state_i = sta.state_i;
		errorCode = sta.errorCode;
		description = sta.description;
		actions = sta.actions;
	}

protected:
	state state_i;
	int errorCode;
	std::string description;
	std::vector<Action*> actions;

};
#endif
