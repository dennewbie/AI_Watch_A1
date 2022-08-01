//
//  SystemCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void SystemCommand::setCommand (std::string command) {
    this->command = command;
}

std::string SystemCommand::getCommand (void) {
    return this->command;
}

void SystemCommand::executeCommand (void) {
    setCommand();
    std::system(getCommand().c_str());
}
