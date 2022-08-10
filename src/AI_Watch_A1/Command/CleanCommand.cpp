//
//  CleanCommand.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "SystemCommand.hpp"



void CleanCommand::setCommand (int * argc, char *** argv) {
    std::stringstream cleanTerminalCommand;
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    
    char *** localArgv = usageManagerInstance->get_argv();
    const char * imagesFolder = (* localArgv)[imagesFolderOffset];
    const char * outputFolder = (* localArgv)[outputFolderOffset];
    cleanTerminalCommand << "rm -r " << imagesFolder << "rgb/ > /dev/null && "
                            "rm -r " << imagesFolder << "d/ > /dev/null && "
                            "rm -r " << imagesFolder << "skeleton/ > /dev/null && "
                            "rm -r " << imagesFolder << "videoframe/ > /dev/null && "
                            "rm -r " << outputFolder << "op/ > /dev/null && "
                            "rm -r " << imagesFolder << "depth/ > /dev/null && "
                            "rm -r " << imagesFolder << "sk/ > /dev/null && "
                            "rm -r " << outputFolder << "movement/ > /dev/null && "
                            "mkdir " << imagesFolder << "rgb && "
                            "mkdir " << imagesFolder << "d && "
                            "mkdir " << imagesFolder << "videoframe && "
                            "mkdir " << imagesFolder << "skeleton && "
                            "mkdir " << imagesFolder << "depth && "
                            "mkdir " << imagesFolder << "sk && "
                            "mkdir " << outputFolder << "movement/ && "
                            "mkdir " << outputFolder << "op/";
    SystemCommand::setCommand(std::string(cleanTerminalCommand.str()));
}
