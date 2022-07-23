//
//  SystemCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



std::string SystemCommand::getCommand (void) {
    return this->command;
}

void SystemCommand::executeCommand (void) {
    setCommand();
    std::system(getCommand().c_str());
}
