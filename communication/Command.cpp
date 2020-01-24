#include "Command.h"

/**
 CONSTRUCTOR
*/
Command::Command(std::string com) {
	command = com;
}

/**
 DECONSTRUCTOR
*/
Command::~Command() {

}

/**
 Gets the command
 @return The command
*/
std::string Command::getCommand() {
	return command;
}