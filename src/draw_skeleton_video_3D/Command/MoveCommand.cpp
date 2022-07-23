//
//  MoveCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void MoveCommand::setCommand (void) {
    std::stringstream moveTerminalCommand;
    moveTerminalCommand << "mv -v " << FacadeSingleton::getInstance()->get_argv()[3] << "rgb/* "
                        << FacadeSingleton::getInstance()->get_argv()[3] << "videoframe/ > /dev/null";
    SystemCommand::command = std::string(moveTerminalCommand.str());
}
