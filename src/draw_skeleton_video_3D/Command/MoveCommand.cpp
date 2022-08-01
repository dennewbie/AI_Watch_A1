//
//  MoveCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void MoveCommand::setCommand (void) {
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    const char ** argv = usageManagerInstance->get_argv();
    std::stringstream moveTerminalCommand;
    const char * imagesFolder = argv[imagesFolderOffset];
    moveTerminalCommand << "mv -v " << imagesFolder << "rgb/* " << imagesFolder << "videoframe/ > /dev/null";
    SystemCommand::setCommand(std::string(moveTerminalCommand.str()));
}
