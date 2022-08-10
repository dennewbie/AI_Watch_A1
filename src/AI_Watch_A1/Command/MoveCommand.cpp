//
//  MoveCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

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
