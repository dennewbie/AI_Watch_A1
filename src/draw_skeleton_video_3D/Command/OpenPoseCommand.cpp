//
//  OpenPoseCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void OpenPoseCommand::setCommand (void) {
    std::stringstream openPoseTerminalCommand;
    const char ** argv = UsageManager::getInstance()->get_argv();
    const char * openPoseFolder = argv[1];
    const char * openPoseExecuteCommand = argv[2];
    const char * imagesFolder = argv[3];
    const char * outputFolder = argv[4];
    openPoseTerminalCommand << "cd " << openPoseFolder << " && "
                            << openPoseExecuteCommand
                            << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir "
                            << imagesFolder << "rgb/ --write_json "
                            << outputFolder << "op/ --logging_level 255 > /dev/null";
    SystemCommand::command = std::string(openPoseTerminalCommand.str());
}
