#include "Status.h"

Status::Status(state stat, int errCod, std::string desc) {
	state_i = stat;
	errorCode = errCod;
	description = desc;
}

Status::~Status() {

}

Status* Status::setRunning() {
	state_i = running;
	errorCode = 0;
	description = "Running";
	clearActions();
	return this;
}

Status* Status::setSuccess() {
	state_i = success;
	errorCode = 0;
	description = "Success";
	clearActions();
	return this;
}

Status* Status::setFailure() {
	state_i = failure;
	errorCode = -1;
	description = "Failure";
	clearActions();
	return this;
}

state Status::getState() {
	return state_i;
}

Status* Status::setState(state stat) {
	state_i = stat;
	return this;
}

int Status::getErrorCode() {
	return errorCode;
}

Status* Status::setErrorCode(int errCod) {
	errorCode = errCod;
	return this;
}

std::string Status::getDescription() {
	return description;
}

Status* Status::setDescription(std::string desc) {
	description = desc;
	return this;
}

std::vector<Action*> Status::getActions() {
	return actions;
}

Status* Status::setActions(std::vector<Action*> acts) {
	actions = acts;
	return this;
}

Status* Status::addAction(Action* act) {
	actions.push_back(act);
	return this;
}

Status* Status::removeAction(Action* act) {
	std::vector<Action*>::iterator itr;
	for (itr = actions.begin(); itr < actions.end(); itr++) {
		if (act == *itr) {
			actions.erase(itr);
		}
	}
	return this;
}

Status* Status::clearActions() {
	actions.clear();
	return this;
}
