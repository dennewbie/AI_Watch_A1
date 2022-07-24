//
//  MoveCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void MoveCommand::setCommand (void) {
    std::stringstream moveTerminalCommand;
    const char ** argv = UsageManager::getInstance()->get_argv();
    const char * imagesFolder = argv[imagesFolderOffset];
    moveTerminalCommand << "mv -v " << imagesFolder << "rgb/* " << imagesFolder << "videoframe/ > /dev/null";
    SystemCommand::command = std::string(moveTerminalCommand.str());
}
