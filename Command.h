/**
 @file Command.h
 @class Command
 @brief The Command Object that holds raw ROS data to be sent
 @details This Command Object holds raw ROS messages to be sent through
 the Messenger Object. Generally these Commands are generated in the Controller
 through a PID loop as required by each loop.

 @author Jonathan Chang
 @version 0.0.1
 @date 16/11/2019 16:18:30
*/
#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <string>
#include <string.h>

class Command {

public:
	Command(std::string com);
	Command() : Command("") {};
    ~Command();
    
	std::string getCommand();
private:
    std::string command;
};
#endif