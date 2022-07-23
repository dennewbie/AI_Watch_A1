//
//  CleanCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void CleanCommand::setCommand (void) {
    std::stringstream cleanTerminalCommand;
    const char ** argv = UsageManager::getInstance()->get_argv();
    const char * imagesFolder = argv[3];
    const char * outputFolder = argv[4];
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
    SystemCommand::command = std::string(cleanTerminalCommand.str());
}
