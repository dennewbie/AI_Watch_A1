//
//  CleanCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void CleanCommand::setCommand (void) {
    std::stringstream cleanTerminalCommand;
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    
    const char ** argv = usageManagerInstance->get_argv();
    const char * imagesFolder = argv[imagesFolderOffset];
    const char * outputFolder = argv[outputFolderOffset];
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
