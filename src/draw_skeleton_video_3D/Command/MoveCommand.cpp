//
//  MoveCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void MoveCommand::setCommand (int * fileArgc, char *** argv) {
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    char *** localArgv = usageManagerInstance->get_argv();
    std::stringstream moveTerminalCommand;
    const char * imagesFolder = (* localArgv)[imagesFolderOffset];
    moveTerminalCommand << "mv -v " << imagesFolder << "rgb/ " << imagesFolder << "videoframe/ > /dev/null";
    SystemCommand::setCommand(std::string(moveTerminalCommand.str()));
}
